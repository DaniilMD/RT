#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int indicator;
	int razr;

	razr = 1000000000;
	if (n == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	if (n < 0)
	{
		n *= -1;
		ft_putchar_fd('-', fd);
	}
	indicator = 0;
	while (razr)
	{
		if (n / razr % 10)
			indicator = 1;
		if (indicator)
			ft_putchar_fd(n / razr % 10 + '0', fd);
		razr /= 10;
	}
	if (n == 0)
		ft_putchar_fd('0', fd);
}
