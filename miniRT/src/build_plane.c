/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrys <mrys@student.42warsaw.pl>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 12:52:10 by mrys              #+#    #+#             */
/*   Updated: 2026/02/28 19:14:46 by mrys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/framebuffer.h"

static void	reverse_hit(t_hit *hit)
{
	hit->n[0] = -hit->n[0];
	hit->n[1] = -hit->n[1];
	hit->n[2] = -hit->n[2];
}

// n, x, y are local plane basis needed for transformation matrix R
// check if n is normalized
void	plane_basis(const double n[3], double x[3], double y[3])
{
	double	u[3];

	if (fabs(n[1]) < 0.99)
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

static int	find_t(const t_obj *obj, const t_ray *ray, t_hit *hit, double *t)
{
	double	o[3];
	double	x[3];
	double	y[3];
	double	d[3];
	double	c[3];

	plane_basis(obj->pos.dir, x, y);
	o[0] = ray->o[0] - obj->pos.pos[0];
	o[1] = ray->o[1] - obj->pos.pos[1];
	o[2] = ray->o[2] - obj->pos.pos[2];
	vcopy3(rv(o, x, y, obj->pos.dir), c);
	vcopy3(rv(ray->d, x, y, obj->pos.dir), d);
	if (fabs(d[2]) < 1e-8)
		return (0);
	else
		*t = -c[2] / d[2];
	if (*t < 1e-4)
		return (0);
	point(c, d, *t, hit->p);
	return (1);
}

/* 
	add: if (fabs(hit->p[0]) > 30 || fabs(hit->p[1]) > 30) return (0);
	if you want not infinite plane

	ray->o is origin of camera obj->pos.pos is a point on the plane
*/
static int	intersect_plane(const t_obj *obj, const t_ray *ray, t_hit *hit)
{
	double	x[3];
	double	y[3];
	double	t;
	double	d_dot_n;

	plane_basis(obj->pos.dir, x, y);
	if (find_t(obj, ray, hit, &t) == 0)
		return (0);
	vcopy3(rv_inv(hit->p, x, y, obj->pos.dir), hit->p);
	hit->obj = obj;
	hit->p[0] = obj->pos.pos[0] + hit->p[0];
	hit->p[1] = obj->pos.pos[1] + hit->p[1];
	hit->p[2] = obj->pos.pos[2] + hit->p[2];
	hit->t = t;
	hit->n[0] = obj->pos.dir[0];
	hit->n[1] = obj->pos.dir[1];
	hit->n[2] = obj->pos.dir[2];
	vnormalize3(hit->n, hit->n);
	d_dot_n = vdotn(ray->d, hit->n, 3);
	if (d_dot_n > 0.0)
		reverse_hit(hit);
	return (1);
}

// pos - center point position in global frame
void	obj_plane(t_obj *obj, t_inputdata *inputdata)
{
	double	tmp[3];

	obj->type = OBJ_PLANE;
	obj->pos.pos[0] = inputdata->pos[0];
	obj->pos.pos[1] = inputdata->pos[1];
	obj->pos.pos[2] = inputdata->pos[2];
	vnormalize3(inputdata->ndir, tmp);
	obj->pos.dir[0] = tmp[0];
	obj->pos.dir[1] = tmp[1];
	obj->pos.dir[2] = tmp[2];
	obj->intersect = intersect_plane;
	obj->albedo[0] = inputdata->albedo[0];
	obj->albedo[1] = inputdata->albedo[1];
	obj->albedo[2] = inputdata->albedo[2];
}
