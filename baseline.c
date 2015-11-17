#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <stdint.h>
double compute_pi(size_t dt){
    double pi = 0.0;
    double delta = 1.0 / dt;
    for (size_t i = 0; i < dt; i++) {
        double x = (double) i / dt;
        pi += delta / (1.0 + x * x);
    }
    return pi * 4.0;
}
static double diff_in_second(struct timespec t1, struct timespec t2)
{
    struct timespec diff;
    if (t2.tv_nsec-t1.tv_nsec < 0) {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec - 1;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec + 1000000000;
    } else {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec;
    }
    return (diff.tv_sec + diff.tv_nsec / 1000000000.0);
}

int main(int argc, char *argv[])
{
    struct timespec start, end;
    double cpu_time;
    
    double pi;
	
    assert(compute_pi(128*1024*1024) &&"Did you implement compute_pi()");
    
    clock_gettime(CLOCK_REALTIME, &start);
    pi=compute_pi((size_t)128*1024*1024);
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time = diff_in_second(start, end);
    printf("pi: %lf\n",pi);
    printf("execution time of compute_pi() : %lf sec\n", cpu_time);

    return 0;
}
