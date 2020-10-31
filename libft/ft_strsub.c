#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*tmp;

	if (!s)
		return (NULL);
	if (len + 1 == 0)
		return (NULL);
	tmp = (char*)malloc(sizeof(char) * (len + 1));
	if (!tmp)
		return (NULL);
	ft_strncpy(tmp, (s + start), len);
	tmp[len] = '\0';
	return (tmp);
}
