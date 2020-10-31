#include "libft.h"

int	ft_sqrt(int nb)
{
	int i;

	i = 0;
	if (nb <= 0)
		return (0);
	if (nb == 1)
		return (1);
	while (i <= nb / 2)
	{
		if (i == 46340)
			return (0);
		if (i * i > nb)
			return (0);
		else if (i * i == nb)
			return (i);
		i++;
	}
	return (0);
}
