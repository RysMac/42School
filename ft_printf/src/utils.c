// two simple function just for testing

#include "utils.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_pustr(char *str)
{
	while (*str)
	{
		ft_putchar(*str);
		str++;
	}
}

void	ft_putnbr(int n)
{
	long	nb;

	nb = n;
	if (n < 0)
	{
		write(1, "-", 1);
		nb *= -1;
	}
	if (nb > 9)
	{
		ft_putnbr(nb / 10);
		ft_putchar((nb % 10) + '0');
	}
	else
	{
		ft_putchar(nb + '0');
	}
}

void	ft_putunsigned(int n)
{
	unsigned int	nb;

	nb = (unsigned)n;
	if (nb > 9)
	{
		ft_putnbr(nb / 10);
		ft_putchar((nb % 10) + '0');
	}
	else
	{
		ft_putchar(nb + '0');
	}
}

void	ft_putnbrhex(int n, char a)
{
	unsigned int	nb;

	nb = (unsigned int)n;
	if (nb >= 16)
		ft_putnbrhex(nb / 16, a);
	if (nb % 16 < 10)
		ft_putchar((nb % 16) + '0');
	else
		ft_putchar((nb % 16) + a - 10);
}

void	ft_putptr(void *ptr)
{
	unsigned long int	num;

	num = (unsigned long int)ptr;
	if (num >= 16)
		ft_putptr((void *)(num / 16));
	if (num % 16 < 10)
		ft_putchar((num % 16) + '0');
	else
		ft_putchar((num % 16) + 'a' - 10);
}
