#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	t_list	*elem;

	if (lst != NULL)
	{
		elem = lst;
		lst = lst->next;
		if (del != NULL)
			del(elem->content);
		if (elem != NULL)
			free(elem);
	}
}
