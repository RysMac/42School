/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coloring_mlx.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrys <mrys@student.42warsaw.pl>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 11:13:19 by mrys              #+#    #+#             */
/*   Updated: 2026/02/26 11:13:19 by mrys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/framebuffer.h"
#include "../include/miniRT.h"

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
	data->fb.data[idx + 0] = (uint8_t)(rgb[2] * 255.0 + 0.5);
	data->fb.data[idx + 1] = (uint8_t)(rgb[1] * 255.0 + 0.5);
	data->fb.data[idx + 2] = (uint8_t)(rgb[0] * 255.0 + 0.5);
	data->fb.data[idx + 3] = (uint8_t)255;
}

static void	set_color(t_data *data, t_ray *ray, size_t x, size_t y)
{
	t_hit	hit;
	int		hit_any;
	size_t	idx;

	dir_dij(&(data->scene.camera), ray, (int)x, (int)y);
	hit_any = find_hit(&(data->scene), ray, &hit);
	idx = y * data->line_len + x * (size_t)(data->bpp / 8);
	set_rgb(data, &hit, hit_any, idx);
}

// as input only t_data*
void	coloring_object_mlx(t_data *data)
{
	t_ray	r;
	size_t	x;
	size_t	y;

	if (data->bpp / 8 != 4)
		return ((void)printf("your code is written for 32bpp only"));
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
