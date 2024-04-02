#include <stdio.h>
#include <stdlib.h>

double* daxpyC(int n, double A, double X[], double Y[]) {
    // Dynamically allocate memory for the result vector OutC
    double* OutC = (double*)malloc(n * sizeof(double));
    if (OutC == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    // Calculate OutC[i] = A * X[i] + Y[i] for each i
    for (int i = 0; i < n; i++) {
        OutC[i] = A * X[i] + Y[i];
    }
    printf("Resulting array OutC:\n");
    int print_limit = 10; // Limiting to print the first 10 elements
    for (int i = 0; i < n && i < print_limit; i++) {
        printf("%.6f ", OutC[i]);
    }
    printf("\n");
    // Return the pointer to the result vector OutC
    return OutC;
}
