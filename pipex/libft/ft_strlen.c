/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mr <mr@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 22:04:11 by mr                #+#    #+#             */
/*   Updated: 2024/12/27 22:04:11 by mr               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

size_t	ft_strlen(const char *str)
{
	size_t  c;
	printf("Path........stre....\n");
	if (!str)
		return (0);
	c = 0;
	while (str[c])
	{
		c++;
	}
	return  (c);
}
