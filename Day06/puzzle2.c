#include "header.h"

static void	print_input(unsigned long long *input, unsigned long long fish_count)
{
	size_t	i = 0;
	static size_t	days = 0;

	printf("After	%d	days: ", days);
	while (i < fish_count)
	{
		printf("%d,", input[i]);
		i++;
	}
	printf("\n");
	days++;
}

static void	print_container(unsigned long long *container)
{
	size_t	i = 0;
	size_t	cont = 0;
	static size_t day = 0;

	printf("Day %\n", day);
	while (i < 9)
	{
		printf("Container: %d Amount: %lld\n", cont, container[i]);
		cont++;
		i++;
	}
	day++;
	printf("\n");
}

static int	*read_input(FILE *fd)
{
	size_t	i = 0;
	size_t	j = 0;
	char	temp[FILE_SIZE + 1];
	int		*input;

	input = (int *)ft_calloc(FISH, sizeof(int));
	fread(temp, 1, FILE_SIZE, fd);
	while (i < FISH)
	{
		input[i] = ft_atoi(&temp[j]);
		j += 2;
		i++;
	}
	return (input);
}

static void	fill_container(unsigned long long *container, int *input)
{
	size_t	i = 0;

	while (i < FISH)
	{
		if (input[i] == 0)
			container[0]++;
		else if (input[i] == 1)
			container[1]++;
		else if (input[i] == 2)
			container[2]++;
		else if (input[i] == 3)
			container[3]++;
		else if (input[i] == 4)
			container[4]++;
		else if (input[i] == 5)
			container[5]++;
		else if (input[i] == 6)
			container[6]++;
		else if (input[i] == 7)
			container[7]++;
		else if (input[i] == 8)
			container[8]++;
		i++;
	}
}

static void	calc_fish(unsigned long long *c)
{
	unsigned long long sum = 0;

	sum = c[0] + c[1] + c[2] + c[3] + c[4] + c[5] + c[6] + c[7] + c[8];
	printf("Total fish: %lld\n", sum);
}

static void	calc_container(int *input)
{
	unsigned long long	*container;
	unsigned long long	temp_last = 0;
	size_t		current_day = 0;

	container = (unsigned long long *)ft_calloc(9, sizeof(unsigned long long));
	fill_container(container, input);
	// print_container(container);
	while(current_day < DAYS)
	{
		temp_last = container[0];
		container[0] = container[1];
		container[1] = container[2];
		container[2] = container[3];
		container[3] = container[4];
		container[4] = container[5];
		container[5] = container[6];
		container[6] = container[7];
		container[7] = container[8];
		container[8] = 0;
		if (temp_last)
		{
			container[6] += temp_last;
			container[8] = temp_last;
			temp_last = 0;
		}
		// print_container(container);
		// printf("%d\n", temp_last);
		current_day++;
	}
	print_container(container);
	calc_fish(container);
}

int	read_instruct(FILE *fd)
{
	int	*input;

	input = read_input(fd);
	calc_container(input);
	// print_input(input);
	return (0);
}

int	main(void)
{
	FILE	*fd;

	fd = fopen("input.txt", "r");
	read_instruct(fd);
	fclose(fd);
}