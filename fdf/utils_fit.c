/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mr <mr@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 18:16:20 by mrys              #+#    #+#             */
/*   Updated: 2025/05/17 13:26:40 by mr               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	zoom_grid(	t_point **grid, t_imgvars win_var
					, float zoom_factor, t_size *size)
{
	int	i;
	int	j;

	i = 0;
	while (i < win_var.h)
	{
		j = 0;
		while (j < win_var.w)
		{
			grid[i][j].screen_x = size->mid_x
				+ (grid[i][j].screen_x - size->mid_x) * zoom_factor;
			grid[i][j].screen_y = size->mid_y
				+ (grid[i][j].screen_y - size->mid_y) * zoom_factor;
			j++;
		}
		i++;
	}
}

static void	init_size(t_size *size)
{
	size->max_x = 0;
	size->max_y = 0;
	size->max_z = 0;
	size->min_x = 0;
	size->min_y = 0;
}

/*
*	Find max and min values (x, y) of the picture, calculates mid point.
*	typedef struct s_size
*	{
*		int	max_x;
*		int	max_y;
*		int	min_x;
*		int	min_y;
*		int	max_z;
*		int	mid_x;
*		int	mid_y;
*	}	t_size;
*/
void	get_size(t_size *size, t_point **grid, int w, int h)
{
	int	i;
	int	j;

	init_size(size);
	i = 0;
	while (i < h)
	{
		j = 0;
		while (j < w)
		{
			if (fabs(grid[i][j].z) > size->max_z)
				size->max_z = grid[i][j].z;
			if (grid[i][j].screen_x > size->max_x)
				size->max_x = grid[i][j].screen_x;
			if (grid[i][j].screen_y > size->max_y)
				size->max_y = grid[i][j].screen_y;
			if (grid[i][j].screen_x < size->min_x)
				size->min_x = grid[i][j].screen_x;
			if (grid[i][j].screen_y < size->min_y)
				size->min_y = grid[i][j].screen_y;
			j++;
		}
		i++;
	}
	size->mid_x = (size->min_x + size->max_x) / 2;
	size->mid_y = (size->min_y + size->max_y) / 2;
}

/*
*	Take a grid and make rigid translation:
*	-> move to the right/left by x/-x
*	-> move up/dpwn by y/-y
*/
void	translate_grid(t_point **grid, int x, int y, t_imgvars win_var)
{
	int	i;
	int	j;

	i = 0;
	while (i < win_var.h)
	{
		j = 0;
		while (j < win_var.w)
		{
			grid[i][j].screen_x += x;
			grid[i][j].screen_y += y;
			j++;
		}
		i++;
	}
}

void	project_point(t_point *p, double scale, t_imgvars win_vars)
{
	double	angle;
	double	iso_x;
	double	iso_y;

	angle = 3.14 / 5;
	double Z_FACTOR = 4.;

	double avg_dim = (win_vars.w + win_vars.h) / 2.0;
	double z_scale = scale * (Z_FACTOR / avg_dim);

	double projected_diag = sqrt(win_vars.w * win_vars.w + win_vars.h * win_vars.h) * scale;
	z_scale = projected_diag * (Z_FACTOR / projected_diag);
	// if (z_scale < 3.)
		// z_scale = 3.;
	if (win_vars.max_z * z_scale > projected_diag / 2. && projected_diag > 100.)
		z_scale = 0.1;

	iso_x = (p->x - p->y) * cos(angle) * scale;
	iso_y = (p->x + p->y) * sin(angle) * scale - (p->z) * z_scale;
	// printf("z_scale = %f \n", z_scale);
	p->screen_x = iso_x;
	p->screen_y = iso_y;
}

void	project_grid(t_point **grid, t_imgvars win_vars, double zoom)
{
	int	i;
	int	j;

	i = 0;
	while (i < win_vars.h)
	{
		j = 0;
		while (j < win_vars.w)
		{
			project_point(&grid[i][j], zoom, win_vars);
			j++;
		}
		i++;
	}
}
