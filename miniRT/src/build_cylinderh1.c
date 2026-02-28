/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cylinderh1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrys <mrys@student.42warsaw.pl>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 11:56:57 by mrys              #+#    #+#             */
/*   Updated: 2026/02/28 18:35:25 by mrys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/framebuffer.h"
#include "../include/miniRT.h"

// n, x, y are local plane basis needed for transformation matrix R
// check if n is normalized
void	cylinder_basis(const double n[3], double x[3], double y[3])
{
	double	u[3];

	if (fabs(n[1]) < 0.9)
	{
		u[0] = 0.0;
		u[1] = 1.0;
		u[2] = 0.0;
	}
	else
	{
		u[0] = 1.0;
		u[1] = 0.0;
		u[2] = 0.0;
	}
	cross3(u, n, x);
	vnormalize3(x, x);
	cross3(n, x, y);
}

/* Init per-object scalars and clear hit state. */
void	cyl_init_ctx(t_cyl_ctx *k, const t_obj *obj)
{
	k->r = obj->shape.cylinder.radius;
	k->hh = obj->shape.cylinder.height * 0.5;
	k->t_side = k->params.cyl_inf;
	k->t_top = k->params.cyl_inf;
	k->t_bot = k->params.cyl_inf;
	k->hit_side = 0;
	k->hit_top = 0;
	k->hit_bot = 0;
	k->t_best = k->params.cyl_inf;
	k->hit_type = 0;
}

/* Build orthonormal basis (x,y) around cylinder axis. */
void	cyl_build_basis(t_cyl_ctx *k, const t_obj *obj)
{
	cylinder_basis(obj->pos.dir, k->x, k->y);
}

/*
	Convert world ray to cylinder
	-local coordinates (origin shifted to center).
*/
void	cyl_set_local_ray(t_cyl_ctx *k, const t_obj *obj,
		const t_ray *ray)
{
	double	o[3];
	t_vec3	v;

	o[0] = ray->o[0] - obj->pos.pos[0];
	o[1] = ray->o[1] - obj->pos.pos[1];
	o[2] = ray->o[2] - obj->pos.pos[2];
	v = rv(o, k->x, k->y, obj->pos.dir);
	vcopy3(v, k->c);
	v = rv(ray->d, k->x, k->y, obj->pos.dir);
	vcopy3(v, k->d);
}

/* Height-clip a candidate side hit and store nearest valid one. */
void	cyl_side_accept(t_cyl_ctx *k, double t)
{
	if (t < k->params.cyl_tmin)
		return ;
	point(k->c, k->d, t, k->p_local);
	if (k->p_local[2] < -k->hh || k->p_local[2] > k->hh)
		return ;
	k->t_side = t;
	k->hit_side = 1;
}
