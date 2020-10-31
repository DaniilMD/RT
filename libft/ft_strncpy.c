#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;
	int		ind;

	ind = 0;
	i = 0;
	while (i < len)
	{
		if (src[i] == '\0')
			ind = 1;
		if (ind != 1)
			dst[i] = src[i];
		else
			dst[i] = '\0';
		i++;
	}
	return (dst);
}
