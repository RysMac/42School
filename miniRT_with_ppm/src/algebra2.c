/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algebra2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrys <mrys@student.42warsaw.pl>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 12:10:10 by mrys              #+#    #+#             */
/*   Updated: 2026/02/26 12:03:41 by mrys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stddef.h>
#include "framebuffer.h"
// #include "miniRT.h"

// v' = R v, where rows of R are x, y, z (your basis vectors)
// projection on x'
// projection on y'
// projection on z'
void	rv(const double vin[3], const double x[3],
			const double y[3], const double z[3], double vout[3])
{
	vout[0] = vdotn(x, vin, 3);
	vout[1] = vdotn(y, vin, 3);
	vout[2] = vdotn(z, vin, 3);
}

// inverse: v = R^T v'  (local -> world)
// vin -> local coords
// vout -> world coords
void	rv_inv(const double vin[3],
			const double x[3],
			const double y[3],
			const double z[3],
			double vout[3])
{
	vout[0] = vin[0] * x[0] + vin[1] * y[0] + vin[2] * z[0];
	vout[1] = vin[0] * x[1] + vin[1] * y[1] + vin[2] * z[1];
	vout[2] = vin[0] * x[2] + vin[1] * y[2] + vin[2] * z[2];
}

void	rotate_x(double v[3], double theta)
{
	double	c;
	double	s;

	c = cos(theta);
	s = sin(theta);
	v[1] = v[1] * c - v[2] * s;
	v[2] = v[1] * s + v[2] * c;
}

void	rotate_y(double v[3], double theta)
{
	double	c;
	double	s;

	c = cos(theta);
	s = sin(theta);
	v[0] = v[0] * c + v[2] * s;
	v[2] = -v[0] * s + v[2] * c;
}

void	rotate_z(double v[3], double theta)
{
	double	c;
	double	s;

	c = cos(theta);
	s = sin(theta);
	v[0] = v[0] * c - v[1] * s;
	v[1] = v[0] * s + v[1] * c;
}
