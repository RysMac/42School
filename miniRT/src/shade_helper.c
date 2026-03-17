/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrys <mrys@student.42warsaw.pl>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 17:39:53 by mrys              #+#    #+#             */
/*   Updated: 2026/02/28 17:42:22 by mrys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "framebuffer.h"
#include <math.h>

// albedo, ambient, ambient_ratio must be [0,1] here
void	ambient_term(const t_scene *scene, const t_hit *hit, double out[3])
{
	const double	*ka;
	const t_ambient	*amb;
	double			ratio;

	ka = hit->obj->albedo;
	amb = &scene->ambient;
	ratio = amb->ambient_ratio;
	out[0] = ratio * ka[0] * amb->ambient_color[0];
	out[1] = ratio * ka[1] * amb->ambient_color[1];
	out[2] = ratio * ka[2] * amb->ambient_color[2];
}

int	check_hit(const t_hit *hit, double color[3])
{
	if (!hit || !hit->obj)
	{
		color[0] = 0.0;
		color[1] = 0.0;
		color[2] = 0.0;
		return (0);
	}
	return (1);
}
