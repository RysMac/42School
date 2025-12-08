#include "../include/framebuffer.h"

// n, x, y are local plane basis needed for transformation matrix R
// check if n is normalized
void    cylinder_basis(const double n[3], double x[3], double y[3])
{
    double u[3];

    if (fabs(n[1]) < 0.9)
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

static int intersect_cylinder(const t_obj *obj, const t_ray *ray, t_hit *hit)
{
    double x[3], y[3];
    double o[3];      // world, relative to center
    double c[3];      // local origin
    double d[3];      // local dir
    double r = obj->shape.cylinder.radius;
    double hh = obj->shape.cylinder.height * 0.5;
    double t_side = 1e30;
    double t_top  = 1e30;
    double t_bot  = 1e30;
    int    hit_side = 0, hit_top = 0, hit_bot = 0;

    // build basis
    cylinder_basis(obj->pos.dir, x, y);

    // shift ray origin to cylinder center
    o[0] = ray->o[0] - obj->pos.pos[0];
    o[1] = ray->o[1] - obj->pos.pos[1];
    o[2] = ray->o[2] - obj->pos.pos[2];

    // world -> local
    rv(o,      x, y, obj->pos.dir, c);
    rv(ray->d, x, y, obj->pos.dir, d);

    /* ---- SIDE (infinite, then height clip) ---- */
    double A = vdotn(d, d, 2);        // dx^2 + dy^2
    double B = 2.0 * vdotn(c, d, 2);  // 2(ox*dx + oy*dy)
    double C = vdotn(c, c, 2) - r*r;  // ox^2 + oy^2 - r^2

    if (fabs(A) > 1e-12)
    {
        double disc = B*B - 4.0*A*C;
        if (disc >= 0.0)
        {
            double sqrtd = sqrt(disc);
            double t0 = (-B - sqrtd) / (2.0*A);
            double t1 = (-B + sqrtd) / (2.0*A);
            swap2(&t0, &t1);

            double t_candidate = (t0 >= 1e-6) ? t0 : ((t1 >= 1e-6) ? t1 : 1e30);
            if (t_candidate < 1e30)
            {
                double p_side[3];
                point(c, d, t_candidate, p_side); // local hit
                if (p_side[2] >= -hh && p_side[2] <= hh)
                {
                    t_side = t_candidate;
                    hit_side = 1;
                }
            }
        }
    }
    // else: parallel to axis, no side hit

    /* ---- TOP cap ---- */
    if (fabs(d[2]) > 1e-12)
    {
        double t = (hh - c[2]) / d[2]; // z' = +hh
        if (t >= 1e-4)
        {
            double p_local[3];
            point(c, d, t, p_local); // local
            double rr = p_local[0]*p_local[0] + p_local[1]*p_local[1];
            if (rr <= r*r)
            {
                t_top  = t;
                hit_top = 1;
            }
        }

        /* ---- BOTTOM cap ---- */
        t = (-hh - c[2]) / d[2]; // z' = -hh
        if (t >= 1e-4)
        {
            double p_local[3];
            point(c, d, t, p_local); // local
            double rr = p_local[0]*p_local[0] + p_local[1]*p_local[1];
            if (rr <= r*r)
            {
                t_bot  = t;
                hit_bot = 1;
            }
        }
    }

    /* ---- choose nearest ---- */
    double t_best = 1e30;
    int    hit_type = 0; // 1=side, 2=top, 3=bottom

    if (hit_side && t_side < t_best) { t_best = t_side; hit_type = 1; }
    if (hit_top  && t_top  < t_best) { t_best = t_top;  hit_type = 2; }
    if (hit_bot  && t_bot  < t_best) { t_best = t_bot;  hit_type = 3; }

    if (hit_type == 0)
        return 0; // no valid intersection

    /* ---- compute final local hit + local normal ---- */
    double p_local[3];
    double n_local[3];

    point(c, d, t_best, p_local);

    if (hit_type == 1) // side
    {
        // radial normal in x,y
        double nx = p_local[0];
        double ny = p_local[1];
        double len = sqrt(nx*nx + ny*ny);
        if (len > 0.0)
        {
            nx /= len;
            ny /= len;
        }
        n_local[0] = nx;
        n_local[1] = ny;
        n_local[2] = 0.0;
    }
    else if (hit_type == 2) // top
    {
        n_local[0] = 0.0;
        n_local[1] = 0.0;
        n_local[2] = 1.0;
    }
    else // bottom
    {
        n_local[0] = 0.0;
        n_local[1] = 0.0;
        n_local[2] = -1.0;
    }

    /* ---- transform back to world ---- */
    double p_world[3], n_world[3];
    rv_inv(p_local, x, y, obj->pos.dir, p_world);
    rv_inv(n_local, x, y, obj->pos.dir, n_world);
    vnormalize3(n_world, n_world);

    p_world[0] += obj->pos.pos[0];
    p_world[1] += obj->pos.pos[1];
    p_world[2] += obj->pos.pos[2];

    hit->obj = obj;
    hit->t    = t_best;
    hit->p[0] = p_world[0];
    hit->p[1] = p_world[1];
    hit->p[2] = p_world[2];
    hit->n[0] = n_world[0];
    hit->n[1] = n_world[1];
    hit->n[2] = n_world[2];
    vnormalize3(hit->n, hit->n);
    double d_dot_n = vdotn(ray->d, hit->n, 3);
    if (d_dot_n > 0.0)
    {
        hit->n[0] = -hit->n[0];
        hit->n[1] = -hit->n[1];
        hit->n[2] = -hit->n[2];
    }
    return 1;
}

// static int intersect_cylinder(const t_obj *obj, const t_ray *ray, t_hit *hit)
// {
//     double o[3];
//     double c[3];
//     double x[3];
//     double y[3];
//     double d[3];
//     double t_hit;
//     double t0;
//     double t1;
//     double t_top;
//     double t_bot;
//     double p[3];

//     cylinder_basis(obj->pos.dir, x, y);
//     // ray->o is origin of camera; obj->pos.pos is a point of the origin of cylinder
//     o[0] = ray->o[0] - obj->pos.pos[0];
//     o[1] = ray->o[1] - obj->pos.pos[1];
//     o[2] = ray->o[2] - obj->pos.pos[2];

//     rv(o, x, y, obj->pos.dir, c);
//     rv(ray->d, x, y, obj->pos.dir, d);

//     double r = obj->shape.cylinder.radius;
//     double a0 = vdotn(d, d, 2);
//     double b0 = 2 * vdotn(c, d, 2);
//     double c0 = vdotn(c, c, 2) - r * r;
//     if (fabs(a0) < 1e-12)
//         return 0; // ray parallel to axis -> no side hit

//     double d0 = b0 * b0 - 4 * a0 * c0;
//     if (d0 < 0) // no hit
//         return (0); 
//     double dsqrt = sqrt(d0);
//     t0 = (- b0 + dsqrt) / (2 * a0);
//     t1 = (- b0 - dsqrt) / (2 * a0);
//     swap2(&t0, &t1);
//     if (t0 >= 1e-6)
//         t_hit = t0;
//     else if (t1 >= 1e-6)
//         t_hit = t1;
//     else
//         return 0; // both behind camera/near plane
//     // hit point in plane/local coords
//     point(c, d, t_hit, hit->p);
//     // check height
//     // if (hit->p[2] > obj->shape.cylinder.height / 2) // t_top
//     // {
//     //     t_top = (obj->shape.cylinder.height / 2 - c[2]) / d[2]; 
//     //     point(c, d, t_top, p);
//     //     if (p[0] * p[0] + p[1] * p[1] <= r * r)
//     //     {
//     //         t_hit = t_top;
//     //         point(c, d, t_hit, hit->p);
//     //     }
//     // }
//     // if (hit->p[2] < - obj->shape.cylinder.height / 2) // t_top
//     // {
//     //     t_bot = (-obj->shape.cylinder.height / 2 - c[2]) / d[2]; 
//     //     point(c, d, t_bot, p);
//     //     if (p[0] * p[0] + p[1] * p[1] <= r * r)
//     //     {
//     //         t_hit = t_bot;
//     //         point(c, d, t_hit, hit->p);
//     //     }
//     // }
//     double n_radial[3];
//     double hit_p[3] = {hit->p[0], hit->p[1], 0.};
//     vnormalize3(hit_p, n_radial);
//     // go back to world frame
//     rv_inv(hit->p, x, y, obj->pos.dir, hit->p);
//     rv_inv(n_radial, x, y, obj->pos.dir, n_radial);
//     // vnormalize3(n_radial, n_radial);
//     // add translation
//     hit->p[0] = obj->pos.pos[0] + hit->p[0];
//     hit->p[1] = obj->pos.pos[1] + hit->p[1];
//     hit->p[2] = obj->pos.pos[2] + hit->p[2];
//     hit->t = t_hit;
//     hit->n[0] = n_radial[0];
//     hit->n[1] = n_radial[1];
//     hit->n[2] = n_radial[2];
    
//     return (1);
// }

void    obj_cylinder(t_obj *obj, t_inputdata *inputdata)
{
    double tmp[3];

    obj->type = OBJ_CYLINDER;
    // center point position in global frame
    obj->pos.pos[0] = inputdata->pos[0];
    obj->pos.pos[1] = inputdata->pos[1];
    obj->pos.pos[2] = inputdata->pos[2];
    // normal direction (needed only for plane)
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