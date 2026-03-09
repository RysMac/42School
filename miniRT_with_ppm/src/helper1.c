/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrys <mrys@student.42warsaw.pl>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 12:20:15 by mrys              #+#    #+#             */
/*   Updated: 2026/02/22 12:20:15 by mrys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/framebuffer.h"

// gives a point based on direction and translation and param t
void	point(const double o[3], const double d[3], const double t, double p[3])
{
	p[0] = o[0] + t * d[0];
	p[1] = o[1] + t * d[1];
	p[2] = o[2] + t * d[2];
}

// sort two numbers
void	swap2(double *t0, double *t1)
{
	double	tmp;

	if (*t0 > *t1)
	{
		tmp = *t0;
		*t0 = *t1;
		*t1 = tmp;
	}
}
