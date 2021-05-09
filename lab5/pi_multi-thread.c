#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long inCircle = 0;
long pointsPerThread;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *runner()
{
    long inCircleThread = 0;

    unsigned int randState = rand();
    long i;
    for (i = 0; i < pointsPerThread; i++)
    {
        double x = rand_r(&randState) / ((double)RAND_MAX + 1) * 2.0 - 1.0;
        double y = rand_r(&randState) / ((double)RAND_MAX + 1) * 2.0 - 1.0;

        if (x * x + y * y < 1)
        {
            inCircleThread++;
        }
    }

    pthread_mutex_lock(&mutex);
    inCircle += inCircleThread;
    pthread_mutex_unlock(&mutex);
}

int main(int argc, const char *argv[])
{
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

    int i;
    for (i = 0; i < threadCount; i++)
    {
        pthread_create(&threads[i], &attr, runner, (void *)NULL);
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    free(threads);

    printf("Pi: %f\n", (4. * (double)inCircle) / totalPoints);
    return 0;
}
