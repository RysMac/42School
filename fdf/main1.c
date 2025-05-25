#include "mlx/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include "fdf.h"

int	main(void)
{
	t_imgvars	img_var;
	t_point **grid;
	char *addr;
	int		win_size = 600;

	// Initialize MiniLibX
	// Get access to the pixel buffer
	addr = set_mlx( &img_var, grid, win_size);
	printf("line length = %d \n", img_var.line_length);
	// Compute pixel position (100, 100)
	for (int i = 0; i < 40; i++)
	{
		int x = 10 * i;
		int y = 10 * i;
		char *dst = addr + (y * img_var.line_length + (x * (img_var.bpp / 8)) );
		// Set pixel color: red (0xFF0000)
		*(unsigned int *)dst = 0xFF0000;
	}

	// Draw the image to the window
	mlx_put_image_to_window(img_var.mlx, img_var.win, img_var.img, 0, 0);

	// Keep window open
	mlx_loop(img_var.mlx);
}
