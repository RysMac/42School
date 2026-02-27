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

/* ---- cylinder intersection helpers (constraints-friendly split) ---- */
#define CYL_TMIN     1e-4
#define CYL_DISC_EPS 1e-12
#define CYL_CAP_EPS  1e-9
#define CYL_INF      1e30

// x,y	local frame (x,y) with axis = obj->pos.dir
// d	ray in cylinder-local space
// p_local	final local hit point
// n_local	final local normal
// p_world	final world hit point
// n_world	final world normal
// hh		radius, half-height
// t_best	chosen intersection t
// hit_type	0 none, 1 side, 2 top, 3 bottom
typedef struct s_cyl_ctx
{
	double	x[3];
	double	y[3];
	double	c[3];
	double	d[3];
	double	p_local[3];
	double	n_local[3];
	double	p_world[3];
	double	n_world[3];

	double	r;
	double	hh;
	double	t_side;
	double	t_top;
	double	t_bot;
	int		hit_side;
	int		hit_top;
	int		hit_bot;

	double	t_best;
	int		hit_type;

	double	q0;
	double	q1;
	double	q2;
	double	q3;
}	t_cyl_ctx;

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
static void	cyl_init_ctx(t_cyl_ctx *k, const t_obj *obj)
{
	k->r = obj->shape.cylinder.radius;
	k->hh = obj->shape.cylinder.height * 0.5;
	k->t_side = CYL_INF;
	k->t_top = CYL_INF;
	k->t_bot = CYL_INF;
	k->hit_side = 0;
	k->hit_top = 0;
	k->hit_bot = 0;
	k->t_best = CYL_INF;
	k->hit_type = 0;
}

/* Build orthonormal basis (x,y) around cylinder axis. */
static void	cyl_build_basis(t_cyl_ctx *k, const t_obj *obj)
{
	cylinder_basis(obj->pos.dir, k->x, k->y);
}

/*
	Convert world ray to cylinder
	-local coordinates (origin shifted to center).
*/
static void	cyl_set_local_ray(t_cyl_ctx *k, const t_obj *obj,
		const t_ray *ray)
{
	double	o[3];

	o[0] = ray->o[0] - obj->pos.pos[0];
	o[1] = ray->o[1] - obj->pos.pos[1];
	o[2] = ray->o[2] - obj->pos.pos[2];
	rv(o, k->x, k->y, obj->pos.dir, k->c);
	rv(ray->d, k->x, k->y, obj->pos.dir, k->d);
}

/* Height-clip a candidate side hit and store nearest valid one. */
static void	cyl_side_accept(t_cyl_ctx *k, double t)
{
	if (t < CYL_TMIN)
		return ;
	point(k->c, k->d, t, k->p_local);
	if (k->p_local[2] < -k->hh || k->p_local[2] > k->hh)
		return ;
	k->t_side = t;
	k->hit_side = 1;
}

/*
	Intersect infinite cylinder (x^2+y^2=r^2),
	then clip by height using both roots.
*/
static void	cyl_intersect_side(t_cyl_ctx *k)
{
	k->hit_side = 0;
	k->t_side = CYL_INF;
	k->q0 = vdotn(k->d, k->d, 2);
	if (fabs(k->q0) <= 1e-12)
		return ;
	k->q1 = 2.0 * vdotn(k->c, k->d, 2);
	k->q2 = vdotn(k->c, k->c, 2) - (k->r * k->r);
	k->q3 = (k->q1 * k->q1) - (4.0 * k->q0 * k->q2);
	if (k->q3 <= -CYL_DISC_EPS)
		return ;
	if (k->q3 < 0.0)
		k->q3 = 0.0;
	k->q3 = sqrt(k->q3);
	k->q2 = 0.5 / k->q0;
	k->q0 = (-k->q1 - k->q3) * k->q2;
	k->q1 = (-k->q1 + k->q3) * k->q2;
	if (k->q0 > k->q1)
	{
		k->q3 = k->q0;
		k->q0 = k->q1;
		k->q1 = k->q3;
	}
	cyl_side_accept(k, k->q0);
	if (!k->hit_side)
		cyl_side_accept(k, k->q1);
}

/* Radius-check a cap hit at parameter t; writes top or bottom result. */
static void	cyl_cap_accept(t_cyl_ctx *k, double t, int top)
{
	if (t < CYL_TMIN)
		return ;
	point(k->c, k->d, t, k->p_local);
	k->q1 = (k->p_local[0] * k->p_local[0]) + (k->p_local[1] * k->p_local[1]);
	if (k->q1 > (k->r * k->r) + CYL_CAP_EPS)
		return ;
	if (top)
	{
		k->t_top = t;
		k->hit_top = 1;
	}
	else
	{
		k->t_bot = t;
		k->hit_bot = 1;
	}
}

/* Intersect end caps z=±hh (local space) and radius-check. */
static void	cyl_intersect_caps(t_cyl_ctx *k)
{
	k->hit_top = 0;
	k->hit_bot = 0;
	k->t_top = CYL_INF;
	k->t_bot = CYL_INF;
	if (fabs(k->d[2]) <= 1e-12)
		return ;
	k->q0 = (k->hh - k->c[2]) / k->d[2];
	cyl_cap_accept(k, k->q0, 1);
	k->q0 = (-k->hh - k->c[2]) / k->d[2];
	cyl_cap_accept(k, k->q0, 0);
}

/* Pick nearest among valid side/top/bottom hits. */
static void	cyl_choose_best(t_cyl_ctx *k)
{
	k->t_best = CYL_INF;
	k->hit_type = 0;
	if (k->hit_side && k->t_side < k->t_best)
	{
		k->t_best = k->t_side;
		k->hit_type = 1;
	}
	if (k->hit_top && k->t_top < k->t_best)
	{
		k->t_best = k->t_top;
		k->hit_type = 2;
	}
	if (k->hit_bot && k->t_bot < k->t_best)
	{
		k->t_best = k->t_bot;
		k->hit_type = 3;
	}
}

/* Compute final local hit point and local normal based on hit type. */
static void	cyl_compute_local_pn(t_cyl_ctx *k)
{
	point(k->c, k->d, k->t_best, k->p_local);
	if (k->hit_type == 1)
	{
		k->n_local[0] = k->p_local[0];
		k->n_local[1] = k->p_local[1];
		k->n_local[2] = 0.0;
		k->q2 = sqrt((k->n_local[0] * k->n_local[0])
				+ (k->n_local[1] * k->n_local[1]));
		if (k->q2 > 0.0)
		{
			k->n_local[0] /= k->q2;
			k->n_local[1] /= k->q2;
		}
		return ;
	}
	k->n_local[0] = 0.0;
	k->n_local[1] = 0.0;
	if (k->hit_type == 2)
		k->n_local[2] = 1.0;
	else
		k->n_local[2] = -1.0;
}

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
