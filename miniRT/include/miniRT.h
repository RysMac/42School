/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrys <mrys@student.42warsaw.pl>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 11:23:54 by mrys              #+#    #+#             */
/*   Updated: 2026/02/26 13:53:52 by mrys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "framebuffer.h"
# include "parse.h"
# include "scene.h"
# include "../minilibx-linux/mlx.h"

# define WIDTH 800
# define HEIGHT 600
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

void	exit_error(const char *msg);
void	cleanup(t_data *data);
int		key_hook(int keycode, t_data *data);
int		close_hook(t_data *data);
void	init_and_render(t_data *data);
void	coloring_object_mlx(t_data *data);
void	coloring_object(t_data *data);

#endif
