/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mr <mr@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 22:40:21 by mr                #+#    #+#             */
/*   Updated: 2024/12/27 22:40:21 by mr               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
/**
 * Function Name: ft_split
 * Description:
 *     Splits a given string `s` into an array of strings using a specified
 *     delimiter `c`. Each word is stored as a separate string in the array.
 *     The array is null-terminated (last pointer is NULL).
 *
 * Parameters:
 *     - s (const char *): The input string to split.
 *     - c (char): The delimiter character used to split the string.
 *
 * Return Value:
 *     Returns a pointer to an array of strings (char **), where each string
 *     is a word from the input string. If the allocation fails, returns NULL.
 */
char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	start;
	size_t	w;
	size_t	word_count;
	char	**ptr;

	if (!s)
		return (NULL);
	i = 0;
	word_count = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			word_count++;
		i++;
	}
	printf("words = %ld\n", word_count);
	ptr = (char **)ft_calloc(word_count + 1, sizeof(char *));
	if (!ptr)
		return (NULL);
	i = 0;
	start = 0;
	w = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			start = i;
			while (s[i] != c && s[i])
				i++;
			printf("word length = %ld\n", i - start);
			ptr[w] = (char *)ft_calloc(i - start + 1, sizeof(char *));
			if (!ptr[w])
				return (NULL);
			ft_strlcpy(ptr[w], &s[start], i - start + 1);
			w++;
		}
		else
			i++;
	}
	ptr[w] = NULL;
	return (ptr);
}
