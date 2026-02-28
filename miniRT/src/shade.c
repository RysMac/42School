/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrys <mrys@student.42warsaw.pl>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 17:23:36 by mrys              #+#    #+#             */
/*   Updated: 2026/02/28 17:23:36 by mrys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "framebuffer.h"
#include <math.h>

/*
	Hard shadow test: ANY hit before the light blocks diffuse contribution 
	be carefull with condition:
	if (tmp.t >= TMIN && tmp.t <= dist_to_light - TMIN)
*/
static int	hard_shadow(const t_scene *scene, double dist_to_light,
				t_ray *shadow)
{
	const t_obj	*obj;
	t_hit		tmp;
	size_t		i;

	i = 0;
	while (i < scene->count)
	{
		obj = &scene->objects[i];
		if (obj->intersect(obj, shadow, &tmp))
		{
			if (tmp.t >= 1e-4 && tmp.t <= dist_to_light - 1e-4)
			{
				return (1);
			}
		}
		++i;
	}
	return (0);
}

/*
	* Bias the shadow ray origin away from the surface in the direction that
	* reduces self-intersection. If dot(n, Ldir) is negative, push along -n.
	* This is safer than always +n when you are inside objects / flipped normals.
*/
static void	safer_shadow(const t_hit *hit, t_ray *shadow, double Ldir[3])
{
	double	shadow_eps;
	double	ndotl;
	double	sign;

	shadow_eps = 1e-3;
	ndotl = vec_dot(hit->n, Ldir);
	if (ndotl >= 0.0)
		sign = 1.0;
	else
		sign = -1.0;
	shadow->o[0] = hit->p[0] + sign * shadow_eps * hit->n[0];
	shadow->o[1] = hit->p[1] + sign * shadow_eps * hit->n[1];
	shadow->o[2] = hit->p[2] + sign * shadow_eps * hit->n[2];
	shadow->d[0] = Ldir[0];
	shadow->d[1] = Ldir[1];
	shadow->d[2] = Ldir[2];
}

static void	color_shadow(const t_scene *scene, const t_hit *hit,
				t_ray *shadow, double cd[3])
{
	double	ldir[3];
	double	to_light[3];
	double	dist_to_light;
	double	ndotl;
	double	intensity;

	vec_sub(scene->light.pos, hit->p, to_light);
	dist_to_light = vec_len(to_light);
	vec_scale(to_light, 1.0 / dist_to_light, ldir);
	safer_shadow(hit, shadow, ldir);
	if (!hard_shadow(scene, dist_to_light, shadow))
	{
		ndotl = vec_dot(hit->n, ldir);
		if (ndotl > 0.0)
		{
			intensity = ndotl * scene->light.brightness;
			cd[0] = intensity * hit->obj->albedo[0] * scene->light.color[0];
			cd[1] = intensity * hit->obj->albedo[1] * scene->light.color[1];
			cd[2] = intensity * hit->obj->albedo[2] * scene->light.color[2];
		}
	}
}

static void	zero_out(double cd[3], double ca[3])
{
	cd[0] = 0.0;
	cd[1] = 0.0;
	cd[2] = 0.0;
	ca[0] = 0.0;
	ca[1] = 0.0;
	ca[2] = 0.0;
}

/*
 * Improvements applied:
 *  1) No skipping (obj == hit->obj) in shadow tests.
 *  2) Shadow origin bias uses +/- normal depending on dot(n, L).
 *  3) Increased epsilon (1e-4).
 */
void	shade(const t_scene *scene, const t_hit *hit, double color[3])
{
	double	cd[3];
	double	ca[3];
	double	to_light[3];
	double	dist_to_light;
	t_ray	shadow;

	zero_out(cd, ca);
	if (check_hit(hit, color) == 0)
		return ;
	ambient_term(scene, hit, ca);
	vec_sub(scene->light.pos, hit->p, to_light);
	dist_to_light = vec_len(to_light);
	if (dist_to_light < 1e-9)
	{
		color[0] = ca[0];
		color[1] = ca[1];
		color[2] = ca[2];
		vec_clamp01(color);
		return ;
	}
	color_shadow(scene, hit, &shadow, cd);
	color[0] = ca[0] + cd[0];
	color[1] = ca[1] + cd[1];
	color[2] = ca[2] + cd[2];
	vec_clamp01(color);
}
