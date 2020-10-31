#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*tmpd;
	unsigned char	*tmps;

	i = 0;
	tmpd = (unsigned char*)dst;
	tmps = (unsigned char*)src;
	while (i < n)
	{
		tmpd[i] = tmps[i];
		if (tmps[i] == (unsigned char)c)
			return ((void*)(tmpd + i + 1));
		if (i == n - 1)
			return (NULL);
		i++;
	}
	return (NULL);
}
