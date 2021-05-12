#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long inCircle = 0;
long pointsPerThread;

void *runner()
{
    long int *inCircleThread = (long int *)malloc(sizeof(long int));
    *inCircleThread = 0;

    unsigned int randState = rand();
    long i;
    for (i = 0; i < pointsPerThread; i++)
    {
        double x = rand_r(&randState) / ((double)RAND_MAX + 1) * 2.0 - 1.0;
        double y = rand_r(&randState) / ((double)RAND_MAX + 1) * 2.0 - 1.0;

        if (x * x + y * y < 1)
        {
            (*inCircleThread)++;
        }
    }
    pthread_exit((void *)inCircleThread);
}

int main(int argc, const char *argv[])
{
    // clock_t start, end;
    // double time_use;
    pthread_t tid;
    pthread_attr_t attr;
    if (argc != 2)
    {
        fprintf(stderr, "usage: ./pi <total points>\n");
        return -1;
    }

    pthread_attr_init(&attr);

    long totalPoints = atol(argv[1]);
    int threadCount;
    if (totalPoints >= 1000)
        threadCount = 1000;
    else if (totalPoints >= 100)
        threadCount = 100;
    else
        threadCount = 1;
    pointsPerThread = totalPoints / threadCount;

    srand((unsigned)time(NULL));

    pthread_t *threads = malloc(threadCount * sizeof(pthread_t));
    // start = clock();
    void *status;
    int i;
    for (i = 0; i < threadCount; i++)
    {
        pthread_create(&threads[i], &attr, runner, (void *)NULL);
        pthread_join(threads[i], &status);
        inCircle += *(long int *)status;
    }
    // end = clock();
    // time_use = (double)(end - start) / CLOCKS_PER_SEC;
    free(threads);

    printf("%f\n", (4. * (double)inCircle) / totalPoints);
    // printf("%f seconds", time_use);

    return 0;
}