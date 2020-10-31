#include "libft.h"

float		ft_atof(char *str)
{
	float	res;
	float	mant;
	int		negative;
	int		div;

	negative = 1;
	res = 0;
	mant = 0;
	div = 10;
	while (*str && (*str == ' ' || *str == '\n' || *str == '\t' ||
			*str == '\v' || *str == '\f' || *str == '\r'))
		++str;
	if (*str == '-')
		negative = -1;
	if (*str == '-' || *str == '+')
		++str;
	while (*str && *str >= '0' && *str <= '9')
		res = res * 10 + (*str++ - 48);
	if (*str++ == '.')
		while (*str && *str >= '0' && *str <= '9' && div <= 10000)
		{
			mant += ((float)(*str++ - 48)) / div;
			div *= 10;
		}
	return (negative * (res + mant));
}
