#include "header.h"
#include <math.h>

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

static int	find_average(int *input)
{
	double	temp = 0;
	size_t	i = 0;

	while (i < CRABS)
	{
		temp += (double)input[i];
		i++;
	}
	temp = temp / CRABS;
	return ((int)ceil(temp));
}

static int	gauss(int n)
{
	int	start;

	start = n + 1;
	return (n * start / 2);
}

static void	calc_fuel(int *input, int average)
{
	size_t	i = 0;
	size_t	temp = 0;
	size_t	fuel = 0;

	while (i < CRABS)
	{
		temp = input[i] - average;
		temp = ft_abs(temp);
		fuel += gauss(temp);
		i++;
	}
	printf("Fuel: %d\n", fuel);
}

int	read_instruct(FILE *fd)
{
	int	*input;
	int	average = 0;

	input = read_input(fd);
	qsort(input, CRABS, sizeof(int), cmpfunc);
	average = find_average(input);
	printf("Average: %d\n", average);
	calc_fuel(input, average - 1);
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