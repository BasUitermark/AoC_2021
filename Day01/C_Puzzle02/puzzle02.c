#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "../../libft/libft.h"

int	sum_calc(char **array, int i)
{
	return (ft_atoi(array[i]) + ft_atoi(array[i + 1]) + ft_atoi(array[i + 2]));
}

int	read_num(char **array, int i)
{
	int	count;
	int	sum[2];

	count = 0;
	while (array[i + 2])
	{
		sum[0] = sum_calc(array, i);
		sum[1] = sum_calc(array, i - 1);
		if (sum[0] > sum[1])
			count++;
		i++;
	}
	return (count);
}

int	read_instruct(int fd)
{
	char	**array;
	char	temp[10000];
	int		i;

	i = 1;
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
