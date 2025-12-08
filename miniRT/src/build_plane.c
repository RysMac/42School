#include "../include/framebuffer.h"

// n, x, y are local plane basis needed for transformation matrix R
// check if n is normalized
void    plane_basis(const double n[3], double x[3], double y[3])
{
    double u[3];

    if (fabs(n[1]) < 0.99)
    {
        u[0] = 0.0;
        u[1] = 1.0;
        u[2] = 0.0;
    }
    else
    {
        u[0] = 1.0;
        u[1] = 0.0;
        u[2] = 0.0;
    }
    cross3(u, n, x);
    vnormalize3(x, x);
    cross3(n, x, y);
}

static int intersect_plane(const t_obj *obj, const t_ray *ray, t_hit *hit)
{
    double o[3];
    double c[3];
    double x[3];
    double y[3];
    double d[3];
    double t;

    plane_basis(obj->pos.dir, x, y);
    // ray->o is origin of camera obj->pos.pos is a point on the plane
    o[0] = ray->o[0] - obj->pos.pos[0];
    o[1] = ray->o[1] - obj->pos.pos[1];
    o[2] = ray->o[2] - obj->pos.pos[2];

    rv(o, x, y, obj->pos.dir, c);
    rv(ray->d, x, y, obj->pos.dir, d);
    if ( fabs(d[2]) < 1e-6 ) // parallel
        return (0);
    else
        t = - c[2] / d[2];
    if (t < 1e-4)
        return (0);
    // hit point in plane/local coords
    point(c, d, t, hit->p);
    if (fabs(hit->p[0]) > 30 || fabs(hit->p[1]) > 30)
        return (0);
    // go back to world frame
    rv_inv(hit->p, x, y, obj->pos.dir, hit->p);
    // add translation
    hit->obj = obj;
    hit->p[0] = obj->pos.pos[0] + hit->p[0];
    hit->p[1] = obj->pos.pos[1] + hit->p[1];
    hit->p[2] = obj->pos.pos[2] + hit->p[2];
    hit->t = t;
    hit->n[0] = obj->pos.dir[0];
    hit->n[1] = obj->pos.dir[1];
    hit->n[2] = obj->pos.dir[2];
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

void    obj_plane(t_obj *obj, t_inputdata *inputdata)
{
    double tmp[3];

    obj->type = OBJ_PLANE;
    // center point position in global frame
    obj->pos.pos[0] = inputdata->pos[0];
    obj->pos.pos[1] = inputdata->pos[1];
    obj->pos.pos[2] = inputdata->pos[2];
    // normal direction (needed only for plane)
    vnormalize3(inputdata->ndir, tmp);
    obj->pos.dir[0] = tmp[0];
    obj->pos.dir[1] = tmp[1];
    obj->pos.dir[2] = tmp[2];
    obj->intersect = intersect_plane;
    obj->albedo[0] = inputdata->albedo[0];
    obj->albedo[1] = inputdata->albedo[1];
    obj->albedo[2] = inputdata->albedo[2];
}
    