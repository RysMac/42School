/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrys <mrys@student.42warsaw.pl>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 15:50:07 by mrys              #+#    #+#             */
/*   Updated: 2024/12/29 15:50:07 by mrys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_digits(unsigned int temp, int n)
{
	size_t	l;

	if (temp == 0)
		return (1);
	l = 0;
	while (temp > 0)
	{
		temp /= 10;
		l++;
	}
	if (n < 0)
		l += 1;
	return (l);
}

char	*ft_itoa(int n)
{
	int				l;
	unsigned int	n_copy;
	char			*ptr;

	if (n < 0)
		n_copy = (unsigned int)(-n);
	else
		n_copy = (unsigned int)(n);
	l = count_digits(n_copy, n);
	ptr = (char *)malloc(l + 1);
	if (!ptr)
		return (NULL);
	ptr[l] = '\0';
	while (--l >= 0)
	{
		if (n < 0 && l == 0)
			ptr[0] = '-';
		else
		{
			ptr[l] = (n_copy % 10) + '0';
			n_copy /= 10;
		}
	}
	return (ptr);
}
