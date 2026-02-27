/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrys <mrys@student.42warsaw.pl>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 12:26:40 by mrys              #+#    #+#             */
/*   Updated: 2026/02/22 12:27:19 by mrys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

// if needed add vnormalize3(f,f); to normalize input
void	parse_camera(char **s, t_scene *scene)
{
	double	f[3];
	double	c[3];
	double	fov;
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	if (len != 4)
		exit_error("Invalid camera format (C pos dir fov)");
	parse_vec3(s[1], c);
	parse_vec3(s[2], f);
	if (!is_normalized(f))
		exit_error("Camera direction not normalized");
	fov = parse_double(s[3]);
	if (fov < 0.0 || fov > 180.0)
		exit_error("FOV must be in [0,180]");
	camera_set(&scene->camera, 800, 600, fov, f, c);
}
