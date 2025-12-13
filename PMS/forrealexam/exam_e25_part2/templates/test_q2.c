#include <stdlib.h>
#include <stdio.h>

double legendreseries(double x, const double *c, int n);

int main(int argc, char *argv[])
{
    int n = 4;
    const double constants[] = {1,1,1,1};
    double x = atof(argv[1]);
    double result = legendreseries(x,constants,n);

    printf("%f \n", result);

    return 0;
}
