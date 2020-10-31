#include "libft.h"

void				*ft_dup(void const *content, size_t content_size)
{
	unsigned char	*ptr;
	unsigned char	*ptr2;
	void			*new;
	size_t			i;

	i = -1;
	if (!(new = ft_memalloc(content_size)))
		return (NULL);
	ptr = (unsigned char*)content;
	ptr2 = (unsigned char*)new;
	while (++i < content_size)
		ptr2[i] = ptr[i];
	return (new);
}
