#include "header.h"

/*
10 lines
14 words
7 characters
*/

static char	***create_list(void)
{
	size_t	line = 0;
	size_t	word = 0;
	char	***list;

	list = (char ***)ft_calloc(LINES + 1, sizeof(char **));
	list[LINES] = '\0';
	while (line < LINES)
	{
		list[line] = (char **)ft_calloc(14 + 1, sizeof(char *));
		list[line][14] = '\0';
		while (word < 14)
		{
			list[line][word] = (char *)ft_calloc(7 + 1, sizeof(char));
			word++;
		}
		word = 0;
		line++;
	}
	return (list);
}

static int	**create_num_array(void)
{
	size_t	line = 0;
	int		**array;

	array = (int **)ft_calloc(LINES, sizeof(int *));
	while (line < LINES)
	{
		array[line] = (int *)ft_calloc(4, sizeof(int));
		line++;
	}
	return (array);
}

static void	fill_list(char ***list, FILE *fd)
{
	size_t	line = 0;
	size_t	word = 0;
	size_t	c = 0;
	size_t	i = 0;
	char	temp[LINE_SIZE];

	while (line < LINES)
	{
		fgets(temp, LINE_SIZE, fd);
		sscanf(temp, "%s %s %s %s %s %s %s %s %s %s %*c %s %s %s %s",
				list[line][0], list[line][1], list[line][2], list[line][3],
				list[line][4], list[line][5], list[line][6], list[line][7],
				list[line][8], list[line][9], list[line][10], list[line][11],
				list[line][12], list[line][13]);
		line++;
	}
}

static char	*find_S1(char **list)
{
	size_t	word = 0;
	char *S1 = (char *)ft_calloc(3, sizeof(char));

	while (ft_strlen(list[word]) != 2)
		word++;
	S1 = list[word];
	return (S1);
}

static char	*find_S2(char *S1, char **list)
{
	size_t	word = 0;
	size_t	i = 0;
	size_t	j = 0;
	char *S2 = (char *)ft_calloc(3, sizeof(char));

	while (ft_strlen(list[word]) != 4)
		word++;
	while (list[word][i])
	{
		if (list[word][i] != S1[0] && list[word][i] != S1[1])
		{
			S2[j] = list[word][i];
			j++;
		}
		i++;
	}
	return (S2);
}

static char	*find_S0(char *S1, char **list)
{
	size_t	word = 0;
	size_t	i = 0;
	size_t	j = 0;
	char *S0 = (char *)ft_calloc(2, sizeof(char));

	while (ft_strlen(list[word]) != 3)
		word++;
	while (list[word][i])
	{
		if (list[word][i] != S1[0] && list[word][i] != S1[1])
		{
			S0[j] = list[word][i];
			j++;
		}
		i++;
	}
	return (S0);
}

static char	*find_S3(char *S0, char *S1, char *S2, char **list)
{
	size_t	word = 0;
	size_t	i = 0;
	size_t	j = 0;
	char *S3 = (char *)ft_calloc(3, sizeof(char));

	while (ft_strlen(list[word]) != 7)
		word++;
	// printf("%s", list[word]);
	while (list[word][i])
	{
		if (list[word][i] != S1[0] && list[word][i] != S1[1] && 
		list[word][i] != S2[0] && list[word][i] != S2[1] && 
		list[word][i] != S0[0])
		{
			S3[j] = list[word][i];
			j++;
		}
		i++;
	}
	return (S3);
}

static int	search(char *list, char *S)
{
	size_t	word = 0;
	size_t	i = 0;
	size_t	count = 0;

	while (list[i])
	{
		if (list[i] == S[0] || list[i] == S[1])
			count++;
		i++;
	}
	if (count == 2)
		return (1);
	else
		return (0);
}

