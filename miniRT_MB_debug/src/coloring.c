/* #include "../include/framebuffer.h"
#include <math.h>

void coloring_object(t_framebuffer *fb, const t_camera *camera, t_scene *scene)
{
    size_t w = fb->w;
    size_t h = fb->h;

    // TEST CZERWONY – zostaw na razie, potem usuń
    size_t idx = 0;
    while (idx < w * h * 4)
    {
        fb->data[idx++] = 255;   // R
        fb->data[idx++] = 0;     // G
        fb->data[idx++] = 0;     // B
        fb->data[idx++] = 255;   // A (alpha – wymagane na macOS)
    }
    //return;  // ← usuń tę linię, gdy chcesz zobaczyć raytracing

    // ────────────────────────────────────────────────
    // Poniżej normalny raytracer – po usunięciu return↑

    t_ray   r;
    t_hit   hit;
    double  t_closest;
    int     hit_any;

    r.o[0] = camera->c[0];
    r.o[1] = camera->c[1];
    r.o[2] = camera->c[2];

    size_t y = 0;
    while (y < h)
    {
        size_t x = 0;
        while (x < w)
        {
            double dij[3];
            d_ij(camera, (int)x, (int)y, dij);

            r.d[0] = dij[0];
            r.d[1] = dij[1];
            r.d[2] = dij[2];
            vnormalize3(r.d, r.d);

            t_closest = 1e30;
            hit_any = 0;

            size_t i = 0;
            while (i < scene->count)
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
                i++;
            }

            double R = 0.0, G = 0.0, B = 0.0;

            if (hit_any)
            {
                double color[3];
                shade(scene, &hit, color);
                R = color[0];
                G = color[1];
                B = color[2];
            }

            R = fmax(0.0, fmin(1.0, R));
            G = fmax(0.0, fmin(1.0, G));
            B = fmax(0.0, fmin(1.0, B));

            size_t idx = (y * w + x) * 4;   // ← 4 bajty na macOS
            fb->data[idx + 0] = (uint8_t)(R * 255.0 + 0.5);
            fb->data[idx + 1] = (uint8_t)(G * 255.0 + 0.5);
            fb->data[idx + 2] = (uint8_t)(B * 255.0 + 0.5);
            fb->data[idx + 3] = 255;   // alpha zawsze 255

            x++;
        }
        y++;
    }
}

*/

#include "../include/framebuffer.h"
#include <math.h>

void coloring_object(t_framebuffer *fb, const t_camera *camera, t_scene *scene, int endian, size_t line_len)
{
    size_t w = fb->w;
    size_t h = fb->h;

    t_ray   r;
    t_hit   hit;
    double  t_closest;
    int     hit_any;

    r.o[0] = camera->c[0];
    r.o[1] = camera->c[1];
    r.o[2] = camera->c[2];

    size_t y = 0;
    while (y < h)
    {
        size_t x = 0;
        while (x < w)
        {
            double dij[3];
            d_ij(camera, (int)x, (int)y, dij);

            r.d[0] = dij[0];
            r.d[1] = dij[1];
            r.d[2] = dij[2];
            vnormalize3(r.d, r.d);

            t_closest = 1e30;
            hit_any = 0;

            size_t i = 0;
            while (i < scene->count)
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
                i++;
            }

            double R = 0.0, G = 0.0, B = 0.0;

            if (hit_any)
            {
                double color[3];
                shade(scene, &hit, color);
                R = color[0];
                G = color[1];
                B = color[2];
            }

            R = fmax(0.0, fmin(1.0, R));
            G = fmax(0.0, fmin(1.0, G));
            B = fmax(0.0, fmin(1.0, B));

            size_t idx = y * line_len + x * 4;

            uint8_t r_byte = (uint8_t)(R * 255.0 + 0.5);
            uint8_t g_byte = (uint8_t)(G * 255.0 + 0.5);
            uint8_t b_byte = (uint8_t)(B * 255.0 + 0.5);

            if (endian == 0) {  // Little-endian (BGRA na macOS/Linux)
                fb->data[idx + 0] = b_byte;  // Blue
                fb->data[idx + 1] = g_byte;  // Green
                fb->data[idx + 2] = r_byte;  // Red
                fb->data[idx + 3] = 255;     // Alpha
            } else {  // Big-endian (ARGB - rzadkie)
                fb->data[idx + 0] = 255;     // Alpha
                fb->data[idx + 1] = r_byte;  // Red
                fb->data[idx + 2] = g_byte;  // Green
                fb->data[idx + 3] = b_byte;  // Blue
            }

            x++;
        }
        y++;
    }
}
