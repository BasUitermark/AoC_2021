#include "header.h"

static void	print_array(int **array)
{
	size_t	line = 0;
	size_t	column = 0;

	while (line < SIZE + 2)
	{
		while (column < SIZE + 2)
		{
			if (array[line][column] > -1 || array[line][column] < 10)
				printf(" ");
			printf("%d ", array[line][column]);
			column++;
		}
		printf("\n");
		column = 0;
		line++;
	}
}

static int	**fill_array(void)
{
	size_t	line = 0;
	size_t	column = 0;
	int		**array;

	array = (int **)ft_calloc(SIZE + 3, sizeof(int *));
	while (line < SIZE + 2)
	{
		array[line] = (int *)ft_calloc(SIZE + 3, sizeof(int));
		while (column < SIZE + 2)
		{
			array[line][column] = -1;
			column++;
		}
		column = 0;
		line++;
	}
	return (array);
}

static int	**create_array(FILE *fd)
{
	size_t	line = 1;
	size_t	column = 1;
	size_t	i = 0;
	char	temp[SIZE + 2];
	int		**array;

	array = fill_array();
	while (line < SIZE + 1)
	{
		fgets(temp, SIZE + 2, fd);
		while (column < SIZE + 1)
		{
			array[line][column] = temp[i] - '0';
			column++;
			i++;
		}
		i = 0;
		column = 1;
		line++;
	}
	return (array);
}

static void	increment(int **array)
{
	size_t	line = 0;
	size_t	column = 0;

	while (line < SIZE + 2)
	{
		while (column < SIZE + 2)
		{
			if (array[line][column] >= 0)
				array[line][column] += 1;
			column++;
		}
		column = 0;
		line++;
	}
}

static int	check(int **array)
{
	size_t	line = 0;
	size_t	column = 0;
	size_t	count = 0;

	while (line < SIZE + 2)
	{
		while (column < SIZE + 2)
		{
			if (array[line][column] > 9)
				count++;
			column++;
		}
		column = 0;
		line++;
	}
	return (count);
}

static int	blink(int **array)
{
	size_t	line = 0;
	size_t	column = 0;
	int		blink = 0;

	while (check(array))
	{
		while (line < SIZE + 2)
		{
			while (column < SIZE + 2)
			{
				if (array[line][column] > 9)
				{
					if (array[line][column + 1] >= 0)
						array[line][column + 1] += 1;
					if (array[line][column - 1] >= 0)
						array[line][column - 1] += 1;
					if (array[line + 1][column] >= 0)
						array[line + 1][column] += 1;
					if (array[line - 1][column] >= 0)
						array[line - 1][column] += 1;
					if (array[line + 1][column + 1] >= 0)
						array[line + 1][column + 1] += 1;
					if (array[line - 1][column - 1] >= 0)
						array[line - 1][column - 1] += 1;
					if (array[line + 1][column - 1] >= 0)
						array[line + 1][column - 1] += 1;
					if (array[line - 1][column + 1] >= 0)
						array[line - 1][column + 1] += 1;
					blink++;
					array[line][column] = -99;
				}
				column++;
			}
			column = 0;
			line++;
		}
		line = 0;
	}
	// printf("Blinks: %d\n", blink);
	return (blink);
}

static int	change(int **array)
{
	size_t	line = 0;
	size_t	column = 0;

	while (line < SIZE + 2)
	{
		while (column < SIZE + 2)
		{
			if (array[line][column] == -99)
				array[line][column] = 0;
			column++;
		}
		column = 0;
		line++;
	}
}

static int	read_instruct(FILE *fd)
{
	int	**array;
	size_t	n = 0;
	int	blinks = 0;
	int	total_blinks = 0;

	array = create_array(fd);
	while (n < DAYS)
	{
		increment(array);
		blinks = blink(array);
		if (blinks == 100)
			printf ("The big blink: DAY%d\n", n + 1);
		total_blinks += blinks;
		change(array);
		n++;
	}
	printf("Total: %d\n\n", total_blinks);
	// print_array(array);

}

int	main(void)
{
	FILE	*fd;

	fd = fopen("inputJ.txt", "r");
	read_instruct(fd);

	fclose(fd);
}