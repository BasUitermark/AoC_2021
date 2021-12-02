#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "../../libft/libft.h"

int	read_num(char **array, int i)
{
	int	count = 0;

	while (array[i])
	{
		if (ft_atoi(array[i]) > ft_atoi(array[i - 1]))
			count++;
		i++;
	}
	//== DEBUG ==//
	return (count);
}

int	read_instruct(int fd)
{
	char	**array;
	char	temp[10000];
	int		i = 1;

	read(fd, temp, 10000);
	array = ft_split(temp, '\n');
	return (read_num(array, i));
}

int	main(void)
{
	int	fd;

	fd = open("input.txt", O_RDONLY);
	// read_instruct(fd);
	printf("Count: %d\n", read_instruct(fd));
	close(fd);
}