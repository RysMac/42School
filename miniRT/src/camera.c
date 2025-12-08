// #include "scene.h"
#include "framebuffer.h"

void camera_basis(t_camera *camera, const double f_in[3])
{
    double f[3];
    double r[3];
    double u[3];
    double ud[3];
    double ua[3];

    ud[0] = 0.0;
    ud[1] = 1.0;
    ud[2] = 0.0;
    ua[0] = 0.0;
    ua[1] = 0.0;
    ua[2] = 1.0;

    vnormalize3(f_in, f); 
    // f cannnot be colinear with u_up
    double dot = f[0]*ud[0] + f[1]*ud[1] + f[2]*ud[2];
    const double *up = (fabs(dot) > 0.99) ? ua : ud;
    
    cross3(f, up, r);
    vnormalize3(r, r);
    cross3(r, f, u);
    vnormalize3(u, u);

    for (int i = 0; i < 3; ++i)
    {
        camera->f[i] = f[i];
        camera->r[i] = r[i];
        camera->u[i] = u[i];
    }
}

void camera_set(t_camera *camera, int w, int h, double fovx,
            const double f_in[3], const double c[3])
{
    double  ar;
    double  fovx_rad;

    ar = (double)w / (double)h;
    fovx_rad = fovx * M_PI / 180.0;
    camera->w = w;
    camera->h = h;
    camera->fovx = fovx;
    camera->fovy = (2 * atan(tan(fovx_rad / 2) / ar)) * 180.0 / M_PI;
    for (int i = 0; i < 3; ++i)
    {
        camera->c[i] = c[i];
    }

    camera_basis(camera, f_in);

}