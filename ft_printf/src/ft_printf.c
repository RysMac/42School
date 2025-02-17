#include "ft_printf.h"

static int	identifier(char c, va_list arg)
{
	int	count;

	count = 0;
	if (c == 'c')
		count += ft_putchar(va_arg(arg, int));
	else if (c == 's')
		count += ft_putstr(va_arg(arg, char *));
	else if (c == 'd' || c == 'i')
		count += ft_putnbr(va_arg(arg, int));
	else if (c == 'u')
		count += ft_putunsigned(va_arg(arg, int));
	else if (c == 'x')
		count += ft_putnbrhex(va_arg(arg, int), 'a');
	else if (c == 'X')
		count += ft_putnbrhex(va_arg(arg, int), 'A');
	else if (c == 'p')
	{
		void *p = va_arg(arg, void *);
		if (p)
			count += ft_putstr("0x");
		count += ft_putptr(p);
	}
	else if (c == '%')
		count += ft_putchar('%');
	else
		return (-1);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list args;
	int		count;

	if (!format)
		return (-1);
	count = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format != '%')
		{
			count += ft_putchar(*format);
			format++;
		}
		if (*format == '%')
		{
			format++;
			count += identifier(*format, args);
			if (count < 0)
				return (-1);
			format++;
		}
	}
	va_end(args);
	return (count);
}
