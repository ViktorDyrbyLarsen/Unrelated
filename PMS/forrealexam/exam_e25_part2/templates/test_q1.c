#include <stdlib.h>
#include <stdio.h>

double log1mexp(double x);

int main(int argc, char *argv[])
{

    double x = atof(argv[1]);
    printf("x is: %f \n", x);
    printf("%.3f \n", log1mexp(x));
    return 0;
}