/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrys <mrys@student.42warsaw.pl>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 15:56:09 by mrys              #+#    #+#             */
/*   Updated: 2024/12/29 15:56:09 by mrys             ###   ########.fr       */
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
