#include <stdio.h>
#include <stdlib.h>
#include "process.h"

int compare(const void* elem1, const void* elem2) {
    Process* x = (Process* ) elem1;
    Process* y = (Process* ) elem2;
    return x->arrive_time - y->arrive_time;
}

void sort(Process* x, int len){
    qsort(x, len, sizeof(*x), compare);
}