#include "header.h"

static void	print_array(char **array)
{
	size_t	i = 0;

	while (array[i])
	{
		printf("%s, ", array[i]);
		i++;
	}
	printf("\n");
}

static char	**ft_create_2d_array(size_t lines, size_t size)
{
	size_t	i;
	char	**array;

	i = 0;
	array = (char **)ft_calloc(lines + 1, sizeof(char *));
	while (i < lines)
	{
		array[i] = (char *)ft_calloc(size + 1, sizeof(char));
		i++;
	}
	return (array);
}

static void fill_array(char **array, FILE *fd)
{
	size_t	line = 0;
	char	temp[SIZE + 1];

	while (line < LINES - 1)
	{
		fgets(temp, SIZE + 1, fd);
		ft_strlcpy(array[line], temp, ft_strlen(temp));
		line++;
	}
	fgets(temp, SIZE + 1, fd);
	ft_strlcpy(array[line], temp, 1 + ft_strlen(temp));
}

static void	init_marked(void)
{
	marked_caves = (char**)ft_calloc(1, sizeof(char *));
	marked_caves[0] = (char *)ft_calloc(6, sizeof(char));
	ft_strlcpy(marked_caves[0], "start", 6);
}

static void	remove_current(char *current)
{
	size_t	i = 0;

	while (i < marks)
	{
		if (ft_strncmp(marked_caves[i], current, ft_strlen(current)) == 0)
			break ;
		i++;
	}
	free(marked_caves[i]);
	marked_caves[i] = NULL;
}

static int	check_marked(char *current)
{
	size_t	i = 1;
	size_t	len = 0;

	len = ft_strlen(current);
	// printf("len: %d\n", len);
	printf("Getting checked: %s\n", current);
	while (i <= marks)
	{
		// printf("help");
		if (ft_strncmp(current, marked_caves[i], len) == 0)
			return (1);
		i++;
	}
	return (0);
}

static void	mark(char *current)
{
	size_t	len = 0;

	marks++;
	len = ft_strlen(current);
	// printf("len: %d\n", len);
	marked_caves = (char **)realloc(marked_caves, (marks + 2) * sizeof(char *));
	marked_caves[marks] = (char *)ft_calloc(len + 1, sizeof(char));
	strcpy(marked_caves[marks], current);
}

static char	*scan_str1(char *array)
{
	size_t	i = 0;
	size_t	j = 0;
	size_t	len = 0;
	char	*str1;

	while (array[i] != '-')
	{
		len++;
		i++;
	}
	i = 0;
	str1 = (char *)ft_calloc(len + 1, sizeof(char));
	while (array[i] != '-')
	{
		str1[j] = array[i];
		j++;
		i++;
	}
	return (str1);
}

static char	*scan_str2(char *array)
{
	size_t	i = 0;
	size_t	j = 0;
	size_t	len = 0;
	char	*str2;

	while (array[j] != '-')
	{
		i++;
		j++;
	}
	j++;
	while (array[i])
	{
		len++;
		i++;
	}
	i = j;
	j = 0;
	str2 = (char *)ft_calloc(len + 1, sizeof(char));
	while (array[i] && array[i] != '\n')
	{
		str2[j] = array[i];
		j++;
		i++;
	}
	return (str2);
}

static char	**search_neighbors(char *current, char **array)
{
	size_t	i = 0;
	size_t	j = 0;
	char	*str1;
	char	*str2;
	char	**neighbors;

	neighbors = (char**)ft_calloc(1, sizeof(char *));
	while (array[i])
	{
		str1 = scan_str1(array[i]);
		str2 = scan_str2(array[i]);
		if (ft_strncmp(str1, current, ft_strlen(current)) == 0)
		{
			neighbors = (char **)realloc(neighbors, (j + 1) * sizeof(char *));
			neighbors[j] = (char *)ft_calloc(ft_strlen(str2), sizeof(char));
			strcpy(neighbors[j], str2);
			j++;
		}
		else if (ft_strncmp(str2, current, ft_strlen(current)) == 0)
		{
			neighbors = (char **)realloc(neighbors, (j + 1) * sizeof(char *));
			neighbors[j] = (char *)ft_calloc(ft_strlen(str1), sizeof(char));
			strcpy(neighbors[j], str1);
			j++;
		}
		i++;
	}
	return (neighbors);
}

static void	search_paths(char *current, char **array)
{
	size_t	i = 0;
	char	**neighbors;


	//check if current is end, if it is we have completed a path
	if (ft_strncmp(current, "end", 3) == 0)
	{
		printf(RED "End of branch\n" RESET);
		paths++;
		return ;
	}

	printf(CYAN"Current node: <%s>\n"RESET, current);
	printf(GREEN"Path count: %d\n"RESET, paths);
	printf("Marked caves:\n");
	print_array(&marked_caves[1]);

	//check if current is a small cave and is marked
	//if it is marked, that means this isn't a valid path
	if (ft_strncmp(current, "start", 5) != 0 && ft_islower(current[0]) && check_marked(current) == 1)
	{
		printf("<%s> is marked!\n", current);
		return ;
	}

	// printf("2\n");
	//if it is not marked, mark the cave
	if (ft_strncmp(current, "start", 5) != 0 && ft_islower(current[0]))
	{
		printf("Added <%s> to marked\n", current);
		mark(current);
	}
	// printf("3\n");
	//make an array of all the neighbors of current
	neighbors = search_neighbors(current, array);

	//recursively search through all neighbors
	while (neighbors[i])
	{
		if (ft_strncmp(neighbors[i], "start", 5) == 0)//if current neighbor is start then skip
		{
			i++;
			continue ;
		}

		printf("Neighbors:\n");
		print_array(neighbors);

		printf(CYAN"Next node: <%s>\n\n"RESET, neighbors[i]);
		search_paths(neighbors[i], array);
		printf(CYAN"Returned to node: <%s>\n"RESET, current);
		i++;
	}
	printf("All neighbors checked\n");

	printf(RED"Exiting branch\n"RESET);
	//when a single path has been completed remove cave from list
	if (ft_strncmp(current, "start", 5) != 0 && ft_islower(current[0]))
	{
		printf("Removing <%s> from marked\n", current);
		remove_current(current);
		marks--;
	}
	printf(GREEN"Branch exited successfully!\n"RESET);
	return ;
}

static int	read_instruct(FILE *fd)
{
	char	**array;
	char	**neighbors;

	size_t	i = 0;

	array = ft_create_2d_array(LINES, SIZE);
	fill_array(array, fd);
	init_marked();
	// print_array(array);
	// neighbors = search_neighbors("b", array);
	// print_array(neighbors);
	search_paths("start", array);
	printf(GREEN"\nTotal paths in file: %d\n"RESET, paths);
}

int	main(void)
{
	FILE	*fd;

	fd = fopen("test1.txt", "r");
	read_instruct(fd);
	fclose(fd);
}