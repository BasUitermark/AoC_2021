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

static unsigned long	calc_missing(char *str)
{
	int	i = ft_strlen(str);
	unsigned long		score = 0;

	// printf("Line: %s\n", str);
	while (i >= 0)
	{
		if (str[i] == '(')
		{
			score *= 5;
			score += 1;
		}
		if (str[i] == '[')
		{
			score *= 5;
			score += 2;
		}
		if (str[i] == '{')
		{
			score *= 5;
			score += 3;
		}
		if (str[i] == '<')
		{
			score *= 5;
			score += 4;
		}
		i--;
	}
	return (score);
}

static int cmpfunc( const void* a , const void* b )
{
	const unsigned long ai = *( const unsigned long* )a;
	const unsigned long bi = *( const unsigned long* )b;

	if( ai < bi )
	{
		return -1;
	}
	else if( ai > bi )
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

static void	print_scores(unsigned long *scores, int missing)
{
	size_t	i = 0;
	while (i < missing)
	{
		printf("%lu\n", scores[i]);
		i++;
	}
}

static void	check_list(char **list)
{
	size_t	line = 0;
	size_t	i = 0;
	int		missing = 0;
	unsigned long		*scores;

	while (line < LINES)
	{
		while (check_change(list[line]))
		{}
		// printf("Line #%d: %s\n", line + 1, list[line]);
		if (!check_valid(list[line]))
		{
			// printf("Line #%d: %s\n", line + 1, list[line]);
			missing++;
		}
		line++;
	}
	line = 0;
	scores = (unsigned long *)ft_calloc(missing, sizeof(unsigned long));
	while (line < LINES)
	{
		if (!check_valid(list[line]))
		{
			scores[i] = calc_missing(list[line]);
			i++;
		}
		line++;
	}
	qsort(scores, missing, sizeof(unsigned long), cmpfunc);
	print_scores(scores, missing);
	printf("Score: %lu\n", scores[(missing) / 2]);

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

	fd = fopen("input.txt", "r");
	read_instruct(fd);

	fclose(fd);
}
