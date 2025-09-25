#include<stdio.h>
#include <stdlib.h>
#include<time.h>
#include<string.h>
#include "../header.h"


//printed matrix
void printMatrix(int m, int n, double H[m][n]){
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            printf("%.10f\t", H[i][j]);
        }   
        printf("\n");
    }
    printf("\n");
    return;
}

//multiply 2 matrice A and B using Naive method
void multiplyNaive(int m,int n, int p, double A[m][n], double B[n][p],double C[m][p]){
    for (int k=0;k<m;k++){
        for(int i=0; i<p;i++){
            double sum = 0;
            for(int j=0;j<n;j++){
                sum += A[k][j]*B[j][i];
            }
            C[k][i] = sum;
        }
    }
}

void zeroPadding(int m, int n, int max, double A[m][n], double A_pad[max][max]){
    for(int i =0; i<max;i++){
        for(int j = 0; j<max;j++){
            A_pad[i][j] = 0;
            if(i>=max-m & j >= max-n){
                A_pad[i][j] = A[i-max+m][j-max+n];
            }
        }
    }
}

void multiplyStrassen(int m, int n, int p, double A[m][n], double B[n][p], double C[m][p]){
    int max = 0;
    max =  m > n? (m > p? m: p): (n > p? n: p);
    if(max%2==1){max += 1;}
    // splitting A and B to 4
    int size = max/2;
    double A_pad[max][max];
    double B_pad[max][max];
    double C_pad[max][max];

    zeroPadding(m,n, max, A, A_pad);
    zeroPadding(n,p,max,B, B_pad);
    zeroPadding(m,p,max, C, C_pad);

    if(size == 1){
        double q1 = A_pad[0][0] * (B_pad[0][0]+B_pad[1][0]);
        double q2 = A_pad[1][1] * (B_pad[0][1]+B_pad[1][1]);
        double q3 = (A_pad[1][1]-A_pad[0][0])*(B_pad[1][0]-B_pad[0][1]);
        double q4 = (A_pad[0][1]-A_pad[1][1])*(B_pad[1][0]+B_pad[1][1]);
        double q5 = (A_pad[0][1]-A_pad[0][0])*B_pad[1][0];
        double q6 = (A_pad[1][0]-A_pad[0][0])*(B_pad[0][0]+B_pad[0][1]);
        double q7 = (A_pad[1][0]-A_pad[1][1])*B_pad[0][1];

        C_pad[0][0] = q1 + q5;
        C_pad[0][1] = q2+q3+q4-q5;
        C_pad[1][0] = q1+q3+q6-q7;
        C_pad[1][1] = q2+q7;

        for(int i =0; i<m;i++){
            for(int j=0;j<p;j++){
                C[i][j]= C_pad[i+max-m][j+max-p];
            }
        }
        return;
    }
    double A0[size][size],A1[size][size],A2[size][size],A3[size][size];
    double B0[size][size],B1[size][size],B2[size][size],B3[size][size];
    // double C0[size][size],C1[size][size],C2[size][size],C3[size][size];


    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            A0[i][j] = A_pad[i][j];
            A1[i][j] = A_pad[i][j+size];
            A2[i][j] = A_pad[i+size][j];
            A3[i][j] = A_pad[i+size][j+size];

            B0[i][j] = B_pad[i][j];
            B1[i][j] = B_pad[i][j+size];
            B2[i][j] = B_pad[i+size][j];
            B3[i][j] = B_pad[i+size][j+size];
        }
    }
    // printMatrix(size,size,B0);
    // printMatrix(size,size,B1);
    // printMatrix(size,size,B2);
    // printMatrix(size,size,B3);
    double E1[size][size],E2[size][size],E3[size][size],E4[size][size],E5[size][size],E6[size][size],E7[size][size];
    double A1_minus_A3[size][size];
    double A0_plus_A3[size][size];
    double A0_minus_A2[size][size];
    double A0_plus_A1[size][size];
    double A2_plus_A3[size][size];
    double B2_plus_B3[size][size];
    double B0_plus_B3[size][size];
    double B0_plus_B1[size][size];
    double B1_minus_B3[size][size];
    double B2_minus_B0[size][size];

    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            A1_minus_A3[i][j] = A1[i][j]-A3[i][j];
            A0_plus_A3[i][j] = A0[i][j]+A3[i][j];
            A0_minus_A2[i][j] = A0[i][j]-A2[i][j];
            A0_plus_A1[i][j] = A0[i][j] + A1[i][j];
            A2_plus_A3[i][j] = A2[i][j] + A3[i][j];
            B2_plus_B3[i][j] = B2[i][j] + B3[i][j];
            B0_plus_B3[i][j] = B0[i][j] + B3[i][j];
            B0_plus_B1[i][j] = B0[i][j] + B1[i][j];
            B1_minus_B3[i][j] = B1[i][j] - B3[i][j];
            B2_minus_B0[i][j] = B2[i][j] - B0[i][j];
        }
    }
    // printMatrix(size,size,A2_plus_A3);
    // printMatrix(size,size,B2_plus_B3);

    multiplyStrassen(size,size,size,A1_minus_A3,B2_plus_B3, E1);
    multiplyStrassen(size,size,size,A0_plus_A3,B0_plus_B3,E2);
    multiplyStrassen(size,size,size,A0_minus_A2,B0_plus_B1,E3);

    multiplyStrassen(size,size,size,A0_plus_A1,B3,E4);
    multiplyStrassen(size,size,size,A0,B1_minus_B3,E5);
    multiplyStrassen(size,size,size,A3,B2_minus_B0,E6);
    multiplyStrassen(size,size,size,A2_plus_A3,B0,E7);

    // printMatrix(size,size,E4);
    // printMatrix(size,size,E5);
    // printMatrix(size,size,E6);
    // printMatrix(size,size,E7);


    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            C_pad[i][j] = E1[i][j] + E2[i][j] - E4[i][j] + E6[i][j];
            C_pad[i][j+size] = E4[i][j] + E5[i][j];
            C_pad[i+size][j] = E6[i][j] + E7[i][j];
            C_pad[i+size][j+size] = E2[i][j] - E3[i][j] + E5[i][j] - E7[i][j];
        }
    }

    for(int i =0; i<m;i++){
        for(int j=0;j<p;j++){
            // printf("%d  %d %.5f\n",i, j, C[i][j]);
            // printf("%d  %d  %.5f\n",i+max-m, j+max-p, C_pad[i+max-m][j+max-p]);

            C[i][j] = C_pad[i+max-m][j+max-p];

        }
    }
    // printMatrix(m,p,C);
    return;
}

// int main() {
//     srand(time(NULL));
//     // size of matrices
//     // matrix size mxn multiply with matrix nxp
//     int m = 3;
//     int n = 3;
//     int p = 5;
//     double A[m][n];
//     double B[n][p];

//     for (int i = 0; i < m; i++) {
//         for (int j = 0; j < n; j++){
//             // random number from [-1,1]
//             double r = ((double)rand() / RAND_MAX) * 2.0f - 1.0f;
//             A[i][j] = r;
//         }
//     }
//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < p; j++){
//             double r = ((double)rand() / RAND_MAX) * 2.0f - 1.0f;
//             B[i][j] = r;
//         }
//     }

//     printf("A = \n");
//     printMatrix(m,n,A);

//     printf("B = \n");
//     printMatrix(n,p,B);

//     double C1[m][p];

//     multiplyNaive(m,n,p,A,B,C1);
//     printf("The multiply matrix using Naive method is : \n");
//     printMatrix(m,p, C1);

//     double C2[m][p];
//     multiplyStrassen(m,n,p,A,B,C2);
//     printf("The multiply matrix using Strassen method is : \n");
//     printMatrix(m,p, C2);
//     return 0;
// }