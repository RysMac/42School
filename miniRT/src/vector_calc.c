/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_calc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrys <mrys@student.42warsaw.pl>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 17:38:55 by mrys              #+#    #+#             */
/*   Updated: 2026/02/28 17:38:56 by mrys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "framebuffer.h"
#include <math.h>

void	vec_sub(const double a[3], const double b[3], double out[3])
{
	out[0] = a[0] - b[0];
	out[1] = a[1] - b[1];
	out[2] = a[2] - b[2];
}

double	vec_dot(const double a[3], const double b[3])
{
	return (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]);
}

double	vec_len(const double v[3])
{
	return (sqrt(vec_dot(v, v)));
}

void	vec_scale(const double v[3], double s, double out[3])
{
	out[0] = v[0] * s;
	out[1] = v[1] * s;
	out[2] = v[2] * s;
}

void	vec_clamp01(double v[3])
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (v[i] < 0.0)
			v[i] = 0.0;
		if (v[i] > 1.0)
			v[i] = 1.0;
		++i;
	}
}
