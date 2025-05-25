#include "fdf.h"
/*
*	TODO:
*	NORM checking
*	compile with proper flags -Wall -Werror -Wextra -> update Makefile
*	./fdf 42.fdf as input
*
*/

// void	init_and_run(t_imgvars *img_var, t_point **grid, int win_size)
// {
// 	char *addr;

// 	addr = set_mlx(img_var, grid, win_size);
// 	draw_grid(addr, *img_var, grid);
// 	mlx_put_image_to_window(img_var->mlx, img_var->win, img_var->img, 0, 0);
// 	mlx_key_hook(img_var->win, handle_keypress, img_var);
// 	mlx_hook(img_var->win, 17, 0, handle_close, img_var);
// 	mlx_loop(img_var->mlx);
// }

int main(int argc, char *argv[])
{
	t_imgvars	img_var;
	t_point		**grid;
	t_size		size;
	int			win_size;

	win_size = 1000;

	// argv[1] = "ones";
	grid_size(&img_var.w, &img_var.h, argv[1]);
	printf("h = %d    w = %d \n", img_var.h, img_var.w);

	grid = grid2d(img_var.w, img_var.h, argv[1]);

	// make projection
	double cover = 1;
	double zoom = (win_size * cover) / ((img_var.h + img_var.w));
	printf("zoom = %f \n", zoom);
	// zoom = 0.9999;

	//zoom = 1.;
	get_size(&size, grid, img_var.w, img_var.h);
	img_var.max_z = size.max_z;

	project_grid(grid, img_var, zoom);
	// make fit: zoom and translation to the midle of the window
	get_size(&size, grid, img_var.w, img_var.h);

	printf("Max z = %d \n", size.max_z);
	// calculate zoom to fit window
	// translate to the middle of the window
	//
	// zoom_grid(grid, win_var, 10., &size);
	translate_grid(grid, win_size/2 - size.mid_x, win_size/2 - size.mid_y, img_var);
	// zoom_grid(grid, win_var, 2., &size);

	char *addr;

	addr = set_mlx(&img_var, grid, win_size);
	draw_grid(addr, img_var, grid);
	mlx_put_image_to_window(img_var.mlx, img_var.win, img_var.img, 0, 0);
	mlx_key_hook(img_var.win, handle_keypress, &img_var);
	mlx_hook(img_var.win, 17, 0, handle_close, &img_var);
	mlx_loop(img_var.mlx);

	// init_and_run(&img_var, grid, win_size);
	free_grid(grid, img_var.h);
	return (0);
}
