#include "header.h"

static int	**fill_array(FILE *fd)
{
	size_t	i = 0;
	size_t	j = 0;
	char	temp[SIZE + 1];
	char	**temparray;
	int		**array;

	array = (int **)ft_calloc(LINES, sizeof(int *));
	while (i < LINES)
	{
		fgets(temp, SIZE + 1, fd);
		temparray = ft_split(temp, ',');
		array[i] = (int *)ft_calloc(2, sizeof(int));
		while (j < 2)
		{
			array[i][j] = ft_atoi(temparray[j]);
			j++;
		}
		j = 0;
		i++;
	}
	fgets(temp, SIZE + 1, fd);
	return (array);
}

static t_dlist	*fill_folds(FILE *fd)
{
	t_size	i = 0;
	char	temp[STR_SIZE + 1];
	t_dlist	*list = NULL;
	char	tempstr[FOLD_SIZE + 1];

	while (i < FOLDS)
	{
		fgets(temp, STR_SIZE + 1, fd);
		sscanf(temp, "%*s %*s %s", tempstr);
		ft_dlstadd_back(&list, ft_dlstnew(ft_strdup(tempstr)));
		i++;
	}
}

static int	fold_n(int n, int value)
{
	int	temp;

	temp = value - n;
	return (temp * -1);
}

static t_array	instruct_folds(int **array, t_dlist *list)
{
	size_t	i = 0;
	size_t	line = 0;
	t_array	array_size;

	array_size.x = 0;
	array_size.y = 0;
	while (list)
	{
		if (((char *)list->content)[0] == 'x')
		{
			array_size.x++;
			while (line < LINES)
			{
				if (array[line][0] > ft_atoi(&((char *)list->content)[2]))
					fold_n(ft_atoi(&((char *)list->content)[2]), array[line][0]);
				line++;
			}
		}
		if (((char*)list->content)[0] == 'y')
		{
			array_size.y++;
			while (line < LINES)
			{
				if (array[line][1] > ft_atoi(&((char *)list->content)[2]))
					fold_n(ft_atoi(&((char *)list->content)[2]), array[line][1]);
				line++;
			}
		}
		list = list->next;
		line = 0;
		i++;
	}
	return (array_size);
}

static int	*grid_size(int **array)
{
	size_t	i = 0;
	int		gsize[2] = {0, 0};

	while (i < LINES)
	{
		if (gsize[0] < array[i][0])
			gsize[0] = array[i][0];
		if (gsize[1] < array[i][1])
			gsize[0] = array[i][0];
		i++;
	}
	return (gsize);
}

static int	**make_array(int **array, t_array array_size)
{
	int	**grid;
	int	*gsize;

	gsize = grid_size(array);
	
}

static int	read_instruct(FILE *fd)
{
	int		**array;
	t_dlist	*folds;
	t_array	array_size;
	int		**grid;

	array = fill_array(fd);
	folds = fill_folds(fd);
	array_size = instruct_folds(array, folds);
	grid = make_array(array, array_size);
	ft_printcarray();
}


int	main(void)
{
	FILE	*fd;

	fd = fopen("test.txt", "r");
	read_instruct(fd);
	fclose(fd);
}