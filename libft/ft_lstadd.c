#include "libft.h"

void	ft_lstadd(t_list **alst, t_list *new)
{
	if (!alst || !new)
		return ;
	else
	{
		new->next = *alst;
		*alst = new;
	}
}
