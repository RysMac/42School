/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mr <mr@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:28:10 by mr                #+#    #+#             */
/*   Updated: 2025/04/23 15:16:06 by mr               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *ft_strdup_gnl(const char *str, size_t start, size_t finish)
{
	size_t	len;
	size_t	i;
	char	*ptr;


	if (!str)
		return (NULL);
	len = finish - start;
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < len)
	{
			ptr[i] = str[i + start];
			i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_join_and_free(char *text, char *buffer)
{
	char	*temp;

	temp = ft_strjoin(text, buffer);
	free(text);
	return (temp);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;
	char	*ptr;

	if (!s1 && !s2)
		return (NULL);


	s1_len = ft_strlen(s1);
	ft_strlen_end_line(s2, &s2_len);
	ptr = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!ptr)
			return (NULL);
	i = 0;
	while (i < s1_len)
	{
			ptr[i] = s1[i];
			i++;
	}
	i = 0;
	while (i < s2_len)
	{
			(ptr + s1_len)[i] = s2[i];
			i++;
	}
	(ptr + s1_len)[i] = '\0';
	return (ptr);
}

size_t	ft_strlen(char const *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

size_t	ft_strlen_end_line(const char *str, size_t *length)
{
	size_t	i;

	*length = 0;
	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\n')
		{
			*length = i + 1;
			return (1);
		}
		i++;
	}
	*length = i;
	return (0);
}
