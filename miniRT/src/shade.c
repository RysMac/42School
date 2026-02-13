#include "framebuffer.h"
#include <math.h>

void vec_sub(const double a[3], const double b[3], double out[3])
{
    out[0] = a[0] - b[0];
    out[1] = a[1] - b[1];
    out[2] = a[2] - b[2];
}

double vec_dot(const double a[3], const double b[3])
{
    return (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]);
}

double vec_len(const double v[3])
{
    return sqrt(vec_dot(v, v));
}

void vec_scale(const double v[3], double s, double out[3])
{
    out[0] = v[0] * s;
    out[1] = v[1] * s;
    out[2] = v[2] * s;
}

void vec_clamp01(double v[3])
{
    for (int i = 0; i < 3; i++)
    {
        if (v[i] < 0.0) v[i] = 0.0;
        if (v[i] > 1.0) v[i] = 1.0;
    }
}

static void ambient_term(const t_scene *scene, const t_hit *hit, double out[3])
{
    const double *ka = hit->obj->albedo;        /* assumed [0,1] */
    const t_ambient *A = &scene->ambient;       /* assumed colors [0,1] */
    const double ratio = A->ambient_ratio;      /* [0,1] */

    out[0] = ratio * ka[0] * A->ambient_color[0];
    out[1] = ratio * ka[1] * A->ambient_color[1];
    out[2] = ratio * ka[2] * A->ambient_color[2];
}

/*
 * Improvements applied:
 *  1) No skipping (obj == hit->obj) in shadow tests.
 *  2) Shadow origin bias uses +/- normal depending on dot(n, L).
 *  3) Increased epsilon (1e-4).
 */
#define SHADOW_EPS 1e-3

void shade(const t_scene *scene, const t_hit *hit, double color[3])
{
    double Ca[3] = {0.0, 0.0, 0.0};
    double Cd[3] = {0.0, 0.0, 0.0};

    double to_light[3];
    double Ldir[3];
    double dist_to_light;

    t_ray  shadow;
    int    in_shadow = 0;

    if (!hit || !hit->obj)
    {
        color[0] = color[1] = color[2] = 0.0;
        return;
    }

    /* Ambient always contributes */
    ambient_term(scene, hit, Ca);

    /* Build direction to light */
    vec_sub(scene->light.pos, hit->p, to_light);
    dist_to_light = vec_len(to_light);
    if (dist_to_light < 1e-9)
    {
        color[0] = Ca[0];
        color[1] = Ca[1];
        color[2] = Ca[2];
        vec_clamp01(color);
        return;
    }
    vec_scale(to_light, 1.0 / dist_to_light, Ldir);

    /*
     * Bias the shadow ray origin away from the surface in the direction that
     * reduces self-intersection. If dot(n, Ldir) is negative, push along -n.
     * This is safer than always +n when you are inside objects / flipped normals.
     */
    {
        const double ndotl = vec_dot(hit->n, Ldir);
        const double sign = (ndotl >= 0.0) ? 1.0 : -1.0;

        shadow.o[0] = hit->p[0] + sign * SHADOW_EPS * hit->n[0];
        shadow.o[1] = hit->p[1] + sign * SHADOW_EPS * hit->n[1];
        shadow.o[2] = hit->p[2] + sign * SHADOW_EPS * hit->n[2];
    }

    shadow.d[0] = Ldir[0];
    shadow.d[1] = Ldir[1];
    shadow.d[2] = Ldir[2];

    /* Hard shadow test: ANY hit before the light blocks diffuse contribution */
    for (size_t i = 0; i < scene->count; i++)
    {
        const t_obj *obj = &scene->objects[i];
        t_hit tmp;

        if (obj->intersect(obj, &shadow, &tmp))
        {
			// if (tmp.t >= TMIN && tmp.t <= dist_to_light - TMIN)
            if (tmp.t >= 1e-4 && tmp.t <= dist_to_light - 1e-4)
            {
                in_shadow = 1;
                break;
            }
        }
    }

    if (!in_shadow)
    {
        const double ndotl = vec_dot(hit->n, Ldir);
        if (ndotl > 0.0)
        {
            const double intensity = ndotl * scene->light.brightness;

            /* assumes albedo/light colors are [0,1] */
            Cd[0] = intensity * hit->obj->albedo[0] * scene->light.color[0];
            Cd[1] = intensity * hit->obj->albedo[1] * scene->light.color[1];
            Cd[2] = intensity * hit->obj->albedo[2] * scene->light.color[2];
        }
    }

    color[0] = Ca[0] + Cd[0];
    color[1] = Ca[1] + Cd[1];
    color[2] = Ca[2] + Cd[2];

    vec_clamp01(color);
}
