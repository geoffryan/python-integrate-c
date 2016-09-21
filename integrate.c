#include "integrate.h"

double riemann(double *f, double a, double b, int N)
{
    double h = (b-a)/N;
    int i;
    double I = 0;
    for(i=0; i<N; i++)
        I += f[i];
    return h*I;
}

double trapezoid(double *f, double a, double b, int N)
{
    double h = (b-a)/N;
    int i;
    double I = 0.5*f[0];
    for(i=1; i<N; i++)
        I += f[i];
    I += 0.5*f[N];

    return h*I;
}
