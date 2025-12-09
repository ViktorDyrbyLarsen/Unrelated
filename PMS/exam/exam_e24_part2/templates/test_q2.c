#include <stdlib.h>
#include <stdio.h>

double chebseries(double x, const double *c, int n);

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Should only input x (double)");
        return 1;
    }
    double x = atof(argv[1]);
    int n = 5; // We get n + 1 coefficients
    const double c[] = {-1,4,2,0.001, 1};

    printf("%.3f \n", chebseries(x,c,n));

    return 0;
}
