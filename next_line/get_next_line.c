/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mr <mr@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 23:10:13 by mr                #+#    #+#             */
/*   Updated: 2025/01/13 14:38:59 by mr               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	int				i;
	int				j;
	static char		buffer[228];
	char			buffer_tmp[228];
	static	size_t 	buffer_pos = 0;
	static ssize_t	bytes_in_buffer = 0;
	char			*line;

	if (bytes_in_buffer == 0)
	{
		printf("%s\n", "reading fd");
		bytes_in_buffer = read(fd, buffer, sizeof(buffer));
	}

	i = 0;
	while (buffer_pos < bytes_in_buffer)
	{
		buffer_tmp[i] = buffer[buffer_pos];
		buffer_pos++;
		i++;
		if (buffer[buffer_pos] == '\n')
			break;
		if (buffer_pos == bytes_in_buffer)
		{
			bytes_in_buffer = read(fd, buffer, sizeof(buffer));
			buffer_pos = 0;
		}

	}

	line = (char *)malloc(sizeof(char) * (i + 1));
	j = 0;
	while (j < i)
	{
		line[j] = buffer_tmp[j];
		j++;
	}
	return (line);
}
