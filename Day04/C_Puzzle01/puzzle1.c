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

void	printList(t_list *n)
{
	int	i = 0;
	int	j = 0;

	while (n != NULL)
	{
		while (i < 25)
		{
			printf("%d: %d\n", j + 1, ((int *)n->content)[i]);
			i++;
			j++;
		}
		i = 0;
		n = n->next;
	}
}

// t_list	*list_fill(void *array)
// {
// 	t_list	*list = NULL;
// 	t_list	*start = NULL;
// 	int		i;

// 	i = 0;
// 	while (array)
// 	{
// 		if (!list)
// 		{
// 			ft_lstadd_back(&list, ft_lstnew(array));
// 			start = list;
// 		}
// 		else
// 			ft_lstadd_back(&list, ft_lstnew(array));
// 		i++;
// 	}
// 	return (start);
// }

int	read_instruct(FILE *fd)
{
	char		input_read[104];
	char		board_read[77];
	int			board_num[25];
	t_list		*num = NULL;
	size_t		b_read;
	size_t		i = 0;
	size_t		j = 0;
	size_t		count = 0;

	b_read = 1;
	fgets(input_read, 103, fd);
	input_read[103] = '\0';
	while (b_read >= 1)
	{
		b_read = fread(board_read, 1, 76, fd);
		board_read[76] = '\0';
		while (board_read[j] != '\0' && count < 3)
		{
			board_num[i] = ft_atoi(&board_read[j]);
			i++;
			j += 3;
			ft_lstadd_back(&num, ft_lstnew(board_num));
			count++;
		}
		i = 0;
		j = 0;
	}
	// printf("%d\n", count);
	printList(num);
	return (0);
}

int	main(void)
{
	FILE	*fd;

	fd = fopen("test.txt", "r");
	read_instruct(fd);
	fclose(fd);
}
