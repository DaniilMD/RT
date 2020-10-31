#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*tmp;

	tmp = (void*)malloc(size * sizeof(void));
	if (!tmp)
		return (NULL);
	ft_bzero(tmp, size);
	return (tmp);
}
