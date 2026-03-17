/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrys <mrys@student.42warsaw.pl>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 13:14:55 by mrys              #+#    #+#             */
/*   Updated: 2026/02/24 12:55:18 by mrys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/framebuffer.h"

static void	n_sphere(const double o[3], const double p[3],
				const double r, double n[3])
{
	n[0] = (p[0] - o[0]) / r;
	n[1] = (p[1] - o[1]) / r;
	n[2] = (p[2] - o[2]) / r;
}

static void	reverse_hit(t_hit *hit)
{
	hit->n[0] = -hit->n[0];
	hit->n[1] = -hit->n[1];
	hit->n[2] = -hit->n[2];
}

// if d<0 no hit return 0
static int	abc(const t_obj *obj, const t_ray *ray, double *t0, double *t1)
{
	double	oc[3];
	double	r;
	double	abc[3];
	double	d;

	r = obj->shape.sphere.radius;
	oc[0] = ray->o[0] - obj->pos.pos[0];
	oc[1] = ray->o[1] - obj->pos.pos[1];
	oc[2] = ray->o[2] - obj->pos.pos[2];
	abc[0] = vdotn(ray->d, ray->d, 3);
	abc[1] = 2 * vdotn(oc, ray->d, 3);
	abc[2] = vdotn(oc, oc, 3) - r * r;
	d = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (d < 0.0)
		return (0);
	*t0 = (-abc[1] + sqrt(d)) / (2 * abc[0]);
	*t1 = (-abc[1] - sqrt(d)) / (2 * abc[0]);
	return (1);
}

// returns 1 if found intersection 0 otherwise
static int	intersect_sphere(const t_obj *obj, const t_ray *ray, t_hit *hit)
{
	double	t0;
	double	t1;
	double	r;
	double	t_hit;

	r = obj->shape.sphere.radius;
	if (abc(obj, ray, &t0, &t1) == 0)
		return (0);
	swap2(&t0, &t1);
	if (t0 >= 1e-4)
		t_hit = t0;
	else if (t1 >= 1e-4)
		t_hit = t1;
	else
		return (0);
	hit->obj = obj;
	hit->t = t_hit;
	point(ray->o, ray->d, t_hit, hit->p);
	n_sphere(obj->pos.pos, hit->p, r, hit->n);
	vnormalize3(hit->n, hit->n);
	if (vdotn(ray->d, hit->n, 3) > 0.0)
	{
		reverse_hit(hit);
	}
	return (1);
}

// this one general function or separate function for each object
void	obj_sphere(t_obj *obj, t_inputdata *inputdata)
{
	obj->type = OBJ_SPHERE;
	obj->pos.pos[0] = inputdata->pos[0];
	obj->pos.pos[1] = inputdata->pos[1];
	obj->pos.pos[2] = inputdata->pos[2];
	obj->pos.dir[0] = inputdata->ndir[0];
	obj->pos.dir[1] = inputdata->ndir[1];
	obj->pos.dir[2] = inputdata->ndir[2];
	obj->shape.sphere.radius = inputdata->radius;
	obj->intersect = intersect_sphere;
	obj->albedo[0] = inputdata->albedo[0];
	obj->albedo[1] = inputdata->albedo[1];
	obj->albedo[2] = inputdata->albedo[2];
}
