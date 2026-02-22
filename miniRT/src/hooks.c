/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrys <mrys@student.42warsaw.pl>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 12:21:48 by mrys              #+#    #+#             */
/*   Updated: 2026/02/22 12:24:20 by mrys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stdlib.h>
#include "../minilibx-linux/mlx.h"

// there should not be fb_free(&data->fb);
void	cleanup(t_data *data)
{
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
		free(data->mlx);
	free(data->scene.objects);
	exit(0);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == ESC_KEY)
		cleanup(data);
	return (0);
}

int	close_hook(t_data *data)
{
	cleanup(data);
	return (0);
}

void	init_and_render(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		exit_error("mlx_init failed");
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "miniRT");
	if (!data->win)
		exit_error("mlx_new_window failed");
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img)
		exit_error("mlx_new_image failed");
	data->addr = mlx_get_data_addr(data->img, &data->bpp,
			&data->line_len, &data->endian);
	if (!data->addr)
		exit_error("mlx_get_data_addr failed");
	fb_init(&data->fb, WIDTH, HEIGHT);
	data->fb.data = (uint8_t *)data->addr;
	coloring_object_mlx(&data->fb, &data->scene.camera,
		&data->scene, data->bpp, data->line_len, data->endian);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	mlx_key_hook(data->win, key_hook, data);
	mlx_hook(data->win, 17, 0, close_hook, data);
}
