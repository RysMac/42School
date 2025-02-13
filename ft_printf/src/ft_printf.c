#include "utils.h"

static int	identfier(char c, va_list arg)
{
	if (c == 'c')
		ft_putchar(va_arg(arg, int));
	else if (c == 's')
		ft_pustr(va_arg(arg, char *));
	else if (c == 'd' || c == 'i')
		ft_putnbr(va_arg(arg, int));
	else if (c == 'u')
		ft_putunsigned(va_arg(arg, int));
	else if (c == 'x')
		ft_putnbrhex(va_arg(arg, int), 'a');
	else if (c == 'X')
		ft_putnbrhex(va_arg(arg, int), 'A');
	else if (c == 'p')
	{
		write(1, "0x", 2);
		ft_putptr(va_arg(arg, void *));
	}
	else if (c == '%')
		ft_putchar('%');
	else
		return (0);
	return (1);
}


int	ft_printf(const char *format, ...)
{
	va_list args;
	int		id;

	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			id = identfier(*format, args);
			format++;
		}
		if (id == 0)
			return (0);
		ft_putchar(*format);
		format++;
	}
	va_end(args);
	return (1);
}
