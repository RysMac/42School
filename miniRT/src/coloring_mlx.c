#include "../include/framebuffer.h"

static inline uint8_t to_u8(double v)
{
    if (v < 0.0) v = 0.0;
    if (v > 1.0) v = 1.0;
    return (uint8_t)(v * 255.0 + 0.5);
}

void coloring_object_mlx(t_framebuffer *fb,
                     const t_camera *camera,
                     t_scene *scene,
                     int bpp,
                     size_t line_len,
                     int endian)
{
    size_t w = fb->w;
    size_t h = fb->h;

    int bytespp = bpp / 8;
    if (bytespp != 4)
	{
		printf("your code is written for 32bpp only");
		return; 
	}
    t_ray r;
    t_hit hit;

    r.o[0] = camera->c[0];
    r.o[1] = camera->c[1];
    r.o[2] = camera->c[2];

    for (size_t y = 0; y < h; ++y)
    {
        for (size_t x = 0; x < w; ++x)
        {
            double dij[3];
            d_ij(camera, (int)x, (int)y, dij);

            r.d[0] = dij[0];
            r.d[1] = dij[1];
            r.d[2] = dij[2];
            vnormalize3(r.d, r.d);

            double t_closest = 1e30;
            int hit_any = 0;

            for (size_t i = 0; i < (size_t)scene->count; ++i)
            {
                const t_obj *object = &scene->objects[i];
                t_hit tmp;

                if (object->intersect(object, &r, &tmp))
                {
                    if (tmp.t > 0.001 && tmp.t < t_closest)
                    {
                        t_closest = tmp.t;
                        hit = tmp;
                        hit_any = 1;
                    }
                }
            }

            double R = 0.0, G = 0.0, B = 0.0;
            if (hit_any)
            {
                double color[3];
                shade(scene, &hit, color);
                R = color[0]; G = color[1]; B = color[2];
            }
			R = fmax(0.0, fmin(1.0, R));
            G = fmax(0.0, fmin(1.0, G));
            B = fmax(0.0, fmin(1.0, B));

            uint8_t r8 = to_u8(R);
            uint8_t g8 = to_u8(G);
            uint8_t b8 = to_u8(B);
            uint8_t a8 = 255;

            size_t idx = y * line_len + x * (size_t)bytespp;

            // Common MLX convention:
            // endian == 0: write as BGRA in memory (least significant byte first)
            // endian == 1: write as ARGB in memory
            // if (endian == 0) {
                fb->data[idx + 0] = b8;
                fb->data[idx + 1] = g8;
                fb->data[idx + 2] = r8;
                fb->data[idx + 3] = a8;
            // } else {
            //     fb->data[idx + 0] = a8;
            //     fb->data[idx + 1] = r8;
            //     fb->data[idx + 2] = g8;
            //     fb->data[idx + 3] = b8;
            // }
        }
    }
}