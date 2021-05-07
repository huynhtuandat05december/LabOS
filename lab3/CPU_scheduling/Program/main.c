#include <stdio.h>
#include <stdlib.h>
#include "process.h"
#include "sort.h"
#include "schedulers.h"

int main(){
    int num_process = 0, i = 0;
    Quantum quantum;
    Process *p;

    // Load processes from file ---------------------------------------------
    FILE *fp = fopen("process.txt", "r");
    if (fp == NULL)
    {
        printf("Can not open the file!\n");
        return 0;
    }

    fscanf(fp, " %d", &num_process);
    p = (Process *)malloc(sizeof(Process) * num_process);

    for(int i=0; i < num_process; i++){
        fscanf(fp, "%s %d %d %d", p[i].id, &p[i].arrive_time, &p[i].burst, &p[i].priority);
    }
    fscanf(fp, " %d", &quantum);
    // ------------------------------------------------------------------------
   
    // Sort by arrive time
    init_process(p, num_process);
    sort(p, num_process);
        
    printf("\nFCFS:\n");
    FCFS(p, num_process);
    print(p, num_process);
    init_process(p, num_process);

    printf("\nSJF:\n");
    SJF(p, num_process);
    print(p, num_process);
    init_process(p, num_process);

    printf("\nPriority_Scheduling:\n");
    Priority_Scheduling(p, num_process);
    print(p, num_process);
    init_process(p, num_process);

    printf("\nRR:\n");
    RR(p, num_process, quantum);
    print(p, num_process);
    init_process(p, num_process);

    return 0;
}