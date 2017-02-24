/*
 * AXPY  Y[N] = Y[N] + a*X[N]
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sys/timeb.h>

/* read timer in second */
double read_timer() {
    struct timeb tm;
    ftime(&tm);
    return (double) tm.time + (double) tm.millitm / 1000.0;
}

/* read timer in ms */
double read_timer_ms() {
    struct timeb tm;
    ftime(&tm);
    return (double) tm.time * 1000.0 + (double) tm.millitm;
}

#define REAL float

/* initialize a vector with random floating point numbers */
void init(REAL A[], int N) {
    int i;
    for (i = 0; i < N; i++) {
        A[i] = (double) drand48();
    }
}

double check(REAL A[], REAL B[], int N) {
    int i;
    double sum = 0.0;
    for (i = 0; i < N; i++) {
        sum += A[i] - B[i];
    }
    return sum;
}

void axpy_base(int N, REAL Y[], REAL X[], REAL a);

void axpy_base_sub(int i_start, int Nt, int N, REAL Y[], REAL X[], REAL a);

void axpy_dist(int N, REAL Y[], REAL X[], REAL a, int num_tasks);
void axpy_dist_pthread(int N, REAL Y[], REAL X[], REAL a, int num_tasks);

int main(int argc, char *argv[]) {
    int N = 1024*4;
    int num_tasks = 5; /* 5 is default number of tasks */
    double elapsed; /* for timing */
    double elapsed_dist; /* for timing */
    if (argc < 2) {
        fprintf(stderr, "Usage: axpy <n(%d)> [<#tasks(%d)>]\n", N, num_tasks);
    } else N = atoi(argv[1]);
    if (argc > 2) num_tasks = atoi(argv[2]);
    REAL a = 123.456;
    REAL Y_base[N];
    REAL Y_dist[N];
    REAL X[N];

    srand48((1 << 12));
    init(X, N);
    init(Y_base, N);
    memcpy(Y_dist, Y_base, N * sizeof(REAL));

    /* example run */
    elapsed = read_timer();
    axpy_base(N, Y_base, X, a);
    elapsed = (read_timer() - elapsed);

    elapsed_dist = read_timer();
    axpy_dist(N, Y_dist, X, a, num_tasks);
    elapsed_dist = (read_timer() - elapsed_dist);

    /* you should add the call to each function and time the execution */
    printf("======================================================================================================\n");
    printf("\tAXPY: Y[N] = Y[N] + a*X[N], N=%d, %d tasks for dist\n", N, num_tasks);
    printf("------------------------------------------------------------------------------------------------------\n");
    printf("Performance:\t\tRuntime (ms)\t MFLOPS \t\tError (compared to base)\n");
    printf("------------------------------------------------------------------------------------------------------\n");
    printf("axpy_base:\t\t%4f\t%4f \t\t%g\n", elapsed * 1.0e3, (2.0 * N) / (1.0e6 * elapsed), check(Y_base, Y_base, N));
    printf("axpy_dist:\t\t%4f\t%4f \t\t%g\n", elapsed_dist * 1.0e3, (2.0 * N) / (1.0e6 * elapsed_dist), check(Y_base, Y_dist, N));
    return 0;
}

void axpy_base(int N, REAL Y[], REAL X[], REAL a) {
    int i;
    for (i = 0; i < N; ++i)
        Y[i] += a * X[i];
}

void axpy_base_sub(int i_start, int Nt, int N, REAL Y[], REAL X[], REAL a) {
    int i;
    for (i = i_start; i < i_start + Nt; ++i)
        Y[i] += a * X[i];
}

void dist(int tid, int N, int num_tasks, int *Nt, int *start) {
    int remain = N % num_tasks;
    int esize = N / num_tasks;
    if (tid < remain) { /* each of the first remain task has one more element */
        *Nt = esize + 1;
        *start = *Nt * tid;
    } else {
        *Nt = esize;
        *start = esize * tid + remain;
    }
}
void axpy_dist(int N, REAL Y[], REAL X[], REAL a, int num_tasks) {
    int tid;
    for (tid = 0; tid < num_tasks; tid++) {
        int Nt, start;
        dist(tid, N, num_tasks, &Nt, &start);
        axpy_base_sub(start, Nt, N, Y, X, a);
    }
}
