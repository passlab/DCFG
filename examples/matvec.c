/*
 * matrix vector multiplication: Y[] = A[][] * B[]
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/timeb.h>
#include <string.h>

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

void zero(REAL A[], int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            A[i * n + j] = 0.0;
        }
    }
}

void init(int N, REAL A[]) {
    int i;
    for (i = 0; i < N; i++) {
        A[i] = (REAL) drand48();
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

void matvec_base(int M, int N, REAL Y[], REAL A[][N], REAL B[]);

void matvec_base_sub(int i_start, int Mt, int M, int N, REAL Y[], REAL A[][N], REAL B[]);

void matvec_row_dist(int M, int N, REAL Y[], REAL A[][N], REAL B[], int num_tasks);

int main(int argc, char *argv[]) {
    int N = 256;
    int num_tasks = 4; /* default number of tasks */
    double elapsed; /* for timing */
    double elapsed_dist;
    if (argc < 2) {
        fprintf(stderr, "Usage: matvec <n(%dx%d)> [<#tasks(%d)>]\n", N, N, num_tasks);
    } else N = atoi(argv[1]);
    if (argc > 2) num_tasks = atoi(argv[2]);
    REAL A[N][N];
    REAL B[N];
    REAL Y_base[N];
    REAL Y_dist[N];
    /* more C matrix needed */

    srand48((1 << 12));
    init(N * N, (REAL *) A);
    init(N, B);

    /* example run */
    elapsed = read_timer();
    matvec_base(N, N, Y_base, A, B);
    elapsed = (read_timer() - elapsed);

    elapsed_dist = read_timer();
    matvec_row_dist(N, N, Y_dist, A, B, num_tasks);
    elapsed_dist = (read_timer() - elapsed_dist);

    /* you should add the call to each function and time the execution */
    printf("======================================================================================================\n");
    printf("\tMatrix Vector Multiplication: Y[N] = A[N][N] * B[N], N=%d, %d tasks for dist\n", N, num_tasks);
    printf("------------------------------------------------------------------------------------------------------\n");
    printf("Performance:\t\tRuntime (ms)\t MFLOPS \t\tError (compared to base)\n");
    printf("------------------------------------------------------------------------------------------------------\n");
    printf("matvec_base:\t\t%4f\t%4f \t\t%g\n", elapsed * 1.0e3, (2.0 * N * N) / (1.0e6 * elapsed), check(Y_base,Y_base, N));
    printf("matvec_row_dist:\t%4f\t%4f \t\t%g\n", elapsed_dist * 1.0e3, (2.0 * N * N) / (1.0e6 * elapsed_dist), check(Y_base, Y_dist, N));
    return 0;

}

void matvec_base(int M, int N, REAL Y[], REAL A[][N], REAL B[]) {
    int i, j;
    for (i = 0; i < M; i++) {
        REAL temp = 0.0;
        for (j = 0; j < N; j++) {
            temp += A[i][j] * B[j];
        }
        Y[i] = temp;
    }
}

void matvec_base_sub(int i_start, int Mt, int M, int N, REAL Y[], REAL A[][N], REAL B[]) {
    int i, j;
    for (i = i_start; i < i_start + Mt; i++) {
        REAL temp = 0.0;
        for (j = 0; j < N; j++) {
            temp += A[i][j] * B[j];
        }
        Y[i] = temp;
    }
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

void matvec_row_dist(int M, int N, REAL Y[], REAL A[][N], REAL B[], int num_tasks) {
    int tid;
    for (tid = 0; tid < num_tasks; tid++) {
        int Mt, i_start;
        dist(tid, M, num_tasks, &Mt, &i_start);
        matvec_base_sub(i_start, Mt, M, N, Y, A, B);
    }
}
