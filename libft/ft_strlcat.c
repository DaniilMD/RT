#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t k;
	size_t z;

	i = 0;
	k = 0;
	z = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (dst[i] != '\0' && i < size)
	{
		z++;
		i++;
	}
	while (i < size - 1 && src[k] != '\0')
	{
		dst[i] = src[k];
		i++;
		k++;
	}
	if (i < size)
		dst[i] = '\0';
	return (z + ft_strlen(src));
}
