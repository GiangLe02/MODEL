// Nesrine Naaman & Nguyen Huong Giang LE

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
# include "header.h"

// computing LU decomposition of a matrix A of size n x n
// A = LU
// L - lower triangular matrix of size n x n with the diagonals =1
// U - upper triangular matrix of size n x n
void LU(int n, double **L, double **U, double **A){
    // initializing L = Id 
    // All of the values of L = 0 except the diagonal = 1
    for(int i = 0; i<n;i++){
        for(int j=0; j<n;j++){
            L[i][j] = 0;
        }
        L[i][i] = 1;
    }

    // initializing U = A
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            U[i][j] = A[i][j];
        }
    }
    // The first row of U is the first row of A => doesn't change
    // We loop from the second row of A to the end
    for(int x=1;x<n;x++){
        // Each element from the column i of L = the same position from column i of U / the pivot
        for(int i =x; i <n;i++){
            L[i][x-1] = U[i][x-1]/U[x-1][x-1];
            for(int j=0; j<n;j++){
                U[i][j] = U[i][j]-U[x-1][j]*L[i][x-1];
            }
        }
    }
}

// Solving the linear system Ax=b using LU decomposition of matrix A
// Ax=b / A=LU
// LUx = b
// Solve Ly = b
// Solve Ux = y
void LU_linear_solving(int n, double **L, double **U, double **x, double **b){
    double **y;
    y = (double**)malloc(n* sizeof(double*));
    for(int i=0;i<n;i++){
        y[i] = (double*)malloc(sizeof(double));
    }
    // solving for y (Ly=b)
    for(int i=0; i<n;i++){
        y[i][0] = b[i][0];
        for(int j=0;j<i;j++){
            y[i][0] -= y[j][0]*L[i][j];
        }
    }

    // y is known, now we solve Ux=y
    for(int i=n-1; i>=0;i--){
        double b_i = y[i][0];
        for(int j=n-1;j>i;j--){
            b_i -= x[j][0]*U[i][j];
        }
        x[i][0] = b_i/U[i][i];
    }
    // x is known, system is solved
    for(int i=0;i<n;i++){
        free(y[i]);
    }
    free(y);
    return;
}