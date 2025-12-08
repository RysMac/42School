#include "framebuffer.h"
#include <stdlib.h>

int fb_init(t_framebuffer *fb, size_t w, size_t h)
{
    fb->data = malloc(w * h * 3 * sizeof(uint8_t));
    if (!fb->data)
        return (1);
    fb->w = w;
    fb->h = h;
    
    return (0);
}

void fb_free(t_framebuffer *fb)
{
    free(fb->data);
    fb->data = NULL;
}