#include "header.h"

void	printList(t_list *n)
{
	int	i = 0;

	while (n != NULL)
	{
		printf("%d: %s\n", i, n->content);
		n = n->next;
		i++;
	}
}

void	comb_list(t_list *list, int i, char num)
{
	t_list	*start = NULL;
	int	j = 0;

	start = list;
	while (list)
	{
		if (((char *)list->content)[i] == num)
		{
			j = 0;
			while (((char *)list->content)[j])
			{
				((char *)list->content)[j] = 'X';
				j++;
			}
		}
		list = list->next;
	}
	// printList(start);
}

char	count_num(t_list *list, int i)
{
	int	num1;
	int	num2;

	num1 = 0;
	num2 = 0;
	while (list)
	{
		while (((char *)list->content)[0] == 'X' && list->next != NULL)
			list = list->next;
		if (((char *)list->content)[i] == '0')
			num1++;
		else if (((char *)list->content)[i] == '1')
			num2++;
		list = list->next;
	}
	printf("iteration: %d\n", i);
	printf("num1: 	%d\n", num1);
	printf("num2: 	%d\n", num2);
	if (num1 < 1 || num2 < 1)
		return ('2');
	if (num1 <= num2)
		return ('1');
	return ('0');
}

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

int	read_instruct(int fd)
{
	t_list	*list1;
	t_list	*list2;
	char	temp[20000];
	int		i;

	i = 0;
	read(fd, temp, 20000);
	list1 = list_fill(ft_split(temp, '\n'));
	while (((char *)list1->content)[i] && count_num(list1, i) != '2')
	{
		comb_list(list1, i, count_num(list1, i));
		i++;
	}
	i = 0;
	while (list1)
	{
		while (((char *)list1->content)[i] != 'X' && ((char *)list1->content)[i])
			i++;
		if (((char *)list1->content)[i] == '\0')
			printf("Answer: %s\n", list1->content);
		i = 0;
		list1 = list1->next;
	}
	return (0);
}

int	main(void)
{
	int	fd;

	fd = open("input.txt", O_RDONLY);
	read_instruct(fd);
	close(fd);
}

// number 1: 010101101111 1391
// number 2: 100110010111 2455