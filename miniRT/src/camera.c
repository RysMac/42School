/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrys <mrys@student.42warsaw.pl>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 12:15:19 by mrys              #+#    #+#             */
/*   Updated: 2026/02/22 12:15:19 by mrys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "scene.h"
#include "framebuffer.h"

static void	base(const double f_in[3], double f[3], double up[3])
{
	double	ud[3];
	double	ua[3];
	double	dot;

	ud[0] = 0.0;
	ud[1] = 1.0;
	ud[2] = 0.0;
	ua[0] = 0.0;
	ua[1] = 0.0;
	ua[2] = 1.0;
	vnormalize3(f_in, f);
	dot = f[0] * ud[0] + f[1] * ud[1] + f[2] * ud[2];
	if (fabs(dot) > 0.99)
	{
		up[0] = ua[0];
		up[1] = ua[1];
		up[2] = ua[2];
	}
	else
	{
		up[0] = ud[0];
		up[1] = ud[1];
		up[2] = ud[2];
	}
}

static void	camera_basis(t_camera *camera, const double f_in[3])
{
	double	f[3];
	double	r[3];
	double	u[3];
	double	up[3];
	int		i;

	base(f_in, f, up);
	cross3(f, up, r);
	vnormalize3(r, r);
	cross3(r, f, u);
	vnormalize3(u, u);
	i = 0;
	while (i < 3)
	{
		camera->f[i] = f[i];
		camera->r[i] = r[i];
		camera->u[i] = u[i];
		++i;
	}
}

void	camera_set(t_camera *camera, double fovx,
				const double f_in[3], const double c[3])
{
	double	ar;
	double	fovx_rad;
	size_t	i;

	ar = (double)(*camera->w) / (double)(*camera->h);
	fovx_rad = fovx * M_PI / 180.0;
	camera->fovx = fovx;
	camera->fovy = (2 * atan(tan(fovx_rad / 2) / ar)) * 180.0 / M_PI;
	i = 0;
	while (i < 3)
	{
		camera->c[i] = c[i];
		++i;
	}
	camera_basis(camera, f_in);
}
