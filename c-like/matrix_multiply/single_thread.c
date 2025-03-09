#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M 1500
#define N 1200
#define B 1400

void init_matrix(int **m, size_t row, size_t col) {
    for (size_t i = 0; i < row; i++) {
        for (size_t j = 0; j < col; j++) {
            m[i][j] = rand() % 100;
        }
    }
}

void print_matrix(int **m, size_t row, size_t col) {
    printf("--------------------------------\n");
    for (size_t i = 0; i < row; i++) {
        for (size_t j = 0; j < col; j++) {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
    printf("--------------------------------\n");
}

int **T(int **m, size_t row, size_t col) {
    int **mT = (int **)malloc(sizeof(int *) * col);
    for (size_t i = 0; i < col; i++) {
        mT[i] = (int *)malloc(sizeof(int) * row);
    }

    for (size_t i = 0; i < row; i++) {
        for (size_t j = 0; j < col; j++) {
            mT[j][i] = m[i][j];
        }
    }

    return mT;
}

void multiply(int **res, size_t res_row, size_t mid_len, size_t res_col,
        int **m1, int **m2) {
    for (size_t i = 0; i < res_row; i++) {
        for (size_t j = 0; j < res_col; j++) {

            for (size_t k = 0; k < mid_len; k++) {
                res[i][j] += m1[i][k] * m2[k][j];
            }

        }
    }
}

void multiply_T(int **res, size_t res_row, size_t mid_len, size_t res_col,
        int **m1, int **m2) {
    for (size_t i = 0; i < res_row; i++) {
        for (size_t j = 0; j < res_col; j++) {

            for (size_t k = 0; k < mid_len; k++) {
                res[i][j] += m1[i][k] * m2[j][k];
            }

        }
    }
}

int main() {
    srand(time(NULL));

    int **m1 = (int **)malloc(sizeof(int *) * M);
    for (size_t i = 0; i < M; i++) {
        m1[i] = (int *)malloc(sizeof(int) * N);
    }
    int **m2 = (int **)malloc(sizeof(int *) * N);
    for (size_t i = 0; i < N; i++) {
        m2[i] = (int *)malloc(sizeof(int) * B);
    }
    int **res = (int **)malloc(sizeof(int *) * M);
    for (size_t i = 0; i < M; i++) {
        res[i] = (int *)malloc(sizeof(int) * B);
    }

    init_matrix(m1, M, N);
    init_matrix(m2, N, B);

    int **m2T = T(m2, N, B);

    // print_matrix(m1, M, N);
    // print_matrix(m2, N, B);
    time_t start = time(NULL);
    multiply(res, M, N, B, m1, m2);
    printf("time: %lu\n", time(NULL) - start);

    start = time(NULL);
    multiply_T(res, M, N, B, m1, m2T);
    printf("time: %lu\n", time(NULL) - start);

    // print_matrix(res, M, B);
    return 0;
}
