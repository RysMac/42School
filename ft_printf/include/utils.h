#ifndef UTILS_H
# define UTILS_H

#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>

int	ft_putchar(char c);
int	ft_putstr(char *str);
int	ft_putnbr(int n);
int	ft_putunsigned(unsigned int n);
int	ft_putnbrhex(int n, char a);
int	ft_putptr(void *);
int	ft_printf(const char *, ...);

#endif
