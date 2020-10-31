#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*tmp;

	if (size + 1 == 0)
		return (NULL);
	tmp = (char*)malloc((size + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	ft_memset(tmp, '\0', size + 1);
	return (tmp);
}
