#include "libft.h"

static int	simil_checker(const char *str, const char *find, int counter2)
{
	int counter;
	int indic;

	indic = 0;
	counter = 0;
	while ((str[counter2] != '\0') && (find[counter] != '\0'))
	{
		if (str[counter2] != find[counter])
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

char		*ft_strstr(const char *str, const char *to_find)
{
	int	indx;

	indx = 0;
	if (to_find[0] == '\0')
		return ((char*)str);
	while (str[indx] != '\0')
	{
		if (str[indx] == to_find[0])
		{
			if (simil_checker(str, to_find, indx) != 1)
				return ((char*)str + indx);
		}
		indx++;
	}
	return (0);
}
