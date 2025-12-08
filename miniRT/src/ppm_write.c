#include <stdio.h>    // fopen, fprintf, fwrite, fclose
#include <stdint.h>   // uint8_t
#include "framebuffer.h"

int ppm_write(const char *path, const t_framebuffer *fb)
{
    if (!path || !fb || !fb->data || fb->w == 0 || fb->h == 0) return 1;

    FILE *f = fopen(path, "wb");          // binary mode
    if (!f) return 1;

    // Header: P6 + width height + maxval 255 + newline after 255
    if (fprintf(f, "P6\n%zu %zu\n255\n", fb->w, fb->h) < 0) {
        fclose(f); return 1;
    }

    size_t total = fb->w * fb->h * 3;     // RGB bytes
    size_t n = fwrite(fb->data, 1, total, f);
    if (n != total) { fclose(f); return 1; }

    if (fclose(f) != 0) return 1;
    return 0;
}