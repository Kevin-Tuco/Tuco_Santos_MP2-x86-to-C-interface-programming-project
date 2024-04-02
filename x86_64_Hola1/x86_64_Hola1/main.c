#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

extern double* daxpyAsm(int n, double a, double* y, double* x);
extern double* daxpyC(int n, double A, double X[], double Y[]);

int main() {
    // Random seed initialization
    srand((unsigned int)time(NULL));

    // Randomize double A within a range
    double A = 1.0 + rand() / (RAND_MAX / 9.0);

    // 2^20 =    1048576
    // 2^24 =   16777216
    // 2^27 =  134217728
    // Variable for the size of arrays X and Y
    int n = 1048576; // Example size, you can set it according to your needs

    // Create arrays X and Y with size n dynamically
    double* X = malloc(n * sizeof(double));
    double* Y = malloc(n * sizeof(double));

    if (X == NULL || Y == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Fill arrays X and Y with random double values from 0.0 to 6.0
    for (int i = 0; i < n; i++) {
        X[i] = (double)rand() / RAND_MAX * 6.0; // Random double between 0.0 and 6.0
        Y[i] = (double)rand() / RAND_MAX * 6.0; // Random double between 0.0 and 6.0
    }

    printf("n: %d\n", n);
    printf("A: %.6f\n", A);
    printf("X: ");
    int print_limit = 10; // Limiting to print the first 10 elements
    for (int i = 0; i < n && i < print_limit; i++) {
        printf("%.6f ", X[i]);
    }
    printf("\n");
    printf("Y: ");
    for (int i = 0; i < n && i < print_limit; i++) {
        printf("%.6f ", Y[i]);
    }
    printf("\n\n-----------------------------\n");

    // Measure execution time in C
    volatile double* OutC; // Declare as volatile to prevent optimizations
    LARGE_INTEGER C_start_time, C_end_time, C_frequency;
    QueryPerformanceFrequency(&C_frequency);
    QueryPerformanceCounter(&C_start_time);
    OutC = daxpyC(n, A, X, Y);
    QueryPerformanceCounter(&C_end_time);
    double C_execution_time = (double)(C_end_time.QuadPart - C_start_time.QuadPart) / C_frequency.QuadPart;
    printf("Execution time in C: %.6f seconds\n", C_execution_time);

    // Measure execution time in Assembly
    volatile double* OutAsm; // Declare as volatile to prevent optimizations
    LARGE_INTEGER Asm_start_time, Asm_end_time;
    QueryPerformanceCounter(&Asm_start_time);
    OutAsm = daxpyAsm(n, A, X, Y);
    QueryPerformanceCounter(&Asm_end_time);
    double Asm_execution_time = (double)(Asm_end_time.QuadPart - Asm_start_time.QuadPart) / C_frequency.QuadPart;
    printf("Execution time in Assembly: %.6f seconds\n", Asm_execution_time);

    // Free dynamically allocated memory
    free(X);
    free(Y);
    free(OutC);
    free(OutAsm);

    return 0;
}
