#include "header.h"

/*

ROW 1: 0, 1, 2, 3, 4
ROW 2: 5, 6, 7, 8, 9
ROW 3: 10, 11, 12, 13, 14
ROW 4: 15, 16, 17, 18, 29
ROW 5: 20, 21, 22, 23, 24

COL 1: 0, 5, 10, 15, 20
COL 2: 1, 6, 11, 16, 21
COL 3: 2, 7, 12, 17, 22
COL 4: 3, 8, 13, 18, 23
COL 5: 4, 9, 14, 19, 24

1. Make array with input numbers
2. Make list of boards
3. Input number in boards
4. Check boards for completion
*/

t_list	*list_fill(char **array)
{
	t_list	*list = NULL;
	t_list	*start = NULL;
	int		i;

	i = 0;
	while (array[i])
	{
		if (!list)
		{
			ft_lstadd_back(&list, ft_lstnew(array[i]));
			start = list;
		}
		else
			ft_lstadd_back(&list, ft_lstnew(array[i]));
		i++;
	}
	return (start);
}

// int	read_instruct(FILE *fd)
// {
// 	char	input_temp[104];
// 	char	board_temp[77];
// 	int		b_read;
// 	size_t		i = 0;

// 	b_read = 1;
// 	fgets(input_temp, 103, fd);
// 	fread(board_temp, 1, 76, fd);
// 	input_temp[103] = '\0';
// 	board_temp[76] = '\0';
// 	printf("input: %s\n", input_temp);
// 	printf("input: %s\n", board_temp);

// 	fread(board_temp, 1, 76, fd);
// 	printf("input: %s\n", board_temp);
// 	return (0);
// }

int	read_instruct(FILE *fd)
{
	char	input_temp[104];
	char	board_temp[77];
	int		b_read;
	size_t		i = 0;

	b_read = 1;
	fgets(input_temp, 103, fd);
	input_temp[103] = '\0';
	while (b_read > 1)
	{
		fread(board_temp, 1, 76, fd);
		board_temp[76] = '\0';
		
	}
	return (0);
}

int	main(void)
{
	FILE	*fd;

	fd = fopen("test.txt", "r");
	read_instruct(fd);
	fclose(fd);
}
