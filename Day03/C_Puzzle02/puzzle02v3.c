#include "header.h"

void	printList(t_list *n)
{
	while (n != NULL)
	{
		printf("%s\n", n->content);
		n = n->next;
	}
}

void	comb_list(t_list *list)
{
	t_list	*start = NULL;
	start = list;
	while (list)
	{
		if (((char *)list->content)[0] == 0)
			ft_lstdelone(list, free);
		list = list->next;
	}
	printList(start);
}

int	count_num(t_list *list)
{
	int	num1;
	int	num2;
	int	i;

	num1 = 0;
	num2 = 0;
	i = 0;
	while (list)
	{
		if (((char *)list->content)[i] == '0')
			num1++;
		else
			num2++;
		list = list->next;
	}
	if (num1 <= num2)
		return (1);
	else
		return (0);
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
	char	temp[10000];

	read(fd, temp, 10000);
	list1 = list_fill(ft_split(temp, '\n'));
	list2 = list_fill(ft_split(temp, '\n'));
	// count_num(list1);
	// comb_list(list1);
	printList(list1);
	// printList(list2);
	return (0);
}

int	main(void)
{
	int	fd;

	fd = open("test.txt", O_RDONLY);
	read_instruct(fd);
	close(fd);
}
