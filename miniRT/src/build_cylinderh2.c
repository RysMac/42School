/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cylinderh2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrys <mrys@student.42warsaw.pl>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 11:59:09 by mrys              #+#    #+#             */
/*   Updated: 2026/02/27 12:15:12 by mrys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/framebuffer.h"
#include "../include/miniRT.h"

/*
	Intersect infinite cylinder (x^2+y^2=r^2),
	then clip by height using both roots.
*/
void	cyl_intersect_side(t_cyl_ctx *k)
{
	k->hit_side = 0;
	k->t_side = k->params.cyl_inf;
	k->q0 = vdotn(k->d, k->d, 2);
	if (fabs(k->q0) <= 1e-12)
		return ;
	k->q1 = 2.0 * vdotn(k->c, k->d, 2);
	k->q2 = vdotn(k->c, k->c, 2) - (k->r * k->r);
	k->q3 = (k->q1 * k->q1) - (4.0 * k->q0 * k->q2);
	if (k->q3 <= -k->params.cyl_disc_eps)
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
void	cyl_cap_accept(t_cyl_ctx *k, double t, int top)
{
	if (t < k->params.cyl_tmin)
		return ;
	point(k->c, k->d, t, k->p_local);
	k->q1 = (k->p_local[0] * k->p_local[0]) + (k->p_local[1] * k->p_local[1]);
	if (k->q1 > (k->r * k->r) + k->params.cyl_cap_eps)
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
void	cyl_intersect_caps(t_cyl_ctx *k)
{
	k->hit_top = 0;
	k->hit_bot = 0;
	k->t_top = k->params.cyl_inf;
	k->t_bot = k->params.cyl_inf;
	if (fabs(k->d[2]) <= 1e-12)
		return ;
	k->q0 = (k->hh - k->c[2]) / k->d[2];
	cyl_cap_accept(k, k->q0, 1);
	k->q0 = (-k->hh - k->c[2]) / k->d[2];
	cyl_cap_accept(k, k->q0, 0);
}

/* Pick nearest among valid side/top/bottom hits. */
void	cyl_choose_best(t_cyl_ctx *k)
{
	k->t_best = k->params.cyl_inf;
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
void	cyl_compute_local_pn(t_cyl_ctx *k)
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
