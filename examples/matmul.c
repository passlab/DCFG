/*
 * Rectangular matrix multiplication
 * A[M][K] * B[k][N] = C[M][N]
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

void init(int M, int N, REAL A[][N]) {
    int i, j;

    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            A[i][j] = (REAL) drand48();
        }
    }
}

double maxerror(int M, int N, REAL A[][N], REAL B[][N]) {
    int i, j;
    double error = 0.0;

    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            double diff = (A[i][j] - B[i][j]) / A[i][j];
            if (diff < 0)
                diff = -diff;
            if (diff > error)
                error = diff;
        }
    }
    return error;
}

void get_task_2D_grid(int total_tasks, int *num_tasks_row, int *num_tasks_col) {
    /* we use a simple 2-d array to store two factors (a, and b) of an interger number n so a*b=n */
    int factor_2D[][2] = { /* MAX_TASKS+1 */
            {0,0}, /* n = 0 */
            {1,1}, /* n = 1 */
            {1,2}, // 2
            {1,3}, // 3
            {2,2}, // 4
            {1,5}, // 5
            {2,3}, // 6
            {1,7}, // 7
            {2,4}, // 8
            {3,3}, // 9
            {2,5}, // 10
            {1,11},// 11
            {3,4}, // 12
            {1,13},// 13
            {2,7}, // 14
            {3,5}, // 15
            {4,4}, // 16
            {1,17},// 17
            {3,6}, // 18 or {2,9}
            {1,19},// 19
            {4,5}, // 20
            {3,7}, // 21
            {2,11},// 22
            {1,23},// 23
            {4,6}, // 24 or {2,12}
            {5,5}, // 25
    };
    int max_good_factor_number = 25;

    if (total_tasks > max_good_factor_number) {
        printf("Not able to do a good factoring for you! Now %d = %d * %d\n", total_tasks, 1, total_tasks);
        *num_tasks_row = 1;
        *num_tasks_col = total_tasks;
    } else {
        *num_tasks_row = factor_2D[total_tasks][0];
        *num_tasks_col = factor_2D[total_tasks][1];
    }
}

void matmul_base(int M, int K, int N, REAL A[][K], REAL B[][N], REAL C[][N]);
void matmul_base_1(int M, int K, int N, REAL A[][K], REAL B[][N], REAL C[][N]);
void matmul_base_sub(int i_start, int j_start, int Mt, int Nt, int M, int K, int N, REAL A[][K], REAL B[][N], REAL C[][N]);
void matmul_row1D_dist(int M, int K, int N, REAL A[][K], REAL B[][N], REAL C[][N], int num_tasks);
void matmul_column1D_dist(int M, int K, int N, REAL A[][K], REAL B[][N], REAL C[][N], int num_tasks);
void matmul_rowcol2D_dist(int M, int K, int N, REAL A[][K], REAL B[][N], REAL C[][N], int num_tasks_row, int num_tasks_col);

