#include "../include/framebuffer.h"

void coloring_object(t_framebuffer *fb, const t_obj *obj, const t_camera *camera, t_scene *scene)
{
    size_t  w = fb->w;
    size_t  h = fb->h;
    const t_obj   *object;
    t_ray   r;
    t_hit   hit;
    t_hit   hit_tmp;
    int     hit_any;
    double  t_closest;
    double  R, G, B;

    
    r.o[0] = (camera->c)[0];
    r.o[1] = (camera->c)[1];
    r.o[2] = (camera->c)[2];

    for (size_t y = 0; y < h; ++y) {
        for (size_t x = 0; x < w; ++x) {
            double dij[3]; // a direction
            d_ij(camera, x, y, dij);
            r.d[0] = dij[0];
            r.d[1] = dij[1];
            r.d[2] = dij[2];

            t_closest = 100000;
            hit_any = 0;
            for (int i = 0; i < scene->count ; i++)
            {
                object = &obj[i];
                if (object->intersect(object, &r, &hit_tmp))
                {
                    if (hit_tmp.t < t_closest)
                    {
                        t_closest = hit_tmp.t;
                        hit = hit_tmp;
                        hit_any = 1;
                    }
                }
            }
            if (hit_any == 1) // && hit.t > 1e-4 ??
            {
                // reverse n if needed
                // put here a function which returns RGB
                // printf("hit \n");
                double color[3];
                shade(scene, &hit, color);
                R = color[0];  // map [-1,1] -> [0,1]
                G = color[1];
                B = color[2];
            }
            else
            {
                R = 0.0;
                G = 0.0;
                B = 0.0;
            }
            // clamp to [0,1] just in case of numerical noise
            if (R < 0.0) R = 0.0; if (R > 1.0) R = 1.0;
            if (G < 0.0) G = 0.0; if (G > 1.0) G = 1.0;
            if (B < 0.0) B = 0.0; if (B > 1.0) B = 1.0;

            size_t idx = (y * w + x) * 3;
            fb->data[idx+0] = (uint8_t)lrint(255.0 * R);
            fb->data[idx+1] = (uint8_t)lrint(255.0 * G);
            fb->data[idx+2] = (uint8_t)lrint(255.0 * B);
        }
    }
}