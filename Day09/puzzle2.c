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
	// print_array(array);
	return (array);
}

static int	check_point(int **array, size_t line, size_t column)
{
	size_t	num = 1;

	int	entry = array[line][column];


	array[line][column] = 9;

	if (entry == 9 || entry == 20) return 0;

	if (array[line][column + 1] > entry && array[line][column + 1] != 9)
		num += check_point(array, line, column + 1);
	if (array[line][column - 1] > entry && array[line][column - 1] != 9)
		num += check_point(array, line, column - 1);
	if (array[line + 1][column] > entry && array[line + 1][column] != 9)
		num += check_point(array, line + 1, column);
	if (array[line - 1][column] > entry && array[line - 1][column] != 9)
		num += check_point(array, line - 1, column);
	// if (array[line][column] != 9)
	// 	array[line][column] = 9;

	return (num);
}

static int	check_neighbor(int **array, size_t line, size_t column)
{
	if (array[line][column] < array[line][column - 1] && 
		array[line][column] < array[line][column + 1] && 
		array[line][column] < array[line - 1][column] && 
		array[line][column] < array[line + 1][column])
		return (1);
	return (0);
}

static t_basin	check_risk(int **array)
{
	size_t	line = 0;
	size_t	column = 0;
	int		**temp_array;
	t_basin store;

	store.basin_size = 0;
	store.basins = (int *)ft_calloc(1, sizeof(int));
	while (line < LINE + 2)
	{
		while (column < SIZE + 2)
		{
			if (check_neighbor(array, line, column) && array[line][column] != 9)
			{
				store.basins = (int *)realloc(store.basins, (store.basin_size + 1) * sizeof(int));
				temp_array = array;
				store.basins[store.basin_size] = check_point(temp_array, line, column);
				// printf("Number: %d\nLine: %d\nColumn: %d\n", array[line][column], line, column);
				// printf("Basin Size: %d\n\n", store.basins[store.basin_size]);
				store.basin_size++;
			}
			column++;
		}
		column = 0;
		line++;
	}
	return (store);
}

static int	cmpfunc(const void *a, const void *b)
{
	return (*(int*)b - *(int*)a);
}

static void calculate_product(t_basin store)
{
	int	product = 1;
	int	i = 0;

	qsort(store.basins, store.basin_size, sizeof(int), cmpfunc);
	// printf("%d\n", store.basins[0]);
	// printf("%d\n", store.basins[1]);
	// printf("%d\n", store.basins[2]);
	while (i < 3)
	{
		product *= store.basins[i];
		i++;
	}
	printf("Product: %d", product);
}

static void	print_basins(t_basin store)
{
	size_t	i = 0;

	qsort(store.basins, store.basin_size, sizeof(int), cmpfunc);
	while (i < store.basin_size)
	{
		printf("%d\n", store.basins[i]);
		i++;
	}
}

static int	read_instruct(FILE *fd)
{
	int		**array;
	t_basin	store;

	array = create_array(fd);
	// check_point(array, 64, 80);
	// print_array(array);
	store = check_risk(array);
	// print_basins(store);
	calculate_product(store);
}

int	main(void)
{
	FILE	*fd;

	fd = fopen("input.txt", "r");
	read_instruct(fd);

	fclose(fd);
}