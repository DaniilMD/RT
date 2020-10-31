#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	char	*tmp;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	tmp = ft_strnew(len + 1);
	if (!tmp)
		return (NULL);
	ft_strcat(tmp, (char*)s1);
	ft_strcat(tmp, (char*)s2);
	return (tmp);
}
