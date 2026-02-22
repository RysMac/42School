/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrys <mrys@student.42warsaw.pl>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 12:33:16 by mrys              #+#    #+#             */
/*   Updated: 2026/02/22 12:33:50 by mrys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	skip_comment(char *line)
{
	char	*comment;

	comment = ft_strchr(line, '#');
	if (comment)
		*comment = '\0';
}

static void	handle_ambient(char **split, t_scene *scene, int *has_a);
static void	handle_camera(char **split, t_scene *scene, int *has_c);
static void	handle_light(char **split, t_scene *scene, int *has_l);

void	parse_line(char *line, t_scene *scene, int *has_a, int *has_c, int *has_l)
{
	char	**split;

	skip_comment(line);
	split = ft_split(line, ' ');
	if (!split || !split[0])
	{
		ft_free_tab(split);
		return ;
	}
	if (ft_strncmp(split[0], "A", 2) == 0)
		handle_ambient(split, scene, has_a);
	else if (ft_strncmp(split[0], "C", 2) == 0)
		handle_camera(split, scene, has_c);
	else if (ft_strncmp(split[0], "L", 2) == 0)
		handle_light(split, scene, has_l);
	else if (ft_strncmp(split[0], "sp", 3) == 0)
		parse_sphere(split, scene);
	else if (ft_strncmp(split[0], "pl", 3) == 0)
		parse_plane(split, scene);
	else if (ft_strncmp(split[0], "cy", 3) == 0)
		parse_cylinder(split, scene);
	else
		exit_error("Unknown element type");
	ft_free_tab(split);
}

static void	handle_ambient(char **split, t_scene *scene, int *has_a)
{
	if (*has_a)
		exit_error("Duplicate ambient lighting");
	parse_ambient(split, scene);
	*has_a = 1;
}

static void	handle_camera(char **split, t_scene *scene, int *has_c)
{
	if (*has_c)
		exit_error("Duplicate camera");
	parse_camera(split, scene);
	*has_c = 1;
}

static void	handle_light(char **split, t_scene *scene, int *has_l)
{
	if (*has_l)
		exit_error("Duplicate light");
	parse_light(split, scene);
	*has_l = 1;
}
