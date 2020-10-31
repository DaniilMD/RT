#include "libft.h"

void	ft_striter(char *s, void (*f)(char *))
{
	int i;

	i = 0;
	if (s == NULL || !f)
		return ;
	while (s[i] != '\0')
	{
		f(s + i);
		i++;
	}
}
