#include "miniRT.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		exit_error("Usage: ./miniRT scene.rt");
	parse_file(argv[1], &data.scene);
	init_and_render(&data);

	printf("amount of objects %li \n", sizeof(&data.scene.objects)/sizeof(data.scene.objects[0]) );

	const char *path = "view.ppm";
    if (ppm_write(path, &(data.fb)) == 1)
        printf("wrong ppm_write\n");
    printf("end of program \n");

	mlx_key_hook(data.win, key_hook, &data);
	mlx_hook(data.win, 17, 0, close_hook, &data);
	mlx_loop(data.mlx);
	return (0);
}
