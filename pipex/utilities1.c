#include "pipex.h"

void ft_putchar(char c)
{
	write(1, &c, 1);
}

void ft_write(const char *str)
{
	while (*str)
	{
		ft_putchar(*str);
		str++;
	}
}

size_t ft_strlen(const char *str)
{
	size_t c;

	c = 0;
	while (str[c])
		c++;
	return (c);
}

int ft_strcomp(const char *str1, const char *str2, size_t n)
{
	size_t i;

	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i] && i < n)
	{
		i++;
	}
	if (i == n)
		return (1);
	return (0);
}

void	free_ptr(char **arr)
{
	int i = 0;
	if (!arr)
		return;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
