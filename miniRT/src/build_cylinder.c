/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrys <mrys@student.42warsaw.pl>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 13:19:15 by mrys              #+#    #+#             */
/*   Updated: 2026/02/24 13:19:15 by mrys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/framebuffer.h"
#include "../include/miniRT.h"

/* Transform local point/normal back to world space and normalize normal. */
static void	cyl_local_to_world(t_cyl_ctx *k, const t_obj *obj)
{
	rv_inv(k->p_local, k->x, k->y, obj->pos.dir, k->p_world);
	rv_inv(k->n_local, k->x, k->y, obj->pos.dir, k->n_world);
	vnormalize3(k->n_world, k->n_world);
	k->p_world[0] += obj->pos.pos[0];
	k->p_world[1] += obj->pos.pos[1];
	k->p_world[2] += obj->pos.pos[2];
}

/* Fill t_hit and flip normal if it faces the ray direction. */
static void	cyl_write_hit(t_hit *hit, const t_obj *obj,
			const t_ray *ray, t_cyl_ctx *k)
{
	double	d_dot_n;

	hit->obj = obj;
	hit->t = k->t_best;
	hit->p[0] = k->p_world[0];
	hit->p[1] = k->p_world[1];
	hit->p[2] = k->p_world[2];
	hit->n[0] = k->n_world[0];
	hit->n[1] = k->n_world[1];
	hit->n[2] = k->n_world[2];
	vnormalize3(hit->n, hit->n);
	d_dot_n = vdotn(ray->d, hit->n, 3);
	if (d_dot_n > 0.0)
	{
		hit->n[0] = -hit->n[0];
		hit->n[1] = -hit->n[1];
		hit->n[2] = -hit->n[2];
	}
}

/*
	Public entry: run side + caps tests,
	choose nearest, produce world-space hit.
*/
static int	intersect_cylinder(const t_obj *obj,
				const t_ray *ray, t_hit *hit)
{
	t_cyl_ctx	k;

	k.params.cyl_tmin = 1e-4;
	k.params.cyl_disc_eps = 1e-12;
	k.params.cyl_cap_eps = 1e-9;
	k.params.cyl_inf = 1e30;
	cyl_init_ctx(&k, obj);
	cyl_build_basis(&k, obj);
	cyl_set_local_ray(&k, obj, ray);
	cyl_intersect_side(&k);
	cyl_intersect_caps(&k);
	cyl_choose_best(&k);
	if (k.hit_type == 0)
		return (0);
	cyl_compute_local_pn(&k);
	cyl_local_to_world(&k, obj);
	cyl_write_hit(hit, obj, ray, &k);
	return (1);
}

// pos - center point position in global frame
// pos.dir - normal direction (needed only for plane)
void	obj_cylinder(t_obj *obj, t_inputdata *inputdata)
{
	double	tmp[3];

	obj->type = OBJ_CYLINDER;
	obj->pos.pos[0] = inputdata->pos[0];
	obj->pos.pos[1] = inputdata->pos[1];
	obj->pos.pos[2] = inputdata->pos[2];
	vnormalize3(inputdata->ndir, tmp);
	obj->pos.dir[0] = tmp[0];
	obj->pos.dir[1] = tmp[1];
	obj->pos.dir[2] = tmp[2];
	obj->intersect = intersect_cylinder;
	obj->shape.cylinder.radius = inputdata->radius;
	obj->shape.cylinder.height = inputdata->height;
	obj->albedo[0] = inputdata->albedo[0];
	obj->albedo[1] = inputdata->albedo[1];
	obj->albedo[2] = inputdata->albedo[2];
}
