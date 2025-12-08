#include "../include/framebuffer.h"

// gives a point based on direction and translation and param t
void point(const double o[3], const double d[3], const double t, double p[3])
{
    p[0] = o[0] + t * d[0];
    p[1] = o[1] + t * d[1];
    p[2] = o[2] + t * d[2];
}

// sort two numbers
void swap2(double *t0, double *t1)
{
    double tmp;

    if (*t0 > *t1)
    {
        tmp = *t0;
        *t0 = *t1;
        *t1 = tmp;
    }
}