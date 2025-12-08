#include "framebuffer.h"

static void vec_sub(const double a[3], const double b[3], double out[3])
{
    out[0] = a[0] - b[0];
    out[1] = a[1] - b[1];
    out[2] = a[2] - b[2];
}

static double vec_dot(const double a[3], const double b[3])
{
    return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
}

static double vec_len(const double v[3])
{
    return sqrt(vec_dot(v, v));
}

static void vec_scale(const double v[3], double s, double out[3])
{
    out[0] = v[0] * s;
    out[1] = v[1] * s;
    out[2] = v[2] * s;
}

static void vec_add(const double a[3], const double b[3], double out[3])
{
    out[0] = a[0] + b[0];
    out[1] = a[1] + b[1];
    out[2] = a[2] + b[2];
}

static void vec_clamp01(double v[3])
{
    for (int i = 0; i < 3; ++i)
    {
        if (v[i] < 0.0) v[i] = 0.0;
        if (v[i] > 1.0) v[i] = 1.0;
    }
}

// out = ambient contribution (RGB in [0,1])
void ambient_term(const t_scene *scene, const t_hit *hit, double out[3])
{
    const double *ka = hit->obj->albedo;              // object albedo
    const t_ambient *A = &scene->ambient;
    double s = A->ambient_ratio;

    out[0] = s * A->ambient_color[0] * ka[0];
    out[1] = s * A->ambient_color[1] * ka[1];
    out[2] = s * A->ambient_color[2] * ka[2];
}

// returns distance to light; L is normalized direction from p to light.
// if light is exactly at p, L = (0,0,0) and distance = 0.
double get_light_vector(const t_scene *scene, const double p[3], double L[3])
{
    double to_light[3];
    vec_sub(scene->light.pos, p, to_light);   // to_light = light.pos - p

    double dist = vec_len(to_light);
    if (dist > 0.0)
    {
        double inv = 1.0 / dist;
        L[0] = to_light[0] * inv;
        L[1] = to_light[1] * inv;
        L[2] = to_light[2] * inv;
    }
    else
    {
        L[0] = 0.0;
        L[1] = 0.0;
        L[2] = 0.0;
    }
    return dist;
}

#define SHADOW_EPS 1e-4

void shade(const t_scene *scene, const t_hit *hit, double out[3])
{
    double Ca[3];          // ambient
    double Cd[3] = {0.0, 0.0, 0.0}; // diffuse
    double L[3];
    double dist_to_light;
    double ndotl;
    double intensity;
    const double *kd = hit->obj->albedo;

    // 1) Ambient term
    ambient_term(scene, hit, Ca);

    // 2) Light direction + distance
    dist_to_light = get_light_vector(scene, hit->p, L);

    // If light is exactly at p, just use ambient (degenerate).
    if (dist_to_light <= 0.0)
    {
        out[0] = Ca[0];
        out[1] = Ca[1];
        out[2] = Ca[2];
        return;
    }

    // 3) Hard shadow test: cast a ray from p + eps * n toward L
    t_ray shadow;
    shadow.o[0] = hit->p[0] + SHADOW_EPS * hit->n[0];
    shadow.o[1] = hit->p[1] + SHADOW_EPS * hit->n[1];
    shadow.o[2] = hit->p[2] + SHADOW_EPS * hit->n[2];
    shadow.d[0] = L[0];
    shadow.d[1] = L[1];
    shadow.d[2] = L[2];

    int in_shadow = 0;
    for (size_t i = 0; i < scene->count; ++i)
    {
        const t_obj *obj = &scene->objects[i];
        t_hit tmp;

        // Optional: skip self if your intersect can report t ≈ 0 on the same surface.
        if (obj == hit->obj) continue;

        if (obj->intersect(obj, &shadow, &tmp))
        {
            if (tmp.t > SHADOW_EPS && tmp.t < dist_to_light - SHADOW_EPS)
            {
                in_shadow = 1;
                break;
            }
        }
    }

    // 4) Diffuse contribution if not in shadow
    if (!in_shadow)
    {
        ndotl = vec_dot(hit->n, L);
        if (ndotl > 0.0)
        {
            intensity = ndotl * scene->light.brightness;
            Cd[0] = intensity * kd[0];
            Cd[1] = intensity * kd[1];
            Cd[2] = intensity * kd[2];
        }
    }

    // 5) Final color = ambient + diffuse
    out[0] = Ca[0] + Cd[0];
    out[1] = Ca[1] + Cd[1];
    out[2] = Ca[2] + Cd[2];

    vec_clamp01(out);
}
