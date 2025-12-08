#include "../include/framebuffer.h"

static void n_sphere(const double o[3], const double p[3], const double r, double n[3])
{
    n[0] = (p[0] - o[0]) / r;
    n[1] = (p[1] - o[1]) / r;
    n[2] = (p[2] - o[2]) / r;
}

// returns 1 if found intersection 0 otherwise
static int intersect_sphere(const t_obj *obj, const t_ray *ray, t_hit *hit)
{
    double oc[3];
    double t0;
    double t1;

    oc[0] = ray->o[0] - obj->pos.pos[0];
    oc[1] = ray->o[1] - obj->pos.pos[1];
    oc[2] = ray->o[2] - obj->pos.pos[2];

    double r = obj->shape.sphere.radius;
    double a = vdotn(ray->d, ray->d, 3);
    double b = 2 * vdotn(oc, ray->d, 3);
    double c = vdotn(oc, oc, 3) - r * r;

    double d = b * b - 4 * a * c;
    if (d < 0) // no hit
        return (0); 
    double dsqrt = sqrt(d);
    t0 = (- b + dsqrt) / (2 * a);
    t1 = (- b - dsqrt) / (2 * a);
    swap2(&t0, &t1);

    double t_hit;
    if (t0 >= 1e-6)
        t_hit = t0;
    else if (t1 >= 1e-6)
        t_hit = t1;
    else
        return 0; // both behind camera/near plane
    hit->obj = obj;
    hit->t = t_hit;
    point(ray->o, ray->d, t_hit, hit->p);
    n_sphere(obj->pos.pos, hit->p, r, hit->n);
    vnormalize3(hit->n, hit->n);
    double d_dot_n = vdotn(ray->d, hit->n, 3);
    if (d_dot_n > 0.0)
    {
        hit->n[0] = -hit->n[0];
        hit->n[1] = -hit->n[1];
        hit->n[2] = -hit->n[2];
    }
    return (1);
}

// this one general function or separate function for each object
void    obj_sphere(t_obj *obj, t_inputdata *inputdata)
{
    obj->type = OBJ_SPHERE;
    // center point position in global frame
    obj->pos.pos[0] = inputdata->pos[0];
    obj->pos.pos[1] = inputdata->pos[1];
    obj->pos.pos[2] = inputdata->pos[2];
    // normal direction (needed only for plane)
    obj->pos.dir[0] = inputdata->ndir[0];
    obj->pos.dir[1] = inputdata->ndir[1];
    obj->pos.dir[2] = inputdata->ndir[2];
    obj->shape.sphere.radius = inputdata->radius;
    obj->intersect = intersect_sphere;
    obj->albedo[0] = inputdata->albedo[0];
    obj->albedo[1] = inputdata->albedo[1];
    obj->albedo[2] = inputdata->albedo[2];

}