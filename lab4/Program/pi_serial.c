#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long inCircle = 0;

int main(int argc, const char *argv[])
{

    // clock_t start, end;
    // double time_use;
    // start = clock();
    if (argc != 2)
    {
        fprintf(stderr, "usage: ./pi <total points>\n");
        return -1;
    }

    long totalPoints = atol(argv[1]);
    int i;
    for (i = 0; i < totalPoints; i++)
    {
        unsigned int randState = rand();

        double x = rand_r(&randState) / ((double)RAND_MAX + 1) * 2.0 - 1.0;
        double y = rand_r(&randState) / ((double)RAND_MAX + 1) * 2.0 - 1.0;

        if (x * x + y * y < 1)
        {
            inCircle++;
        }
    }
    // end = clock();
    // time_use = (double)(end - start) / CLOCKS_PER_SEC;

    printf("%f\n", (4. * (double)inCircle) / totalPoints);
    // printf("%f seconds", time_use);
    return 0;
}
