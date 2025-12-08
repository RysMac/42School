#include <stdlib.h>
#include <stdio.h>
#include "framebuffer.h"

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

int main()
{
    const size_t w = 600;
    const size_t h = 600;

    t_framebuffer   fb;
    t_camera        camera;
    t_obj           *obj;
    t_inputdata     *alldata;
    t_scene         scene;
    
    // camera direction
    double f_in[3] = { 0.0, 0.0, -1.0 };
    // rotate_x(f_in, 20 * M_PI / 180);
    // rotate_y(f_in, 10 * M_PI / 180);
    // camera center
    const double c[3] = { 0.0, 0.0, 40.0 };
    double fovx = 100.0;
    camera_set(&camera, w, h, fovx, f_in, c);
    
    // define some objets sphere, plane, cylinder -> for now hard coded
    size_t n = 7;
    obj = malloc(sizeof(t_obj) * n );
    alldata = malloc(sizeof(t_inputdata) * n );

    // SPHERES
    // sphere normal direction (not needed for sphere so can be any)
    double ndir[3] = { 0.0, 0.0, 1.0 };
    // position of the sphere center 1 2...
    double sc0[3] = {20.0, 20.0, -0.0 };
    double sc1[3] = { -20.0, 20.0, -0.0 };
    double sc2[3] = { 0.0, 0.0, 0.0 };
    double sphere_albedo[3] = {1., 0., 0.};
    alldata[0] = inputdata(OBJ_SPHERE, sc0, ndir, sphere_albedo, 10., 0.);
    alldata[1] = inputdata(OBJ_SPHERE, sc1, ndir, sphere_albedo, 15., 0.);
    alldata[2] = inputdata(OBJ_SPHERE, sc2, ndir, sphere_albedo, 10., 0.);
    // PLANES
    // plane needs osition + normal direction
    double sc3[3] = { 0.0, -20.0, 0.0 };
    double sc4[3] = { 0.0, 25.0, -20.0 };
    double plane_albedo[3] = {0., 0., 1.};
    rotate_x(ndir, -15 * M_PI / 180);
    // rotate_y(ndir, 30 * M_PI / 180);
    alldata[3] = inputdata(OBJ_PLANE, sc3, ndir, plane_albedo, 0., 0.);
    alldata[4] = inputdata(OBJ_PLANE, sc4, ndir, plane_albedo, 0., 0.);
    // CYLINDERS
    double sc5[3] = { 0.0, 5.0, 5.0 };
    double ndirc[3] = { 0.0, 1.0, 0.0 };
    double cylinder_albedo[3] = {0.1, 0.5, 0.4};
    rotate_z(ndirc, -35 * M_PI / 180);
    alldata[5] = inputdata(OBJ_CYLINDER, sc5, ndirc, cylinder_albedo, 5., 80.);
    rotate_z(ndirc, -60 * M_PI / 180);
    alldata[6] = inputdata(OBJ_CYLINDER, sc5, ndirc, cylinder_albedo, 5., 80.);

    for (int i = 0; i < n; i++)
    {
        build_objects(&obj[i], &alldata[i]);
    }

    // obj_cylinder(&obj[5], &cylinder1);
    printf("object set done \n");
    scene.objects = obj;
    scene.ambient.ambient_color[0] = 1.0;
    scene.ambient.ambient_color[1] = 1.0;
    scene.ambient.ambient_color[2] = 1.0;
    scene.ambient.ambient_ratio = 0.4;
    scene.camera = camera;
    scene.light.brightness = 1.0;
    // the same as camera forward direction
    scene.light.pos[0] = 40.0;
    scene.light.pos[1] = 5.0;
    scene.light.pos[2] = 15.0;
    scene.count = n;
    printf("scene set done \n");

    if (fb_init(&fb, w, h))
        return (1);   

    coloring_object(&fb, obj, &camera, &scene);

    const char *path = "view.ppm";
    if (ppm_write(path, &fb) == 1)
        printf("wrong ppm_write\n");
    printf("end of program \n");
    return (0);
}