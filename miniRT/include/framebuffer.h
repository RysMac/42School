/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   framebuffer.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrys <mrys@student.42warsaw.pl>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 11:38:40 by mrys              #+#    #+#             */
/*   Updated: 2026/03/03 11:56:59 by mrys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAMEBUFFER_H
# define FRAMEBUFFER_H

# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <math.h>
# include "scene.h"
# include "object.h"
# include "framebuffer.h"

# ifndef M_PI
# define M_PI 3.14159265358979323846
# endif

typedef struct s_cyl_ctx	t_cyl_ctx;

typedef struct s_inputdata
{
	t_obj_type	obj_type;
	double		pos[3];
	double		ndir[3];
	double		radius;
	double		height;
	double		albedo[3];
}	t_inputdata;

/*
	w 		- witdh
	h 		- height
	data 	- the whole array of pixels 
*/
typedef struct s_framebuffer
{
	size_t	w;
	size_t	h;
	uint8_t	*data;
}	t_framebuffer;

// algebra.c vector operations
double		vdotn(const double v1[3], const double v2[3], size_t n);
double		vnorm3(const double v[3]);
void		vnormalize3(const double v[3], double vnrm[3]);
void		cross3(const double a[3], const double b[3], double result[3]);
t_vec3		rv(const double vin[3], const double x[3], const double y[3],
				const double z[3]);
t_vec3		rv_inv(const double vin[3], const double x[3], const double y[3],
				const double z[3]);
void		rotate_x(double v[3], double theta);
void		rotate_y(double v[3], double theta);
void		rotate_z(double v[3], double theta);
void		vcopy3(const t_vec3 vin, double vout[3]);

// helper1.c
void		point(const double o[3], const double d[3],
				const double t, double p[3]);
void		swap2(double *t0, double *t1);

// shade lights etc
int			check_hit(const t_hit *hit, double color[3]);
void		ambient_term(const t_scene *scene, const t_hit *hit, double out[3]);
void		shade(const t_scene *scene, const t_hit *hit, double out[3]);

//*************** */
int			fb_init(t_framebuffer *fb, size_t w, size_t h);
void		fb_free(t_framebuffer *fb);
int			ppm_write(const char *path, const t_framebuffer *fb);

void		d_ij(const t_camera *camera, int i, int j, double dij[3]);
void		camera_set(t_camera *camera,
				double fov, const double f_in[3], const double c[3]);

// build objects
void		obj_sphere(t_obj *obj, t_inputdata *inputdata);
void		obj_plane(t_obj *obj, t_inputdata *inputdata);
void		obj_cylinder(t_obj *obj, t_inputdata *inputdata);

// cylinderh1
void		cylinder_basis(const double n[3], double x[3], double y[3]);
void		cyl_init_ctx(t_cyl_ctx *k, const t_obj *obj);
void		cyl_build_basis(t_cyl_ctx *k, const t_obj *obj);
void		cyl_set_local_ray(t_cyl_ctx *k, const t_obj *obj,
				const t_ray *ray);
void		cyl_side_accept(t_cyl_ctx *k, double t);
// cylinderh2
void		cyl_intersect_side(t_cyl_ctx *k);
void		cyl_cap_accept(t_cyl_ctx *k, double t, int top);
void		cyl_intersect_caps(t_cyl_ctx *k);
void		cyl_choose_best(t_cyl_ctx *k);
void		cyl_compute_local_pn(t_cyl_ctx *k);
// vector calculus
void		vec_sub(const double a[3], const double b[3], double out[3]);
double		vec_dot(const double a[3], const double b[3]);
double		vec_len(const double v[3]);
void		vec_scale(const double v[3], double s, double out[3]);
void		vec_clamp01(double v[3]);
#endif