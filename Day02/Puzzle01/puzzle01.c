#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "../../libft/libft.h"

/*
location[0] = Position	(Forward)
location[1] = Depth		(Up-, Down+)
*/

int	*read_location(char **array, int i, int *location)
{
	while (array[i])
	{
		if (array[i][0] == 'f')
			location[0] += ft_atoi_plus(array[i]);
		if (array[i][0] == 'd')
			location[1] += ft_atoi_plus(array[i]);
		if (array[i][0] == 'u')
			location[1] -= ft_atoi_plus(array[i]);
		i++;
	}
	//== DEBUG ==//
	printf("Position: %d\n", location[0]);
	printf("Depth: %d\n", location[1]);
}

int	read_instruct(int fd)
{
	char	**array;
	char	temp[10000];
	int		location[2] = {0, 0};
	int		i = 0;

	read(fd, temp, 10000);
	array = ft_split(temp, '\n');
	read_location(array, i, location);
	return (location[0] * location[1]);
}

int	main(void)
{
	int	fd;

	fd = open("input.txt", O_RDONLY);
	// read_instruct(fd);
	printf("Product: %d\n", read_instruct(fd));
	close(fd);
}
