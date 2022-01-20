#include "header.h"

int main(int argc, char const *argv[])
{
	t_dlist	*list;
	t_dlist	*temp;

	list = ft_dlstnew("start");
	ft_dlstadd_back(&list, ft_dlstnew("b"));
	// list = ft_dlstfirst(list);
	// while (list->next)
	// {
	// 	if (ft_strncmp(list->content, "this is THE string!", 20) == 0)
	// 		ft_dlstinsert_after(list, ft_dlstnew("insert!"));
	// 	list = list->next;
	// }
	// list = ft_dlstfirst(list);
	temp = list;
	while (list != NULL)
	{
		if (ft_strncmp(list->content, "b", 2) == 0)
		{
			printf("yes");
			ft_dlstdel_node(&list, list);
			break ;
		}
		list = list->next;
	}

	ft_printdlist(temp);
}
