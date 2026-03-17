#include "libft.h"

int	ft_atoi(const char *str)
{
	size_t	i;
	int		sign;
	int		nbr;

	i = 0;
	while (str[i] == 32 || str[i] == 9 || str[i] == 10 ||
			str[i] == 11 || str[i] == 12 || str[i] == 13)
			i++;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	nbr = 0;
	while ('0' <= str[i] && str[i] <= '9')
	{
		nbr = nbr * 10 + (str[i] - '0');
		i++;
	}
	return (sign * nbr);
}
