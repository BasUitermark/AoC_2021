#include "header.h"

static char	**create_list(void)
{
	size_t	line = 0;
	char	**list;

	list = (char **)ft_calloc(LINES + 1, sizeof(char *));
	while (line < LINES)
	{
		list[line] = (char *)ft_calloc(LINE_SIZE + 1, sizeof(char));
		line++;
	}
	return (list);
}

static void	fill_list(char **list, FILE *fd)
{
	size_t	line = 0;
	char	temp[LINE_SIZE];

	while (line < LINES)
	{
		fgets(temp, LINE_SIZE, fd);
		sscanf(temp, "%s", list[line]);
		line++;
	}
}

static int	check_change(char *str)
{
	int	found = 0;
	int	comp1 = 0;
	int	comp2 = 1;
	int	len;

	len = ft_strlen(str);
	while (comp1 < len && comp2 < len)
	{
		while (str[comp1] == 'A' || str[comp2] == 'A' )
		{
			if (str[comp1] == 'A')
				comp1++;
			if (str[comp2] == 'A')
				comp2++;
			if (comp1 == comp2)
				comp2++;
		}
		if (str[comp1] == '(' && str[comp2] == ')')
		{
			str[comp1] = 'A';
			str[comp2] = 'A';
			found++;
		}
		if (str[comp1] == '[' && str[comp2] == ']')
		{
			str[comp1] = 'A';
			str[comp2] = 'A';
			found++;
		}
		if (str[comp1] == '{' && str[comp2] == '}')
		{
			str[comp1] = 'A';
			str[comp2] = 'A';
			found++;
		}
		if (str[comp1] == '<' && str[comp2] == '>')
		{
			str[comp1] = 'A';
			str[comp2] = 'A';
			found++;
		}
		comp1++;
		comp2++;
	}
	// printf("%d\n", found);
	return (found);
}

static int	calc(char *str)
{
	size_t	i = 0;
	int		score = 0;

	while (i < LINE_SIZE)
	{
		if (str[i] == ')')
			return (3);
		else if (str[i] == ']')
			return (57);
		else if (str[i] == '}')
			return (1197);
		else if (str[i] == '>')
			return (25137);
		i++;
	}
}

static int	check_valid(char *str)
{
	size_t	i = 0;

	while (str[i])
	{
		if (str[i] == ')' || str[i] == '}' || str[i] == ']' || str[i] == '>')
			return (1);
		i++;
	}
	return (0);
}

static void	check_list(char **list)
{
	size_t	line = 0;
	int		score = 0;

	while (line < LINES)
	{
		while (check_change(list[line]))
		{}
		if (check_valid(list[line]))
			score += calc(list[line]);
		line++;
	}
	printf("%d\n", score);
}


static int	read_instruct(FILE *fd)
{
	char	**list;

	list = create_list();
	fill_list(list, fd);
	check_list(list);
}

int	main(void)
{
	FILE	*fd;

	fd = fopen("inputJ.txt", "r");
	read_instruct(fd);

	fclose(fd);
}
