/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrys <mrys@student.42warsaw.pl>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 10:49:56 by mrys              #+#    #+#             */
/*   Updated: 2026/02/08 17:08:54 by mrys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_and_process(int fd, char **temp, char *line)
{
	char	buffer[BUFFER_SIZE + 1];
	ssize_t	bytes_read;
	size_t	position;

	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(line), NULL);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		line = ft_join_and_free(line, buffer);
		if (ft_strlen_end_line(buffer, &position))
		{
			*temp = ft_strdup_gnl(buffer, position, BUFFER_SIZE);
			return (line);
		}
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*temp;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	if (temp)
	{
		line = ft_strdup_gnl(temp, 0, ft_strlen(temp));
		free(temp);
		temp = NULL;
	}
	return (read_and_process(fd, &temp, line));
}
