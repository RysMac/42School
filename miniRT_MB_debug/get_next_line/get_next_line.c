/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mr <mr@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 23:10:13 by mr                #+#    #+#             */
/*   Updated: 2025/04/23 15:16:48 by mr               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*line; // whole line must be returned so no need to be static
	static char	*temp; // part of the text which left from buffer
	char		buffer[BUFFER_SIZE + 1];
	ssize_t		bytes_read;
	size_t		position;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	if (temp)
	{
		line = ft_strdup_gnl(temp, 0, ft_strlen(temp));
		free(temp);
		temp = NULL;
	}
	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(line);
			return (NULL);
		}
		if (bytes_read == 0)
			break;
		buffer[bytes_read] = '\0';
		line = ft_join_and_free(line, buffer);

		if (ft_strlen_end_line(buffer, &position) == 1 || bytes_read == 0)
		{
			temp = ft_strdup_gnl(buffer, position, BUFFER_SIZE);
			return (line);
		}
	}
	return (line);
}
