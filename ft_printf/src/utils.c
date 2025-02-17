// two simple function just for testing

#include "ft_printf.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *str)
{
	int	count;

	count = 0;
	if (str == NULL)
	{
		ft_putstr("(null)");
		return (6);
	}
	if (!str)
		return (-1000000);
	while (*str)
	{
		count += ft_putchar(*str);
		str++;
	}
	return (count);
}

int	ft_putnbr(int n)
{
	long	nb;
	int		count;

	count = 0;
	nb = (long)n;
	if (n < 0)
	{
		write(1, "-", 1);
		nb *= -1;
		count += 1;
	}
	if (nb > 9)
		count += ft_putnbr(nb / 10);
	count += ft_putchar((nb % 10) + '0');
	return (count);
}

int	ft_putunsigned(unsigned int n)
{
	int	count;

	count = 0;
	if (n > 9)
		count += ft_putunsigned(n / 10);
	count += ft_putchar((n % 10) + '0');
	return (count);
}

int	ft_putnbrhex(int n, char a)
{
	unsigned int	nb;
	int 			count;

	count = 0;
	nb = (unsigned int)n;
	if (nb >= 16)
		count += ft_putnbrhex(nb / 16, a);
	if (nb % 16 < 10)
		count += ft_putchar((nb % 16) + '0');
	else
		count += ft_putchar((nb % 16) + a - 10);
	return (count);
}

int	ft_putptr(void *ptr)
{
	unsigned long int	num;
	int					count;

	if (!ptr)
	{
		ft_putstr("(nil)");
		return (5);
	}
	num = (unsigned long int)ptr;
	count = 0;
	if (num >= 16)
		count += ft_putptr((void *)(num / 16));
	if (num % 16 < 10)
		count += ft_putchar((num % 16) + '0');
	else
		count += ft_putchar((num % 16) + 'a' - 10);
	return (count);
}