static void	decode_input(char ***list, int **array)
{
	size_t	line = 0;
	size_t	word = 0;
	size_t	num = 0;
	char	*S0;
	char	*S1;
	char	*S2;
	char	*S3;

	//== DEBUG ==//
	// S1 = find_S1(list[word]);
	// S0 = find_S0(S1, list[word]);
	// S2 = find_S2(S1, list[word]);
	// S3 = find_S3(S0, S1, S2, list[word]);

	// word = 12;
	// line = 2;
	// while (num < 1)
	// {
	// 	if (ft_strlen(list[line][word]) == 6 && !(search(list[line][word], S2)) && search(list[line][word], S3))
	// 		array[0][0] = 6;
	// // 		else if (ft_strlen(list[line][word]) == 6 && search(list[line][word], S2) && search(list[line][word], S1))
	// // 			array[line][num] = 9;
	// 	// word++;
	// 	num++;
	// }
	// printf("Current wordcount: %d\n", word);
	// printf("Current wordcount: %d\n", search(list[line][word], S2));
	// printf("Current wordcount: %d\n", search(list[line][word], S3));
	// printf("Current word: %s\n", list[line][word]);
	// printf("\nSegments: \n");
	// printf("S0: %s\n", S0);
	// printf("S1: %s\n", S1);
	// printf("S2: %s\n", S2);
	// printf("S3: %s\n", S3);
	// printf("Array number: %d\n", array[0][0]);
	// printf("Array number: %d\n", array[line][num - 2]);
	// while (line < LINES)
	{
		S1 = find_S1(list[line]);
		S0 = find_S0(S1, list[line]);
		S2 = find_S2(S1, list[line]);
		S3 = find_S3(S0, S1, S2, list[line]);
		word = 10;
		while (num < 4)
		{
			if (ft_strlen(list[line][word]) == 6 && search(list[line][word], S1) && search(list[line][word], S3))
				array[line][num] = 0;
			else if (ft_strlen(list[line][word]) == 2)
				array[line][num] = 1;
			else if (ft_strlen(list[line][word]) == 5 && search(list[line][word], S3))
				array[line][num] = 2;
			else if (ft_strlen(list[line][word]) == 5 && search(list[line][word], S1))
				array[line][num] = 3;
			else if (ft_strlen(list[line][word]) == 4)
				array[line][num] = 4;
			else if (ft_strlen(list[line][word]) == 5 && search(list[line][word], S2))
				array[line][num] = 5;
			else if (ft_strlen(list[line][word]) == 6 && search(list[line][word], S2) == 1 && search(list[line][word], S3) == 1)
				array[line][num] = 6;
			else if (ft_strlen(list[line][word]) == 3)
				array[line][num] = 7;
			else if (ft_strlen(list[line][word]) == 7)
				array[line][num] = 8;
			else if (ft_strlen(list[line][word]) == 6 && search(list[line][word], S2) && search(list[line][word], S1))
				array[line][num] = 9;
			word++;
			num++;
		}
		word = 0;
		num = 0;
		line++;
	}
}

static void count_part1(int **array)
{
	size_t	line = 0;
	size_t	entry = 0;
	size_t	count = 0;

	while (line < LINES)
	{
		while (entry < 4)
		{
			if (array[line][entry] == 1 || 
				array[line][entry] == 4 || 
				array[line][entry] == 7 || 
				array[line][entry] == 8 )
				count++;
			printf("%d ", array[line][entry]);
			entry++;
		}
		entry = 0;
		line++;
		printf("\n");
	}
	printf("%d\n", count);
}

int	read_instruct(FILE *fd)
{
	char	***list;
	int		**array;
	size_t	line = 0;

	
	list = create_list();
	array = create_num_array();
	fill_list(list, fd);
	// printf("%d", search(list[2][2], "cg"));
	decode_input(list, array);
	// printf("%d\n", array[2][2]);
	// printf("%s\n", list[1][11]);
	// count_part1(array);
	// count_part1(array);
	return (0);
}

int	main(void)
{
	FILE	*fd;

	fd = fopen("test.txt", "r");
	read_instruct(fd);

	fclose(fd);
}