int main(int argc, char *argv[]) {
    int N = 256;
    int num_tasks = 4; /* 5 is default number of tasks */
    double elapsed_base, elapsed_base_1, elapsed_row1D_dist, elapsed_column1D_dist, elapsed_rowcol2D_dist; /* for timing */
    if (argc < 2) {
        fprintf(stderr, "Usage: matmul <n(%dx%d)> [<#tasks(%d)>]\n", N, N, num_tasks);
    } else N = atoi(argv[1]);
    if (argc > 2) num_tasks = atoi(argv[2]);
    REAL A[N][N];
    REAL B[N][N];
    REAL C_base[N][N];
    REAL C_base_1[N][N];
    REAL C_row1D_dist[N][N];
    REAL C_column1D_dist[N][N];
    REAL C_rowcol2D_dist[N][N];

    srand48((1 << 12));
    init(N, N, A);
    init(N, N, B);

    /* example run */
    elapsed_base = read_timer();
    matmul_base(N, N, N, A, B, C_base);
    elapsed_base = (read_timer() - elapsed_base);

    elapsed_base_1 = read_timer();
    matmul_base_1(N, N, N, A, B, C_base_1);
    elapsed_base_1 = (read_timer() - elapsed_base_1);

    elapsed_row1D_dist = read_timer();
    matmul_row1D_dist(N, N, N, A, B, C_row1D_dist, num_tasks);
    elapsed_row1D_dist = (read_timer() - elapsed_row1D_dist);

    elapsed_column1D_dist = read_timer();
    matmul_column1D_dist(N, N, N, A, B, C_column1D_dist, num_tasks);
    elapsed_column1D_dist = (read_timer() - elapsed_column1D_dist);

    elapsed_rowcol2D_dist = read_timer();
    int num_tasks_row, num_tasks_col;
    get_task_2D_grid(num_tasks, &num_tasks_row, &num_tasks_col);
    matmul_rowcol2D_dist(N, N, N, A, B, C_rowcol2D_dist, num_tasks_row, num_tasks_col);
    elapsed_rowcol2D_dist = (read_timer() - elapsed_rowcol2D_dist);
    /* you should add the call to each function and time the execution */

    printf("======================================================================================================\n");
    printf("Matrix Multiplication: A[M][K] * B[k][N] = C[M][N], M=K=N=%d, %d tasks for 1D dist, %dx%d tasks for 2D dist\n", N, num_tasks, num_tasks_row, num_tasks_col);
    printf("------------------------------------------------------------------------------------------------------\n");
    printf("Performance:\t\tRuntime (ms)\t MFLOPS \t\tError (compared to base)\n");
    printf("------------------------------------------------------------------------------------------------------\n");
    printf("matmul_base:\t\t%4f\t%4f \t\t%g\n", elapsed_base * 1.0e3, ((((2.0 * N) * N) * N) / (1.0e6 * elapsed_base)), maxerror(N, N, C_base, C_base));
    printf("matmul_base_1:\t\t%4f\t%4f \t\t%g\n", elapsed_base_1 * 1.0e3, ((((2.0 * N) * N) * N) / (1.0e6 * elapsed_base_1)), maxerror(N, N, C_base, C_base_1));
    printf("matmul_row1D_dist:\t%4f\t%4f \t\t%g\n", elapsed_row1D_dist * 1.0e3, ((((2.0 * N) * N) * N) / (1.0e6 * elapsed_row1D_dist)), maxerror(N, N, C_base, C_row1D_dist));
    printf("matmul_column1D_dist:\t%4f\t%4f \t\t%g\n", elapsed_column1D_dist * 1.0e3, ((((2.0 * N) * N) * N) / (1.0e6 * elapsed_column1D_dist)), maxerror(N, N, C_base, C_column1D_dist));
    printf("matmul_rowcol2D_dist:\t%4f\t%4f \t\t%g\n", elapsed_rowcol2D_dist * 1.0e3, ((((2.0 * N) * N) * N) / (1.0e6 * elapsed_rowcol2D_dist)), maxerror(N, N, C_base, C_rowcol2D_dist));
    return 0;
}

void matmul_base(int M, int K, int N, REAL A[][K], REAL B[][N], REAL C[][N]) {
    int i, j, k;
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            REAL temp = 0.0;
            for (k = 0; k < K; k++) {
                temp += A[i][k] * B[k][j];
            }
            C[i][j] = temp;
        }
    }
}

void matmul_base_1(int M, int K, int N, REAL A[][K], REAL B[][N], REAL C[][N]) {
    int i, j, k;
    for (j = 0; j < N; j++) {
        for (i = 0; i < M; i++) {
            REAL temp = 0.0;
            for (k = 0; k < K; k++) {
                temp += A[i][k] * B[k][j];
            }
            C[i][j] = temp;
        }
    }
}

void matmul_base_sub(int i_start, int j_start, int Mt, int Nt, int M, int K, int N,
        REAL A[][K], REAL B[][N], REAL C[][N]) {
    int i, j, k;
    for (i = i_start; i < i_start + Mt; i++) {
        for (j = j_start; j < j_start + Nt; j++) {
            REAL temp = 0.0;
            for (k = 0; k < K; k++) {
                temp += A[i][k] * B[k][j];
            }
            C[i][j] = temp;
        }
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

void matmul_row1D_dist(int M, int K, int N, REAL A[][K], REAL B[][N], REAL C[][N], int num_tasks) {
    int tid;
    for (tid = 0; tid < num_tasks; tid++) {
        int Mt, i_start;
        dist(tid, M, num_tasks, &Mt, &i_start);
        matmul_base_sub(i_start, 0, Mt, N, M, K, N, A, B, C);
    }
}

void matmul_column1D_dist(int M, int K, int N, REAL A[][K], REAL B[][N], REAL C[][N], int num_tasks) {
    int tid;
    for (tid = 0; tid < num_tasks; tid++) {
        int Nt, j_start;
        dist(tid, N, num_tasks, &Nt, &j_start);
        matmul_base_sub(0, j_start, M, Nt, M, K, N, A, B, C);
    }
}

void matmul_rowcol2D_dist(int M, int K, int N, REAL A[][K], REAL B[][N], REAL C[][N], int num_tasks_row, int num_tasks_col) {
    int tid_row, tid_col;
    for (tid_row = 0; tid_row < num_tasks_row; tid_row++) {
        int Mt, i_start;
        dist(tid_row, M, num_tasks_row, &Mt, &i_start);

        for (tid_col = 0; tid_col < num_tasks_col; tid_col++) {
            int Nt, j_start;
            dist(tid_col, N, num_tasks_col, &Nt, &j_start);
            matmul_base_sub(i_start, j_start, Mt, Nt, M, K, N, A, B, C);
        }
    }
}
