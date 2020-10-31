#include "libft.h"

static int	simil_nchecker(const char *str,
	const char *find, size_t counter2, size_t len)
{
	size_t counter;
	size_t indic;

	indic = 0;
	counter = 0;
	while ((str[counter2] != '\0') && (find[counter] != '\0'))
	{
		if (str[counter2] != find[counter] || counter2 >= len)
		{
			indic = 1;
			break ;
		}
		counter2++;
		counter++;
		if ((str[counter2] == '\0') && (find[counter] != '\0'))
			return (1);
	}
	return (indic);
}

char		*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	indx;

	indx = 0;
	if (to_find[0] == '\0')
		return ((char*)str);
	while (str[indx] != '\0' && indx < len)
	{
		if (str[indx] == to_find[0])
		{
			if (simil_nchecker(str, to_find, indx, len) != 1)
				return ((char*)str + indx);
		}
		indx++;
	}
	return (0);
}
