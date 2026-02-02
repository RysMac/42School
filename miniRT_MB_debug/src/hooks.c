/* #include "miniRT.h"
#include <stdlib.h>
# include <mlx.h>
#include <stdio.h>

void	cleanup(t_data *data)
{
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
		free(data->mlx);
	fb_free(&data->fb);
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
	printf("Rozpoczynam inicjalizację okna...\n");

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

	// DEBUG – najważniejsze informacje o buforze MLX
	printf("Bufor MLX: bpp = %d, line_len = %d, endian = %d\n",
	       data->bpp, data->line_len, data->endian);
	printf("Oczekiwane: bpp=32, line_len ≈ %d (WIDTH*4)\n", WIDTH * 4);

	fb_init(&data->fb, WIDTH, HEIGHT);
	data->fb.data = (uint8_t *)data->addr;   // Podpięcie bufora MLX – MUSI być TU

	printf("Wywołuję coloring_object...\n");

	coloring_object(&data->fb, &data->scene.camera, &data->scene);

	printf("Rendering zakończony – wrzucam obraz do okna\n");

	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);

	// Hooki
	mlx_key_hook(data->win, key_hook, data);
	mlx_hook(data->win, 17, 0, close_hook, data);   // zamykanie okna (X)
}

*/

#include "miniRT.h"
#include <stdlib.h>
# include "../minilibx-linux/mlx.h"

void	cleanup(t_data *data)
{
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
		free(data->mlx);
	fb_free(&data->fb);
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
	data->fb.data = (uint8_t *)data->addr;   // Podpięcie bufora MLX – MUSI być TU

	coloring_object(&data->fb, &data->scene.camera, &data->scene, data->endian, data->line_len);

	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);

	// Hooki
	mlx_key_hook(data->win, key_hook, data);
	mlx_hook(data->win, 17, 0, close_hook, data);   // zamykanie okna (X)
}
