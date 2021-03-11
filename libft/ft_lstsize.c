#include "libft.h"

int		ft_lstsize(t_list *lst)
{
	t_list	*elem;
	int		size;

	size = 0;
	elem = lst;
	while (elem != NULL)
	{
		size++;
		elem = elem->next;
	}
	return (size);
}
