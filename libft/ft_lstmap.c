#include "libft.h"

static t_list	*clear_lst(t_list *lst)
{
	t_list *tmp;

	while (lst)
	{
		tmp = lst;
		free(lst->content);
		free(lst);
		lst = tmp->next;
	}
	return (NULL);
}

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *tmp;
	t_list *new;
	t_list *res;
	t_list *begin;

	tmp = lst;
	if (!tmp || !f)
		return (NULL);
	res = f(tmp);
	new = ft_lstnew(res->content, res->content_size);
	if (!new)
		return (NULL);
	tmp = tmp->next;
	begin = new;
	while (tmp)
	{
		res = f(tmp);
		new->next = ft_lstnew(res->content, res->content_size);
		if (!new->next)
			return (clear_lst(begin));
		new = new->next;
		tmp = tmp->next;
	}
	return (begin);
}
