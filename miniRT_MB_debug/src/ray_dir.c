#include "../include/framebuffer.h"

// horizontal sweep
static double xs_i(int i, int w, double fovx)
{
    double  u0;
    double  u;
    double  fovx_rad;

    fovx_rad = fovx * M_PI / 180.0;
    u0 = (double)(i + 0.5) / (double)w; // (0, 1)
    u = 2.0 * u0 - 1.0;                 // (-1, 1)

    return u * tan(fovx_rad / 2);

}

// vertical sweep
static double ys_i(int i, int h, double fovy)
{
    double  v0;
    double  v;
    double  fovy_rad;

    fovy_rad = fovy * M_PI / 180.0;
    v0 = (double)(i + 0.5) / (double)h; // (0, 1)
    v = 1 - 2.0 * v0;                 // (-1, 1)

    return v * tan(fovy_rad / 2);

}

// direction in world space 3D => no need to make transformation with R
void d_ij(const t_camera *camera, int i, int j, double dij[3])
{
    double  xsi;
    double  ysj;
    double  d[3];

    xsi = xs_i(i, camera->w, camera->fovx);
    ysj = ys_i(j, camera->h, camera->fovy);

    d[0] = camera->f[0] + xsi * camera->r[0] + ysj * camera->u[0];
    d[1] = camera->f[1] + xsi * camera->r[1] + ysj * camera->u[1];
    d[2] = camera->f[2] + xsi * camera->r[2] + ysj * camera->u[2];
    vnormalize3(d, dij);
}

// ray -> this function is not needed 
// void r_ij(const t_camera *camera, int i, int j, double t, double rij[3])
// {
//     double  dij[3];

//     d_ij(camera, i, j, dij);
//     rij[0] = camera->c[0] + t * dij[0];
//     rij[1] = camera->c[1] + t * dij[1];
//     rij[2] = camera->c[2] + t * dij[2];
// }