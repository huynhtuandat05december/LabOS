#ifndef __PROC__
#define __PROC__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _process_{
    char id[256];
    int arrive_time;
    int burst;
    int tmp_burst_;
    int priority;
    int return_time;
    int waiting_time;
    int turnaround_time;
    int response_time;
    bool completed;
    bool executing;
}Process;

void init_process(Process p[], int len)
{
    int i;

    for (i = 0; i < len; i++)
    {
        p[i].return_time = 0;
        p[i].waiting_time = 0;
        p[i].turnaround_time = 0;        
        p[i].response_time = 0;
        p[i].completed = false;
        p[i].executing = false;
        p[i].tmp_burst_ = p[i].burst;
    }
}

typedef int Quantum;

#endif
