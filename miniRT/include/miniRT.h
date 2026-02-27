/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrys <mrys@student.42warsaw.pl>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 11:23:54 by mrys              #+#    #+#             */
/*   Updated: 2026/02/27 14:56:37 by mrys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "framebuffer.h"
# include "parse.h"
# include "scene.h"
# include "../minilibx-linux/mlx.h"

// # define WIDTH 800
// # define HEIGHT 600
# define ESC_KEY 65307

typedef struct s_data
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
	int				w;
	int				h;
	t_framebuffer	fb;
	t_framebuffer	fb_ppm;
	t_scene			scene;
}	t_data;

typedef struct s_cyl_params
{
	double	cyl_tmin;
	double	cyl_disc_eps;
	double	cyl_cap_eps;
	double	cyl_inf;
	
}	t_cyl_params;

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

	t_cyl_params	params;
}	t_cyl_ctx;

void	exit_error(const char *msg);
void	cleanup(t_data *data);
int		key_hook(int keycode, t_data *data);
int		close_hook(t_data *data);
void	init_and_render(t_data *data);
void	coloring_object_mlx(t_data *data);
void	coloring_object(t_data *data);

#endif
