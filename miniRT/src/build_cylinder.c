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

	#define TMIN 1e-4
	#define DISC_EPS 1e-12
	#define CAP_EPS  1e-9

	/* ---- CYLINDER SIDE (fix: test BOTH roots + clamp near-zero negative disc) ---- */
	double A = vdotn(d, d, 2);        /* dx^2 + dy^2 */
	double B = 2.0 * vdotn(c, d, 2);  /* 2(ox*dx + oy*dy) */
	double C = vdotn(c, c, 2) - r*r;  /* ox^2 + oy^2 - r^2 */

	hit_side = 0;
	t_side = 1e30;

	if (fabs(A) > 1e-12)
	{
		double disc = B*B - 4.0*A*C;

		/* robustness: treat tiny negative as zero (tangent rays) */
		if (disc > -DISC_EPS)
		{
			if (disc < 0.0) disc = 0.0;

			double sqrtd = sqrt(disc);
			double t0 = (-B - sqrtd) / (2.0*A);
			double t1 = (-B + sqrtd) / (2.0*A);
			if (t0 > t1) { double tmp = t0; t0 = t1; t1 = tmp; }

			/* IMPORTANT FIX: test BOTH roots with height clip */
			if (t0 >= TMIN)
			{
				double p0[3];
				point(c, d, t0, p0);
				if (p0[2] >= -hh && p0[2] <= hh)
				{
					t_side = t0;
					hit_side = 1;
				}
			}
			if (!hit_side && t1 >= TMIN)
			{
				double p1[3];
				point(c, d, t1, p1);
				if (p1[2] >= -hh && p1[2] <= hh)
				{
					t_side = t1;
					hit_side = 1;
				}
			}
		}
	}

	/* ---- CAPS (fix: use same TMIN + allow tiny tolerance on rr<=r^2) ---- */
	hit_top = 0;
	hit_bot = 0;
	t_top = t_bot = 1e30;

	if (fabs(d[2]) > 1e-12)
	{
		double t = (hh - c[2]) / d[2]; /* top z=+hh */
		if (t >= TMIN)
		{
			double p_local[3];
			point(c, d, t, p_local);
			double rr = p_local[0]*p_local[0] + p_local[1]*p_local[1];
			if (rr <= r*r + CAP_EPS)
			{
				t_top = t;
				hit_top = 1;
			}
		}

		t = (-hh - c[2]) / d[2];       /* bottom z=-hh */
		if (t >= TMIN)
		{
			double p_local[3];
			point(c, d, t, p_local);
			double rr = p_local[0]*p_local[0] + p_local[1]*p_local[1];
			if (rr <= r*r + CAP_EPS)
			{
				t_bot = t;
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