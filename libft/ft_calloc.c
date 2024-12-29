/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mr <mr@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 21:47:48 by mr                #+#    #+#             */
/*   Updated: 2024/12/27 21:47:48 by mr               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	total_size;
	void	*m_ptr;

	total_size = nmemb * size;
	m_ptr = malloc(total_size);
	if (!m_ptr)
		return (NULL);
	ft_bzero(m_ptr, total_size);
	return (m_ptr);
}
