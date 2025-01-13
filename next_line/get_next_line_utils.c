/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mr <mr@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:28:10 by mr                #+#    #+#             */
/*   Updated: 2025/01/13 13:26:13 by mr               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	line_counts(char *buffer)
{
	size_t	i;

	i = 0;
	while (buffer[i] != '\n')
		i++;
	return (i);
}
