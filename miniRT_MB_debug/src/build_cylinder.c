#include "../include/framebuffer.h"

void cylinder_basis(const double n[3], double x[3], double y[3])
{
    double u[3];

    if (fabs(n[1]) < 0.9)
    {
        u[0] = 0.0; u[1] = 1.0; u[2] = 0.0;
    }
    else
    {
        u[0] = 1.0; u[1] = 0.0; u[2] = 0.0;
    }
    cross3(u, n, x);
    vnormalize3(x, x);
    cross3(n, x, y);
}

static int intersect_disk(const double center[3], const double normal[3],
                          const t_ray *ray, double radius, double *t, double hit_p[3])
{
    double oc[3];
    double denom;
    double tt;

    vec_sub(center, ray->o, oc);
    denom = vec_dot(normal, ray->d);
    if (fabs(denom) < 1e-6)
        return (0);
    tt = vec_dot(oc, normal) / denom;
    if (tt < 1e-6)
        return (0);

    hit_p[0] = ray->o[0] + tt * ray->d[0];
    hit_p[1] = ray->o[1] + tt * ray->d[1];
    hit_p[2] = ray->o[2] + tt * ray->d[2];

    double dist2 = (hit_p[0] - center[0]) * (hit_p[0] - center[0]) +
                   (hit_p[1] - center[1]) * (hit_p[1] - center[1]) +
                   (hit_p[2] - center[2]) * (hit_p[2] - center[2]);
    if (dist2 > radius * radius + 1e-6)
        return (0);

    *t = tt;
    return (1);
}

static int intersect_cylinder(const t_obj *obj, const t_ray *ray, t_hit *hit)
{
    double      x[3], y[3];
    double      o_local[3], d_local[3];
    double      a, b, c, discr;
    double      t0, t1, t_hit;
    double      hh = obj->shape.cylinder.height * 0.5;
    double      r = obj->shape.cylinder.radius;
    double      t_cap_top = 1e30, t_cap_bot = 1e30;
    double      p_top[3], p_bot[3];
    int         which = 0; // 0=side, 1=top, 2=bot

    cylinder_basis(obj->pos.dir, x, y);

    rv_inv(ray->o, x, y, obj->pos.dir, o_local);
    o_local[0] -= obj->pos.pos[0];
    o_local[1] -= obj->pos.pos[1];
    o_local[2] -= obj->pos.pos[2];

    rv_inv(ray->d, x, y, obj->pos.dir, d_local);

    // side
    a = d_local[0]*d_local[0] + d_local[1]*d_local[1];
    b = 2.0 * (o_local[0]*d_local[0] + o_local[1]*d_local[1]);
    c = o_local[0]*o_local[0] + o_local[1]*o_local[1] - r*r;

    discr = b*b - 4*a*c;
    t_hit = 1e30;
    if (discr >= 0)
    {
        double sd = sqrt(discr);
        t0 = (-b - sd)/(2*a);
        t1 = (-b + sd)/(2*a);
        if (t0 > t1) { double tmp = t0; t0 = t1; t1 = tmp; }

        if (t0 >= 1e-6) t_hit = t0;
        else if (t1 >= 1e-6) t_hit = t1;
    }

    if (t_hit < 1e29)
    {
        double z = o_local[2] + t_hit * d_local[2];
        if (z < -hh || z > hh)
            t_hit = 1e30;
    }

    // caps
    double top_c[3] = {0,0,hh};
    double bot_c[3] = {0,0,-hh};
    double n_top[3] = {0,0,1};
    double n_bot[3] = {0,0,-1};

    intersect_disk(top_c, n_top, ray, r, &t_cap_top, p_top);
    intersect_disk(bot_c, n_bot, ray, r, &t_cap_bot, p_bot);

    double t_closest = 1e30;
    if (t_hit < t_closest)     { t_closest = t_hit; which = 0; }
    if (t_cap_top < t_closest) { t_closest = t_cap_top; which = 1; }
    if (t_cap_bot < t_closest) { t_closest = t_cap_bot; which = 2; }

    if (t_closest > 1e29)
        return (0);

    hit->t = t_closest;

    double p_local[3];

    if (which == 0)
    {
        p_local[0] = o_local[0] + t_closest * d_local[0];
        p_local[1] = o_local[1] + t_closest * d_local[1];
        p_local[2] = o_local[2] + t_closest * d_local[2];
        hit->n[0] = p_local[0]; hit->n[1] = p_local[1]; hit->n[2] = 0;
        vnormalize3(hit->n, hit->n);
    }
    else if (which == 1)
    {
        hit->n[0] = 0; hit->n[1] = 0; hit->n[2] = 1;
        p_local[0] = p_top[0]; p_local[1] = p_top[1]; p_local[2] = p_top[2];
    }
    else
    {
        hit->n[0] = 0; hit->n[1] = 0; hit->n[2] = -1;
        p_local[0] = p_bot[0]; p_local[1] = p_bot[1]; p_local[2] = p_bot[2];
    }

    rv(p_local, x, y, obj->pos.dir, hit->p);
    hit->p[0] += obj->pos.pos[0];
    hit->p[1] += obj->pos.pos[1];
    hit->p[2] += obj->pos.pos[2];

    rv(hit->n, x, y, obj->pos.dir, hit->n);

    double ddn = vdotn(ray->d, hit->n, 3);
    if (ddn > 0.0)
    {
        hit->n[0] = -hit->n[0];
        hit->n[1] = -hit->n[1];
        hit->n[2] = -hit->n[2];
    }

    hit->obj = obj;

    return (1);
}

void    obj_cylinder(t_obj *obj, t_inputdata *inputdata)
{
    double tmp[3];

    obj->type = OBJ_CYLINDER;
    obj->pos.pos[0] = inputdata->pos[0];
    obj->pos.pos[1] = inputdata->pos[1];
    obj->pos.pos[2] = inputdata->pos[2];

    vnormalize3(inputdata->ndir, tmp);
    obj->pos.dir[0] = tmp[0];
    obj->pos.dir[1] = tmp[1];
    obj->pos.dir[2] = tmp[2];

    obj->intersect = intersect_cylinder;
    obj->shape.cylinder.radius = inputdata->radius;
    obj->shape.cylinder.height = inputdata->height;
    obj->albedo[0] = inputdata->albedo[0];
    obj->albedo[1] = inputdata->albedo[1];
    obj->albedo[2] = inputdata->albedo[2];
}
