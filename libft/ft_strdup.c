#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*s;
	int		k;

	i = 0;
	while (s1[i] != '\0')
		i++;
	s = ft_strnew(i);
	if (!s)
		return (NULL);
	k = 0;
	while (k < i)
	{
		s[k] = s1[k];
		k++;
	}
	return (s);
}
