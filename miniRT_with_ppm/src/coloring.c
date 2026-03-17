#include "../include/miniRT.h"

// void coloring_object(t_framebuffer *fb, const t_camera *camera, t_scene *scene)
// {
// 	size_t w = fb->w;
// 	size_t h = fb->h;
// 	const t_obj *object;
// 	t_ray r;
// 	t_hit hit;
// 	t_hit hit_tmp;
// 	int hit_any;
// 	double t_closest;
// 	double R, G, B;

// 	r.o[0] = (camera->c)[0];
// 	r.o[1] = (camera->c)[1];
// 	r.o[2] = (camera->c)[2];

// 	for (size_t y = 0; y < h; ++y)
// 	{
// 		for (size_t x = 0; x < w; ++x)
// 		{
// 			double dij[3];
// 			d_ij(camera, x, y, dij);
// 			r.d[0] = dij[0];
// 			r.d[1] = dij[1];
// 			r.d[2] = dij[2];

// 			t_closest = 100000;
// 			hit_any = 0;
// 			for (int i = 0; i < scene->count; i++)
// 			{
// 				object = &scene->objects[i];
// 				if (object->intersect(object, &r, &hit_tmp))
// 				{
// 					if (hit_tmp.t < t_closest)
// 					{
// 						t_closest = hit_tmp.t;
// 						hit = hit_tmp;
// 						hit_any = 1;
// 					}
// 				}
// 			}
// 			if (hit_any == 1) // && hit.t > 1e-4 ??
// 			{
// 				// reverse n if needed
// 				// put here a function which returns RGB
// 				// printf("hit \n");
// 				double color[3];
// 				shade(scene, &hit, color);
// 				R = color[0]; // map [-1,1] -> [0,1]
// 				G = color[1];
// 				B = color[2];
// 			}
// 			else
// 			{
// 				R = 0.0;
// 				G = 0.0;
// 				B = 0.0;
// 			}
// 			// clamp to [0,1] just in case of numerical noise
// 			R = fmin(1.0, fmax(0.0, R));
// 			G = fmin(1.0, fmax(0.0, G));
// 			B = fmin(1.0, fmax(0.0, B));

// 			size_t idx = (y * w + x) * 3;
// 			fb->data[idx + 0] = (uint8_t)lrint(255.0 * R);
// 			fb->data[idx + 1] = (uint8_t)lrint(255.0 * G);
// 			fb->data[idx + 2] = (uint8_t)lrint(255.0 * B);
// 		}
// 	}
// }

static void	dir_dij(const t_camera *camera, t_ray *ray, int x, int y)
{
	double	dij[3];

	d_ij(camera, x, y, dij);
	ray->d[0] = dij[0];
	ray->d[1] = dij[1];
	ray->d[2] = dij[2];
	vnormalize3(ray->d, ray->d);
}

static int	find_hit(t_scene *scene, t_ray *ray, t_hit *hit)
{
	double		t_closest;
	int			hit_any;
	const t_obj	*object;
	t_hit		tmp;
	size_t		i;

	t_closest = 1e30;
	hit_any = 0;
	i = 0;
	while (i < (size_t)scene->count)
	{
		object = &scene->objects[i];
		if (object->intersect(object, ray, &tmp))
		{
			if (tmp.t > 0.001 && tmp.t < t_closest)
			{
				t_closest = tmp.t;
				*hit = tmp;
				hit_any = 1;
			}
		}
		++i;
	}
	return (hit_any);
}

static void	set_rgb(t_data *data, t_hit *hit, int hit_any, size_t idx)
{
	double	rgb[3];

	if (hit_any)
		shade(&data->scene, hit, rgb);
	else
	{
		rgb[0] = 0.0;
		rgb[1] = 0.0;
		rgb[2] = 0.0;
	}
	rgb[0] = fmin(1.0, fmax(0.0, rgb[0]));
	rgb[1] = fmin(1.0, fmax(0.0, rgb[1]));
	rgb[2] = fmin(1.0, fmax(0.0, rgb[2]));
	data->fb_ppm.data[idx + 0] = (uint8_t)(rgb[0] * 255.0 + 0.5);
	data->fb_ppm.data[idx + 1] = (uint8_t)(rgb[1] * 255.0 + 0.5);
	data->fb_ppm.data[idx + 2] = (uint8_t)(rgb[2] * 255.0 + 0.5);

	// size_t idx = (y * w + x) * 3;
	// fb->data[idx + 0] = (uint8_t)lrint(255.0 * R);
	// fb->data[idx + 1] = (uint8_t)lrint(255.0 * G);
	// fb->data[idx + 2] = (uint8_t)lrint(255.0 * B);
}

static void	set_color(t_data *data, t_ray *ray, size_t x, size_t y)
{
	t_hit	hit;
	int		hit_any;
	size_t	idx;

	dir_dij(&(data->scene.camera), ray, (int)x, (int)y);
	hit_any = find_hit(&(data->scene), ray, &hit);
	idx = (y * data->fb.w + x) * 3;
	idx = y * data->line_len + x * (size_t)(data->bpp / 8);
	set_rgb(data, &hit, hit_any, idx);
}

void	coloring_object(t_data *data)
{
	t_ray	r;
	size_t	x;
	size_t	y;

	r.o[0] = data->scene.camera.c[0];
	r.o[1] = data->scene.camera.c[1];
	r.o[2] = data->scene.camera.c[2];
	y = 0;
	while (y < data->fb.h)
	{
		x = 0;
		while (x < data->fb.w)
		{
			set_color(data, &r, x, y);
			++x;
		}
		++y;
	}
}