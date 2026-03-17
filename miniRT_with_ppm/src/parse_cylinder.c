/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrys <mrys@student.42warsaw.pl>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 12:28:25 by mrys              #+#    #+#             */
/*   Updated: 2026/02/22 12:29:40 by mrys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

// if needed add vnormalize3(in.ndir, in.ndir); to normalize input
void	parse_cylinder(char **s, t_scene *scene)
{
	t_inputdata	in;
	t_obj		obj;
	double		diameter;
	size_t		len;

	len = 0;
	while (s[len])
		len++;
	if (len != 6)
		exit_error("Invalid cylinder format \
			(cy pos axis diameter height color)");
	ft_bzero(&in, sizeof(in));
	parse_vec3(s[1], in.pos);
	parse_vec3(s[2], in.ndir);
	if (!is_normalized(in.ndir))
		exit_error("Cylinder axis not normalized");
	diameter = parse_double(s[3]);
	if (diameter <= 0.0)
		exit_error("Cylinder diameter must be positive");
	in.radius = diameter / 2.0;
	in.height = parse_double(s[4]);
	if (in.height <= 0.0)
		exit_error("Cylinder height must be positive");
	parse_color(s[5], in.albedo);
	obj_cylinder(&obj, &in);
	add_object(scene, &obj);
}
