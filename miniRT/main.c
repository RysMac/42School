#include <stdlib.h>
#include <stdio.h>
#include "framebuffer.h"
#include "miniRT.h"

double print_vector3(const double v[3])
{
	for (int i = 0; i < 3; i++)
		printf(" %f ", v[i]);
	printf("\n");
}

int main(int argc, char **argv)
{
	const size_t w = 800;
	const size_t h = 600;

	t_framebuffer fb_ppm;
	t_data data;

	data.mlx = NULL;
	data.win = NULL;
	data.img = NULL;
	data.addr = NULL;
	data.bpp = 0;
	data.line_len = 0;
	data.endian = 0;

	if (argc != 2)
		exit_error("Usage: ./miniRT scene.rt");
	parse_file(argv[1], &data.scene); // add here sizes w, h

	if (fb_init(&fb_ppm, w, h)) // fb size based on camera w, h
		return (1);
	coloring_object(&fb_ppm, &data.scene.camera, &data.scene);

	const char *path = "view.ppm";
	if (ppm_write(path, &fb_ppm) == 1)
		printf("wrong ppm_write\n");
	printf("end of program \n");

	fb_free(&fb_ppm);
	// free(data.scene.objects);

	// this function is related to mlx
	init_and_render(&data);
	mlx_key_hook(data.win, key_hook, &data);
	mlx_hook(data.win, 17, 0, close_hook, &data);
	mlx_loop(data.mlx);
	return (0);
}
