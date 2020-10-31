#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t nb)
{
	int i;
	int k;

	i = 0;
	k = 0;
	while (dest[i] != '\0')
		i++;
	while ((src[k] != '\0') && (nb > 0))
	{
		dest[i] = src[k];
		i++;
		k++;
		nb--;
	}
	dest[i] = '\0';
	return (dest);
}
