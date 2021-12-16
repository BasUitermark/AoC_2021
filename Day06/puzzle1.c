#include "header.h"

static void	print_input(long long *input, long long fish_count)
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

static long long	*read_input(FILE *fd)
{
	size_t	i = 0;
	size_t	j = 0;
	char	temp[FILE_SIZE + 1];
	long long		*input;

	input = (long long *)ft_calloc(FISH, sizeof(long long));
	fread(temp, 1, FILE_SIZE, fd);
	while (i < FISH)
	{
		input[i] = ft_atoi(&temp[j]);
		j += 2;
		i++;
	}
	return (input);
}

static void	calc_fish(long long *input)
{
	size_t	day_count = 0;
	size_t	i = 0;
	long long	current_count = FISH;
	long long	new_count= 0;

	// print_input(input, current_count);
	while (day_count < DAYS)
	{
		while (i < current_count)
		{
			if (new_count < current_count)
				new_count = current_count;
			input[i]--;
			if (input[i] == -1)
			{
				new_count++;
				input = (long long *)realloc(input, new_count * sizeof(long long));
				input[new_count - 1] = 8;
			}
			if (input[i] == -1)
				input[i] = 6;
			// printf("%d\n", new_count);
			i++;
		}
		i = 0;
		current_count = new_count;
		day_count++;
		// print_input(input, current_count);
	}
	printf("Total fish: %d\n", current_count);
}

int	read_instruct(FILE *fd)
{
	long long	*input;

	input = read_input(fd);
	calc_fish(input);
	// print_input(input);
	return (0);
}

int	main(void)
{
	FILE	*fd;

	fd = fopen("test.txt", "r");
	read_instruct(fd);
	fclose(fd);
}