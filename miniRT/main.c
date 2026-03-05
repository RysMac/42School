#include <stdlib.h>
#include <stdio.h>
#include "framebuffer.h"
#include "miniRT.h"

int main(int argc, char **argv)
{
	t_data data;

	data.mlx = NULL;
	data.win = NULL;
	data.img = NULL;
	data.addr = NULL;
	data.bpp = 0;
	data.line_len = 0;
	data.endian = 0;
	data.w = 800;
	data.h = 500;
	data.scene.w = data.w;
	data.scene.h = data.h;
	data.scene.camera.w = &data.w;
	data.scene.camera.h = &data.h;

	if (argc != 2)
		exit_error("Usage: ./miniRT scene.rt");
	parse_file(argv[1], &data.scene);

	init_and_render(&data);
	// mlx_key_hook(data.win, key_hook, &data);
	// mlx_hook(data.win, 17, 0, close_hook, &data);
	mlx_loop(data.mlx);
	
	return (0);
}
