#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*elem;
	t_list	*head;

	if (lst != NULL)
	{
		head = *lst;
		while (head != NULL)
		{
			elem = head;
			head = head->next;
			if (del != NULL)
				del(elem->content);
			if (elem != NULL)
				free(elem);
		}
		*lst = NULL;
	}
}
