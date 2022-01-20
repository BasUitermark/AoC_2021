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

static void	print_list(t_list *list)
{
	while (list)
	{
		printf("%s, ", list->content);
		list = list->next;
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
	marked_caves = NULL;
	marked_caves = ft_dlstnew("start");
}

static void	remove_current(char *current)
{
	t_dlist *temp;

	temp = marked_caves;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->content, current, ft_strlen(current)) == 0)
		{
			ft_dlstdel_node(&temp, temp);
			break ;
		}
		temp = temp->next;
	}
}

static int	check_marked(char *current)
{
	size_t	len = 0;
	t_dlist	*temp;

	len = ft_strlen(current);
	temp = marked_caves;
	while (temp != NULL)
	{
		if (ft_strncmp(current, temp->content, len) == 0)
			return(1);
		temp = temp->next;
	}
	return (0);
}

static void	mark(char *current)
{
	ft_dlstadd_back(&marked_caves, ft_dlstnew(current));
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

static t_list	*search_neighbors(char *current, char **array)
{
	size_t	i = 0;
	char	*str1;
	char	*str2;
	t_list	*neighbors = NULL;

	while (array[i])
	{
		str1 = scan_str1(array[i]);
		str2 = scan_str2(array[i]);
		if (ft_strncmp(str1, current, ft_strlen(current)) == 0)
			ft_lstadd_back(&neighbors, ft_lstnew(str2));
		else if (ft_strncmp(str2, current, ft_strlen(current)) == 0)
			ft_lstadd_back(&neighbors, ft_lstnew(str1));
		i++;
	}
	return (neighbors);
}

static void	search_paths(char *current, char **array)
{
	size_t	i = 0;
	t_list	*neighbors;

	if (ft_strncmp(current, "end", 3) == 0)
	{
		paths++;
		return ;
	}

	if (ft_strncmp(current, "start", 5) != 0 && ft_islower(current[0]) && check_marked(current) == 1)
		return ;

	if (ft_strncmp(current, "start", 5) != 0 && ft_islower(current[0]))
		mark(current);

	neighbors = search_neighbors(current, array);
	while (neighbors)
	{
		if (ft_strncmp(neighbors->content, "start", 5) == 0)
		{
			neighbors = neighbors->next;
			continue ;
		}
		search_paths(neighbors->content, array);
		neighbors = neighbors->next;
	}

	if (ft_strncmp(current, "start", 5) != 0 && ft_islower(current[0]))
	{
		remove_current(current);
		marks--;
	}
	ft_lstclear(&neighbors, free);
	return ;
}

static int	read_instruct(FILE *fd)
{
	char	**array;

	array = ft_create_2d_array(LINES, SIZE);
	fill_array(array, fd);
	init_marked();
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