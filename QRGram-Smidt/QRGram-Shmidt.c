#include<stdio.h>
#include<math.h>
#include<string.h>

void printMatrix(int m,int n, double A[m][n]){
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            // printf("%f ",A[i][j]);
            printf("%.5f\t", A[i][j]);
        }
        printf("\n");
    }
}

int main(){
    int n=2;
    int m=4;
    double A[4][2] = {{5,5},{12,12},{0,3},{0,-4}};
    double Q[m][m];
    double R[m][n];
    memset( Q, 0, m*m*sizeof(double) );
    memset( R, 0, n*m*sizeof(double) );

    double sum =0;
    for(int i = 0; i<m; i++){
        sum += A[i][0]*A[i][0];
    }
    R[0][0] = sqrt(sum);

    for(int i=0;i<m;i++){
        Q[i][0] = A[i][0]/R[0][0];
    }

    for(int i = 1; i<n;i++){
        for(int j=0;j<m;j++){
            Q[j][i] = A[j][i];
        }
        for(int j =0; j<i;j++){
            sum = 0;
            for(int k=0;k<m;k++){
                sum += Q[k][j]*Q[k][i];
            }
            R[j][i] = sum;
        }
        sum =0;
        for(int k = 0; k<m; k++){
            sum += Q[k][i]*Q[k][i];
        }
        R[i][i] = sqrt(sum);
        for(int k=0; k<m;k++){
            Q[k][i] = Q[k][i]/R[i][i];
        }
    }
    printf("Q = \n");
    printMatrix(m,m,Q);
    printf("\nR = \n");
    printMatrix(m,n,R);
    return 0;
}