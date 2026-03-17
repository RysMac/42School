/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrys <mrys@student.42warsaw.pl>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 15:14:17 by mrys              #+#    #+#             */
/*   Updated: 2024/12/29 15:14:17 by mrys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*extract_word(char const *s, size_t *i, char c)
{
	size_t	start;

	start = *i;
	while (s[*i] && s[*i] != c)
		(*i)++;
	return (ft_substr(s, start, *i - start));
}

static size_t	fworld_count(char const *s, char c)
{
	size_t	word_count;
	size_t	i;

	i = 0;
	word_count = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			word_count++;
		i++;
	}
	return (word_count);
}

static void	zero_var(size_t *a, size_t *b)
{
	*a = 0;
	*b = 0;
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	w;
	char	**ptr;

	if (!s)
		return (NULL);
	ptr = (char **)ft_calloc(fworld_count(s, c) + 1, sizeof(char *));
	if (!ptr)
		return (NULL);
	zero_var(&i, &w);
	while (s[i])
	{
		if (s[i] != c)
		{
			ptr[w] = extract_word(s, &i, c);
			if (!ptr[w])
				return (NULL);
			w++;
		}
		else
			i++;
	}
	ptr[w] = NULL;
	return (ptr);
}
