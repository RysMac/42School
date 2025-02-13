#ifndef UTILS_H
# define UTILS_H

#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>

void	ft_putchar(char c);
void	ft_pustr(char *str);
void	ft_putnbr(int n);
void	ft_putunsigned(int n);
void	ft_putnbrhex(int n, char a);
void	ft_putptr(void *);
int		ft_printf(const char *, ...);

#endif
