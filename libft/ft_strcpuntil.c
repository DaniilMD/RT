#include "libft.h"

char	*ft_strcpuntil(char *s, char c)
{
	char		*out;
	size_t		len;

	if (!s)
		return (NULL);
	len = 0;
	while (s[len] != '\0' || s[len] != c)
		len++;
	if (!(out = (char *)malloc(sizeof(char) * (len + 1))))
		return (ft_strncpy(out, s, len));
	else
		return (NULL);
}
