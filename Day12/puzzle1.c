#include "header.h"

static void	print_array(char **array)
{
	size_t	i = 0;

	while (array[i])
	{
		printf("%s\n", array[i]);
		i++;
	}
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

	while (line < LINES)
	{
		fgets(temp, SIZE + 1, fd);
		strcpy(array[line], temp);
		line++;
	}
}

static void	init_marked(void)
{
	marked_caves = (char**)ft_calloc(1, sizeof(char *));
	marked_caves[0] = (char *)ft_calloc(6, sizeof(char));
	ft_strlcpy(marked_caves[0], "start", 6);
}

static void	reset_marked(int marks)
{
	size_t	i = 0;

	while (marks > i)
	{
		free(marked_caves[marks]);
		marks--;
	}
	free(marked_caves);
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
	printf("<%s> is not marked\n", current);
	return (0);
}

static void	mark(char *current)
{
	size_t	len = 0;

	marks++;
	len = ft_strlen(current);
	// printf("len: %d", len);
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
			neighbors[j] = (char *)ft_calloc(ft_strlen(str2) + 1, sizeof(char));
			strcpy(neighbors[j], str2);
			j++;
		}
		if (ft_strncmp(str2, current, ft_strlen(current)) == 0)
		{
			neighbors = (char **)realloc(neighbors, (j + 1) * sizeof(char *));
			neighbors[j] = (char *)ft_calloc(ft_strlen(str1) + 1, sizeof(char));
			strcpy(neighbors[j], str1);
			j++;
		}
		free(str1);
		free(str2);
		i++;
	}
	return (neighbors);
}

static void	search_paths(char *current, char **array)
{
	size_t	i = 0;
	char	**neighbors;

	printf("Current node: %s\n", current);
	printf("Total paths: %d\n", paths);
	printf("Marks: %d\n", marks);
	printf("Marked caves:\n");
	print_array(marked_caves);

	//check if current is end, if it is we have completed a path
	if (ft_strncmp(current, "end", 3) == 0)
	{
		printf("BRANCH ENDED\n");
		paths++;
		return ;
	}
	// printf("1\n");
	//check if current is a small cave and is marked
	//if it is marked, that means this isn't a valid path
	if (ft_strncmp(current, "start", 5) != 0 && ft_islower(current[0]) && check_marked(current) == 1)
	{
		printf("<%s> is false!\n", current);
		return ;
	}

	// printf("2\n");
	//if it is not marked, mark the cave
	if (ft_islower(current[0]) && ft_strncmp(current, "start", 5) != 0)
	{
		printf("Added <%s> to marked\n", current);
		mark(current);
	}
	// printf("3\n");
	//make an array of all the neighbors of current
	neighbors = search_neighbors(current, array);
	printf("Neighbors:\n");
	print_array(neighbors);

	//recursively search through all neighbors
	while (neighbors[i])
	{
		if (ft_strncmp(neighbors[i], "start", 5) == 0)//if current neighbor is start then skip
		{
			// printf("%d\n", i);
			i++;
			continue ;
		}
		printf("Next node: %s\n\n", neighbors[i]);
		search_paths(neighbors[i], array);
		i++;
	}

	//when a single path has been completed reset marked caves
	if (marks > 1)
		reset_marked(marks);
	init_marked();
	marks = 1;
	return ;
}

static int	read_instruct(FILE *fd)
{
	char	**array;
	char	**neighbors;

	array = ft_create_2d_array(LINES, SIZE);
	fill_array(array, fd);
	init_marked();
	mark("b");
	search_paths("A", array);

	// neighbors = search_neighbors("A", array);
	// printf("%s\n", neighbors[0]);
	// printf("%s\n", neighbors[1]);
	// printf("%s\n", neighbors[2]);
	// printf("%s\n", neighbors[3]);
	// printf("%d\n", ft_strlen(neighbors[0]));
	// printf("%d\n", ft_strlen(neighbors[1]));
	// printf("%d\n", ft_strlen(neighbors[2]));
	// printf("%d\n", ft_strlen(neighbors[3]));
	// mark("c");
}

int	main(void)
{
	FILE	*fd;

	fd = fopen("test1.txt", "r");
	read_instruct(fd);

	fclose(fd);
}