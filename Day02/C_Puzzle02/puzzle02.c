#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "../../libft/libft.h"

/*
/== INSTRUCTIONS ==/
Calculate the horizontal position and depth you would have 
after following the planned course. 
What do you get if you multiply your final horizontal position 
by your final depth?

- Forward X increases the horizontal position by X units.
- Down X increases the depth by X units.
- Up X decreases the depth by X units.

/== Location ==/
location[0] = Position	(Forward)
location[1] = Depth		(Up-, Down+)
*/

void	read_location(char **array, int i, int *location)
{
	int	tempPos;

	tempPos = 0;
	while (array[i])
	{
		if (array[i][0] == 'f')
		{
			location[0] += ft_atoi_plus(array[i]);
			tempPos = ft_atoi_plus(array[i]);
			location[1] += tempPos * location[2];
		}
		if (array[i][0] == 'd')
			location[2] += ft_atoi_plus(array[i]);
		if (array[i][0] == 'u')
			location[2] -= ft_atoi_plus(array[i]);
		tempPos = 0;
		i++;
	}
	//== DEBUG ==//
	printf("Position: %d\n", location[0]);
	printf("Aim: %d\n", location[2]);
	printf("Depth: %d\n", location[1]);
}

int	read_instruct(int fd)
{
	char	**array;
	char	temp[10000];
	int		location[3];
	int		i;

	i = 0;
	read(fd, temp, 10000);
	array = ft_split(temp, '\n');
	read_location(array, i, location);
	return (location[0] * location[1]);
}

int	main(void)
{
	int	fd;

	fd = open("input.txt", O_RDONLY);
	printf("Product: %d\n", read_instruct(fd));
	close(fd);
}
