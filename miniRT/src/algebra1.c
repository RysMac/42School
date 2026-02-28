/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algebra.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrys <mrys@student.42warsaw.pl>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 11:51:05 by mrys              #+#    #+#             */
/*   Updated: 2026/02/22 11:51:05 by mrys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stddef.h>
#include "../include/object.h"

double	vdotn(const double v1[3], const double v2[3], size_t n)
{
	size_t	i;
	double	sum;

	i = 0;
	sum = 0.0;
	while (i < n)
	{
		sum += v1[i] * v2[i];
		i++;
	}
	return (sum);
}

double	vnorm3(const double v[3])
{
	return (sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]));
}

void	vnormalize3(const double v[3], double vnrm[3])
{
	double	a0;
	double	a1;
	double	a2;
	double	nrm;
	double	inv;

	a0 = v[0];
	a1 = v[1];
	a2 = v[2];
	nrm = sqrt(a0 * a0 + a1 * a1 + a2 * a2);
	if (nrm == 0.0)
	{
		vnrm[0] = 0.0;
		vnrm[1] = 0.0;
		vnrm[2] = 0.0;
		return ;
	}
	inv = 1.0 / nrm;
	vnrm[0] = a0 * inv;
	vnrm[1] = a1 * inv;
	vnrm[2] = a2 * inv;
}

void	cross3(const double a[3], const double b[3], double result[3])
{
	result[0] = a[1] * b[2] - a[2] * b[1];
	result[1] = a[2] * b[0] - a[0] * b[2];
	result[2] = a[0] * b[1] - a[1] * b[0];
}

void	vcopy3(const t_vec3 vin, double vout[3])
{
	vout[0] = vin.v[0];
	vout[1] = vin.v[1];
	vout[2] = vin.v[2];
}
