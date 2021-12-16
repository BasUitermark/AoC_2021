#include "header.h"

static void	print_list(int *input)
{
	size_t	i = 0;

	while (i < CRABS)
	{
		printf("%d\n", input[i]);
		i++;
	}
}

static int	count_crabs(char **split)
{
	size_t	i = 0;

	while (split[i])
		i++;
	return (i);
}

static int	*read_input(FILE *fd)
{
	size_t	i = 0;
	size_t	j = 0;
	size_t	count = 0;
	char	temp[FILE_SIZE + 1];
	int		*list;

	fread(temp, 1, FILE_SIZE, fd);
	list = (int *)ft_calloc(CRABS, sizeof(int));
	while (i < CRABS)
	{
		list[i] = ft_atoi(&temp[j]);
		while (ft_isdigit(temp[j]))
			j++;
		j++;
		i++;
	}
	// print_list(list, count);
	return (list);
}

static int	cmpfunc (const void * a, const void * b) 
{
	return ( *(int*)a - *(int*)b );
}

static int	find_median(int *input)
{
	size_t	median = 0;
	size_t	temp = 0;

	temp = CRABS;
	if (temp % 2 != 0)
		temp++;
	return (input[temp / 2]);
}

static void	calc_fuel(int *input, int median)
{
	size_t	i = 0;
	size_t	temp = 0;
	size_t	fuel = 0;

	while (i < CRABS)
	{
		temp = input[i] - median;
		temp = ft_abs(temp);
		fuel += temp; 
		i++;
	}
	printf("%d", fuel);
}

int	read_instruct(FILE *fd)
{
	int	*input;
	int	median = 0;

	input = read_input(fd);
	qsort(input, CRABS, sizeof(int), cmpfunc);
	median = find_median(input);
	// printf("%d", median);
	calc_fuel(input, median);
	// print_list(input);
	return (0);
}

int	main(void)
{
	FILE	*fd;

	fd = fopen("input.txt", "r");
	read_instruct(fd);
	fclose(fd);
}