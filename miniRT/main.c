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

t_inputdata inputdata(t_obj_type type, double pos[3], double ndir[3], double albedo[3], double radius, double height)
{
    t_inputdata data;

    data.obj_type = type;
    data.pos[0] = pos[0];
    data.pos[1] = pos[1];
    data.pos[2] = pos[2];
    data.ndir[0] = ndir[0];
    data.ndir[1] = ndir[1];
    data.ndir[2] = ndir[2];
    data.albedo[0] = albedo[0];
    data.albedo[1] = albedo[1];
    data.albedo[2] = albedo[2];
    data.radius = radius;
    data.height = height;

    return (data);
}

int build_objects(t_obj *object, t_inputdata *data)
{
    if (data->obj_type == OBJ_PLANE)
    {
        obj_plane(object, data);
        return (1);
    }
    else if (data->obj_type == OBJ_SPHERE)
    {
        obj_sphere(object, data);
        return (1);
    }
    else if (data->obj_type == OBJ_CYLINDER)
    {
        obj_cylinder(object, data);
        return (1);
    }
    else
        return (0);
}

int	main(int argc, char **argv)
{
    const size_t w = 800;
    const size_t h = 600;

    t_framebuffer   fb_ppm;
    t_data	data;

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
    
    // this function is related to mlx
    init_and_render(&data);

    // // here ppm_write should be replaced by mlx...
    const char *path = "view.ppm";
    if (ppm_write(path, &fb_ppm) == 1)
        printf("wrong ppm_write\n");
    printf("end of program \n");

    // free(data.scene.objects);

	mlx_key_hook(data.win, key_hook, &data);
	mlx_hook(data.win, 17, 0, close_hook, &data);
	mlx_loop(data.mlx);
    return (0);
}