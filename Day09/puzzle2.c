#include "header.h"

static void	print_array(int **array)
{
	size_t	line = 0;
	size_t	column = 0;

	while (line < LINE + 2)
	{
		while (column < SIZE + 2)
		{
			if (array[line][column] < 10)
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

	array = (int **)ft_calloc(LINE + 3, sizeof(int *));
	while (line < LINE + 2)
	{
		array[line] = (int *)ft_calloc(SIZE + 3, sizeof(int));
		while (column < SIZE + 2)
		{
			array[line][column] = 20;
			column++;
		}
		column = 0;
		line++;
	}
	return (array);
	// printf("%d\n", array[2][10]);
}

static int	**create_array(FILE *fd)
{
	size_t	line = 1;
	size_t	column = 1;
	size_t	i = 0;
	char	temp[SIZE + 2];
	int		**array;

	array = fill_array();
	while (line < LINE + 1)
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
	print_array(array);
	return (array);
}

static int	check_point(int **array, size_t line, size_t column)
{
	size_t	num = 0;

	/*
	Send copy of main array and reset before main send to check_point

	Return should be stored in a new int array. 
	Use realloc to increase storage by 1 after every succesful itteration

	Use reverse qsort and return the product of the 3 highest numbers

	if (array[line][column] - array[line][column + 1] == -1)
		num += check_point(array, line, column + 1)
	if (array[line][column] - array[line][column - 1] == -1)
		num += check_point(array, line, column - 1)
	if (array[line][column] - array[line + 1][column] == -1)
		num += check_point(array, line + 1, column)
	if (array[line][column] - array[line - 1][column] == -1)
		num += check_point(array, line - 1, column)
	array[line][column] = 20;
	*/

	return (num);
}

static int	check_neighbor(int **array, size_t line, size_t column)
{
	if (array[line][column] < array[line][column - 1] & 
		array[line][column] < array[line][column + 1] & 
		array[line][column] < array[line - 1][column] & 
		array[line][column] < array[line + 1][column])
		return (1);
	return (0);
}

static void	check_risk(int **array)
{
	size_t	line = 1;
	size_t	column = 1;
	int		num = 0;

	while (line < LINE + 1)
	{
		while (column < SIZE + 1)
		{
			if (check_neighbor(array, line, column))
				num += check_point(array, line, column);
			column++;
		}
		column = 0;
		line++;
	}
	// printf("%d\n", risk);
}

static int	read_instruct(FILE *fd)
{
	int		**array;

	array = create_array(fd);
	
	check_risk(array);
}

int	main(void)
{
	FILE	*fd;

	fd = fopen("test.txt", "r");
	read_instruct(fd);

	fclose(fd);
}