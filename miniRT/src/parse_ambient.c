/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrys <mrys@student.42warsaw.pl>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 12:24:49 by mrys              #+#    #+#             */
/*   Updated: 2026/02/22 12:24:51 by mrys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	parse_ambient(char **s, t_scene *scene)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	if (len != 3)
		exit_error("Invalid ambient format (A ratio color)");
	scene->ambient.ambient_ratio = parse_double(s[1]);
	if (scene->ambient.ambient_ratio < 0.0
		|| scene->ambient.ambient_ratio > 1.0)
		exit_error("Ambient ratio must be in [0,1]");
	parse_color(s[2], scene->ambient.ambient_color);
}
