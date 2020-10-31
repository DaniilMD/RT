#include "libft.h"

char	*ft_itoa(int n)
{
	long long	ch;
	char		*str;
	int			cnt;
	int			sign;

	sign = (n < 0) ? -1 : 1;
	cnt = (n < 0) ? 2 : 1;
	ch = n;
	ch *= sign;
	while (ch /= 10)
		cnt++;
	str = ft_strnew(cnt);
	if (!str)
		return (NULL);
	str[0] = '0';
	ch = n;
	ch *= sign;
	while (ch > 0)
	{
		str[--cnt] = ('0' + (ch % 10));
		ch /= 10;
	}
	if (sign == -1)
		str[0] = '-';
	return (str);
}
