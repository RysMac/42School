/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mr <mr@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:34:52 by mrys              #+#    #+#             */
/*   Updated: 2025/05/20 21:14:27 by mr               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	*set_mlx(t_imgvars *img_var, t_point **grid, int win_size)
{
	char *addr;

	img_var->mlx = mlx_init();
	img_var->win = mlx_new_window(img_var->mlx, win_size, win_size, "FDF Test");
	img_var->img = mlx_new_image(img_var->mlx, win_size, win_size);
	addr = mlx_get_data_addr(img_var->img, &(img_var->bpp), &(img_var->line_length), &(img_var->endian));
	img_var->grid = grid;
	return (addr);
}

void put_pixel(char *addr, t_imgvars img_var, t_point pixel)
{
	char *dst = addr + (pixel.screen_y * img_var.line_length + pixel.screen_x * (img_var.bpp / 8));
	*(unsigned int *)dst = pixel.color;
}

void	draw_line(char *addr, t_imgvars img_var, t_point node1, t_point node2)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int e2;

	dx = abs(node2.screen_x - node1.screen_x);
	dy = abs(node2.screen_y - node1.screen_y);
	if (node1.screen_x < node2.screen_x)
		sx = 1;
	else
		sx = -1;

	if (node1.screen_y < node2.screen_y)
		sy = 1;
	else
		sy = -1;
	err = dx - dy;
	while (1)
	{
		put_pixel(addr, img_var, node1);
		if (node1.screen_x == node2.screen_x && node1.screen_y == node2.screen_y)
			break ;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			node1.screen_x += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			node1.screen_y += sy;
		}
	}
}

void	draw_grid(char *addr, t_imgvars img_var, t_point **grid)
{
	int	x;
	int	y;

	y = 0;
	while (y < img_var.h)
	{
		x = 0;
		while (x < img_var.w - 1)
		{
			draw_line(addr, img_var, grid[y][x], grid[y][x + 1]);
			x++;
		}
		y++;
	}
	x = 0;
	while (x < img_var.w)
	{
		y = 0;
		while (y < img_var.h - 1)
		{
			draw_line(addr, img_var, grid[y][x], grid[y + 1][x]);
			y++;
		}
		x++;
	}
}

// On Linux with X11. Use 53 on macOS.
// #define ESC_KEY 65307

int	handle_keypress(int keycode, t_imgvars *vars)
{
	if (keycode == 65307)
	{
		printf("ESC pressed. Cleaning up and exiting.\n");
		if (vars->win)
			mlx_destroy_window(vars->mlx, vars->win);
		if (vars->img)
			mlx_destroy_display(vars->mlx);
		//free(vars->mlx);
		if (vars->grid)
			free_grid(vars->grid, vars->h);
		exit(0);
	}
	return (0);
}

int	handle_close(t_imgvars *vars)
{
	printf("Window closed. Cleaning up and exiting.\n");
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->img)
		mlx_destroy_display(vars->mlx);
	//free(vars->mlx);
	if (vars->grid)
		free_grid(vars->grid, vars->h);
	exit(0);
	return (0);
}
