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

    // Variable for the size of arrays X and Y
    // 2^20 =    1048576
    // 2^24 =   16777216
    // 2^27 =  134217728
    // 2^28 =  268435456 Can't Handle
    int n = 134217728; // Example size, you can set it according to your needs

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
        printf("%.6f ", X[i]);
    }
    printf("\n\n-----------------------------\n");
    // Call the daxpy function from the "CKernel" program and measure execution time
    clock_t C_start_time = clock();
    double* OutC = daxpyC(n, A, X, Y);
    clock_t C_end_time = clock();
    double C_execution_time = (double)(C_end_time - C_start_time) / CLOCKS_PER_SEC;
    printf("Execution time in C: %.6f seconds\n", C_execution_time);

    // Call the daxpy function from the "asmKernel" program and measure execution time
    clock_t Asm_start_time = clock();
    double* OutAsm = daxpyAsm(n, A, X, Y);
    clock_t Asm_end_time = clock();
    double Asm_execution_time = (double)(Asm_end_time - Asm_start_time) / CLOCKS_PER_SEC;
    printf("Execution time in Assembly: %.6f seconds\n", Asm_execution_time);
    
    return 0;
};