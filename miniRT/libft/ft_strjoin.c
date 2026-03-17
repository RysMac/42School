/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrys <mrys@student.42warsaw.pl>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 15:12:34 by mrys              #+#    #+#             */
/*   Updated: 2024/12/29 15:12:34 by mrys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*fill_ptr(char *ptr, char const *s, size_t start, size_t stop)
{
	size_t	i;

	i = 0;
	while (i < stop)
	{
		ptr[i + start] = s[i];
		i++;
	}
	return (ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*ptr;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ptr = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!ptr)
		return (NULL);
	fill_ptr(ptr, s1, 0, s1_len);
	fill_ptr(ptr, s2, s1_len, s2_len);
	ptr[s1_len + s2_len] = '\0';
	return (ptr);
}
