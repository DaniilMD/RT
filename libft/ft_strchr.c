#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int i;

	i = 0;
	while (s[i] != '\0')
	{
		if ((unsigned char)c == s[i])
			return ((char*)s + i);
		i++;
	}
	if ((unsigned char)c == '\0')
		return ((char*)s + i);
	return (NULL);
}
