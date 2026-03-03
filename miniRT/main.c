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
	data.w = 100;
	data.h = 50;
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
	printf("data w,h, %d  %d \n", data.w, data.h);
	printf("camera w,h, %i  %i \n", *data.scene.camera.w , *data.scene.camera.h);
	printf("fb w,h, %ld  %ld \n", data.fb.w, data.fb.h);
	mlx_loop(data.mlx);
	
	return (0);
}
