#include "libft.h"
#define MAIN_LONG_MAX ((unsigned long)(~0L))
#define M_LONG_MAX ((long)(MAIN_LONG_MAX >> 1))
#define M_LONG_MIN ((long)(~M_LONG_MAX))

static int	maxchecks(long long res, const char *str, int i, int indic)
{
	long long	brd;

	brd = M_LONG_MAX / 10;
	if ((res > brd || (res == brd && (str[i] - '0') > 7)) && indic == 0)
		return (-1);
	if ((res > brd || (res == brd && (str[i] - '0') > 8)) && indic == 1)
		return (0);
	return (1);
}

int			ft_atoi(const char *str)
{
	int			i;
	long long	res;
	int			indic;

	indic = 0;
	i = 0;
	res = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
	|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
		indic = 1;
	else if (str[i] == '+')
		i++;
	if (indic)
		i++;
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		if (maxchecks(res, str, i, indic) != 1)
			return (maxchecks(res, str, i, indic));
		res = res * 10 + (str[i++] - 48);
	}
	if (indic == 1)
		res *= -1;
	return ((int)res);
}
