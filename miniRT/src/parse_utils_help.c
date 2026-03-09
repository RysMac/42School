/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_help.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrys <mrys@student.42warsaw.pl>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 18:01:33 by mrys              #+#    #+#             */
/*   Updated: 2026/02/28 18:35:20 by mrys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include <math.h>

int	is_number(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]) && s[i] != '.')
			return (0);
		i++;
	}
	return (1);
}

void	skipper(const char *str, int *i, int *sign, double *result)
{
	while (str[*i] == ' ' || (str[*i] >= '\t' && str[*i] <= '\r'))
		(*i)++;
	if (str[*i] == '-')
	{
		*sign = -1;
		(*i)++;
	}
	else if (str[*i] == '+')
		(*i)++;
	while (ft_isdigit(str[*i]))
	{
		*result = *result * 10.0 + (str[*i] - '0');
		(*i)++;
	}
}

double	parse_double_internal(const char *str)
{
	double	result;
	double	fraction;
	int		sign;
	int		i;

	result = 0.0;
	fraction = 0.1;
	sign = 1;
	i = 0;
	skipper(str, &i, &sign, &result);
	if (str[i] == '.')
	{
		i++;
		while (ft_isdigit(str[i]))
		{
			result += (str[i] - '0') * fraction;
			fraction *= 0.1;
			i++;
		}
	}
	return (result * sign);
}

double	parse_double(char *s)
{
	if (!is_number(s))
		exit_error("Invalid number format");
	return (parse_double_internal(s));
}
