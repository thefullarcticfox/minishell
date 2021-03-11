#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*elem;

	elem = lst;
	while (elem != NULL && f != NULL)
	{
		(*f)(elem->content);
		if (elem->next == NULL)
			break ;
		elem = elem->next;
	}
}
