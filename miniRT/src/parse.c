/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrys <mrys@student.42warsaw.pl>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 12:42:26 by mrys              #+#    #+#             */
/*   Updated: 2026/03/03 12:56:07 by mrys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include <fcntl.h>
#include "../get_next_line/get_next_line.h"

// ft_bzero(&scene->camera, sizeof(t_camera)); - deleted
static void	init_scene(t_scene *scene)
{
	// ft_bzero(&scene->ambient, sizeof(t_ambient));
	// ft_bzero(&scene->light, sizeof(t_light));
	// ft_bzero(&scene->camera, sizeof(t_camera));
	// scene->w = 800;
	// scene->h = 100;
	scene->objects = NULL;
	scene->count = 0;
}

static int	has_valid_extension(const char *path)
{
	size_t	len;

	len = ft_strlen(path);
	if (len < 3)
		return (0);
	if (path[len - 3] != '.' || path[len - 2] != 'r' || path[len - 1] != 't')
		return (0);
	return (1);
}

static void	parse_line_helper(char *line, t_scene *scene, t_flags *flags)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] != '\0' && line[i] != '#')
		parse_line(line, scene, flags);
}

void	parse_file(const char *path, t_scene *scene)
{
	int		fd;
	char	*line;
	t_flags	flags;

	if (!has_valid_extension(path))
		exit_error("Invalid file extension (must be .rt)");
	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit_error("Cannot open file");
	init_scene(scene);
	flags.has_a = 0;
	flags.has_c = 0;
	flags.has_l = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		parse_line_helper(line, scene, &flags);
		free(line);
	}
	close(fd);
	if (!flags.has_a || !flags.has_c || !flags.has_l)
		exit_error("Missing required elements (A, C, L)");
}
