#include <math.h>
#include <stddef.h>

double vdotn(const double v1[3], const double v2[3], size_t n)
{
    size_t  i;
    double  sum;

    i = 0;
    sum = 0.0;
    while (i < n)
    {
        sum += v1[i]*v2[i];
        i++;
    }
    return (sum);
}

double vnorm3(const double v[3])
{
    return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

void vnormalize3(const double v[3], double vnrm[3])
{
    double nrm;

    nrm = vnorm3(v);
    if (nrm == 0.0)
    {
        vnrm[0] = vnrm[1] = vnrm[2] = 0.0;
        return ;
    }
    vnrm[0] = v[0] / nrm;
    vnrm[1] = v[1] / nrm;
    vnrm[2] = v[2] / nrm; 
}

void cross3(const double a[3], const double b[3], double result[3])
{
    result[0] = a[1]*b[2] - a[2]*b[1];
    result[1] = a[2]*b[0] - a[0]*b[2];
    result[2] = a[0]*b[1] - a[1]*b[0];
}

// v' = R v, where rows of R are x, y, z (your basis vectors)
void rv(const double vin[3],
               const double x[3],
               const double y[3],
               const double z[3],
               double vout[3])
{
    vout[0] = vdotn(x, vin, 3); // projection on x'
    vout[1] = vdotn(y, vin, 3); // projection on y'
    vout[2] = vdotn(z, vin, 3); // projection on z'
}

// inverse: v = R^T v'  (local -> world)
void rv_inv(const double vin[3],   // local coords
                   const double x[3],
                   const double y[3],
                   const double z[3],
                   double vout[3])       // world coords
{
    vout[0] = vin[0]*x[0] + vin[1]*y[0] + vin[2]*z[0];
    vout[1] = vin[0]*x[1] + vin[1]*y[1] + vin[2]*z[1];
    vout[2] = vin[0]*x[2] + vin[1]*y[2] + vin[2]*z[2];
}

void rotate_x(double v[3], double theta)
{
    double c = cos(theta);
    double s = sin(theta);

    v[1] = v[1] * c - v[2] * s;
    v[2] = v[1] * s + v[2] * c;
}

void rotate_y(double v[3], double theta)
{
    double c = cos(theta);
    double s = sin(theta);

    v[0] = v[0] * c + v[2] * s;
    v[2] = -v[0] * s + v[2] * c;
}

void rotate_z(double v[3], double theta)
{
    double c = cos(theta);
    double s = sin(theta);

    v[0] = v[0] * c - v[1] * s;
    v[1] = v[0] * s + v[1] * c;
}