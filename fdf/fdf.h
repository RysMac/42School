/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mr <mr@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:12:17 by mrys              #+#    #+#             */
/*   Updated: 2025/05/20 20:33:54 by mr               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H

# define FDF_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include "mlx/mlx.h"
# include <math.h>
# include "get_next_line/get_next_line.h"
# include "libft/libft.h"

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	screen_x;
	int	screen_y;
	int	color;
}	t_point;

typedef struct s_imgvars
{
	void	*mlx;
	void	*win;
	void	*img;
	int		bpp;
	int		line_length;
	int		endian;
	t_point	**grid;
	int		h;
	int		w;
	int		max_z;
}	t_imgvars;

typedef struct s_size
{
	int	max_x;
	int	max_y;
	int	min_x;
	int	min_y;
	int	max_z;
	int	mid_x;
	int	mid_y;
}	t_size;

int		read_file(char *name);
void	free_loop(char **arr);
void	project_point(t_point *p, double scale, t_imgvars win_vars);
int		hex_to_int(const char *hex);

void	grid_size(int *w, int *h, char *name);
t_point	**grid2d(int w, int h, char *name);
void	free_grid(t_point **grid, int h);
void	draw_line(char *addr, t_imgvars img_var, t_point node1, t_point node2);
void	draw_grid(char *addr, t_imgvars img_var, t_point **grid);
void    project_grid(t_point **grid, t_imgvars win_vars, double zoom);

void	get_size(t_size *size, t_point **grid, int w, int h);
void	translate_grid(t_point **grid, int x, int y, t_imgvars win_var);
void	zoom_grid(t_point **grid, t_imgvars win_var, float zoom_factor, t_size *size);

int		handle_keypress(int keycode, t_imgvars *vars);
char	*set_mlx(t_imgvars *win_var, t_point **grid, int win_size);
int		handle_close(t_imgvars *vars);

#endif
