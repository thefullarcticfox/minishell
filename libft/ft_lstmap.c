#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*elem;

	if (lst == NULL || f == NULL)
		return (NULL);
	elem = ft_lstnew(f(lst->content));
	if (elem == NULL)
		return (NULL);
	newlst = elem;
	while (lst->next != NULL)
	{
		lst = lst->next;
		elem->next = ft_lstnew(f(lst->content));
		if (elem->next == NULL)
		{
			ft_lstclear(&newlst, del);
			return (NULL);
		}
		elem = elem->next;
	}
	return (newlst);
}
