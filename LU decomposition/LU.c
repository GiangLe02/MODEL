#include <stdio.h>
#include <stdlib.h>
#include <time.h>
# include "../header.h"

// void printMatrix(int m, int n, double H[m][n]){
//     for(int i=0;i<m;i++){
//         for(int j=0;j<n;j++){
//             printf("%.10f\t", H[i][j]);
//         }   
//         printf("\n");
//     }
//     printf("\n");
//     return;
// }

// void multiplyNaive(int m,int n, int p, double A[m][n], double B[n][p],double C[m][p]){
//     for (int k=0;k<m;k++){
//         for(int i=0; i<p;i++){
//             double sum = 0;
//             for(int j=0;j<n;j++){
//                 sum += A[k][j]*B[j][i];
//             }
//             C[k][i] = sum;
//         }
//     }
// }

void LU(int n, double L[n][n], double U[n][n], double A[n][n]){
    // initialize L = I
    for(int i = 0; i<n;i++){
        for(int j=0; j<n;j++){
            L[i][j] = 0;
        }
        L[i][i] = 1;
    }

    // initialize U = A
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            U[i][j] = A[i][j];
        }
    }

    for(int x=1;x<n;x++){
        for(int i =x; i <n;i++){
            L[i][x-1] = U[i][x-1]/U[x-1][x-1];
            for(int j=0; j<n;j++){
                U[i][j] = U[i][j]-U[x-1][j]*L[i][x-1];
            }
        }
    }
}

// int main(){

//     srand(time(NULL));
//     // size of matrices
//     // matrix size mxn
//     // int m = 3;
//     int n = 3;
//     double A[n][n];

//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < n; j++){
//             // random number from [-1,1]
//             double r = ((double)rand() / RAND_MAX) * 2.0f - 1.0f;
//             A[i][j] = r;
//         }
//     }
//     printf("A = \n");
//     printMatrix(n,n,A);

//     double L[n][n], U[n][n];
    
//     LU(n,L,U,A);

//     printf("L = \n");
//     printMatrix(n,n,L);
//     printf("U = \n");
//     printMatrix(n,n,U);

//     double Test[n][n];
//     multiplyNaive(n,n,n,L,U,Test);
//     printf("Checking LU by multiplication = \n");
//     printMatrix(n,n,Test);
// }