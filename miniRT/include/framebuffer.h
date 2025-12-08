#ifndef FRAMEBUFFER_H
# define FRAMEBUFFER_H

# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <math.h>
# include "scene.h"
# include "object.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef struct s_inputdata
{
    t_obj_type  obj_type;
    double      pos[3];
    double      ndir[3];
    double      radius; // only for sphere and cylinder
    double      height; // only fo cylinder
    double      albedo[3];
}   t_inputdata;

typedef struct s_framebuffer
{
    size_t w; // width
	size_t h; // height
    uint8_t *data; // the whole array of pixels info

}	t_framebuffer;

// algebra.c vector operations
double  vdotn(const double v1[3], const double v2[3], size_t n);
double	vnorm3(const double v[3]);
void	vnormalize3(const double v[3], double vnrm[3]);
void	cross3(const double a[3], const double b[3], double result[3]);
void    rv(const double vin[3], const double x[3], const double y[3],
               const double z[3], double vout[3]);
void    rv_inv(const double vin[3], const double x[3], const double y[3],
                   const double z[3], double vout[3]);
void rotate_x(double v[3], double theta);
void rotate_y(double v[3], double theta);
void rotate_z(double v[3], double theta);

// helper1.c 
void point(const double o[3], const double d[3], const double t, double p[3]);
void swap2(double *t0, double *t1);

// shade lights etc
void shade(const t_scene *scene, const t_hit *hit, double out[3]);

//*************** */

int		fb_init(t_framebuffer *fb, size_t w, size_t h);
void	fb_free(t_framebuffer *fb);
int		ppm_write(const char *path, const t_framebuffer *fb);

void    d_ij(const t_camera *camera, int i, int j, double dij[3]);
void    camera_set(t_camera *camera, int w, int h, double fov, const double f_in[3], const double c[3]);


// build objects
void    obj_sphere(t_obj *obj, t_inputdata *inputdata);
void    obj_plane(t_obj *obj, t_inputdata *inputdata);
void    obj_cylinder(t_obj *obj, t_inputdata *inputdata);

void    coloring_object(t_framebuffer *fb, const t_obj *obj, const t_camera *camera, t_scene *scene);

#endif