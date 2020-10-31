#include "libft.h"

void	ft_list_sort(t_list **begin_list, int (*cmp)())
{
	t_list	*tmp;
	t_list	*next_n;
	void	*sw;
	size_t	sz;

	tmp = *begin_list;
	if (tmp)
		while (tmp)
		{
			next_n = tmp->next;
			while (next_n)
			{
				if (cmp(tmp->content, next_n->content) > 0)
				{
					sw = tmp->content;
					sz = tmp->content_size;
					tmp->content = next_n->content;
					tmp->content_size = next_n->content_size;
					next_n->content = sw;
					next_n->content_size = sz;
				}
				next_n = next_n->next;
			}
			tmp = tmp->next;
		}
}
