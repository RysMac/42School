#include "framebuffer.h"
#include <stdlib.h>

int fb_init(t_framebuffer *fb, size_t w, size_t h)
{
    fb->w = w;
    fb->h = h;
    fb->data = NULL;  
    return (0);
}

void fb_free(t_framebuffer *fb)
{
    fb->data = NULL;           // nie free, bo to bufor MLX
}
