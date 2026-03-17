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
	void	*m_ptr;

	m_ptr = (void *)malloc(nmemb * size);
	if (!m_ptr)
		return (NULL);
	ft_bzero(m_ptr, nmemb * size);
	return (m_ptr);
}
