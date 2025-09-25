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
double coef(double x, double y,double z){
    double n = sqrt(y*y + z*z);
    return x/n;
}
void multiplyMatrix(int m1, int n1, double A[m1][n1], int n2, double B[n1][n2], double C[m1][n2]){
    for(int i=0; i<m1; i++){
        for(int j=0; j<n2;j++){
            double sum = 0;
            for(int k=0;k<n1;k++){
                sum += A[i][k]*B[k][j];
            }
            C[i][j] = sum;
        }
    }
}

int main(){
    int n=2;
    int m=3;
    double A[3][2] = {{3,-3},{4,-4},{0,40}};
    double Q[m][m];
    double R[m][n];
    memset( Q, 0, m*m*sizeof(double) );
    memset( R, 0, n*m*sizeof(double) );

    for(int i=0;i<m;i++){
        Q[i][i]=1;
        for(int j=0;j<n;j++){
            R[i][j] = A[i][j];
        }
    }

    for(int j =0;j<n;j++){
        for(int i =j+1; i<m;i++){
            double G[m][m];
            memset( G, 0, m*m*sizeof(double) );
            double GT[m][m];
            memset(GT, 0, m*m*sizeof(double) );
            for(int k=0;k<m;k++){
                G[k][k]=1;
                GT[k][k]=1;
            }
            double c = coef(R[j][j],R[j][j],R[i][j]);
            double s = coef(R[i][j],R[j][j],R[i][j]);
        
            G[i][i]=c;
            G[j][j]= c;
            G[j][i]= s;
            G[i][j]= -s;
            GT[i][i]=c;
            GT[j][j]= c;
            GT[j][i]= -s;
            GT[i][j]= s;
            // printf("G = \n");
            // printMatrix(m,m,G);
            multiplyMatrix(m,m,G,n,R,R);
            multiplyMatrix(m,m,Q,m,GT,Q);
        }
    }
    printf("Q = \n");
    printMatrix(m,m,Q);
    printf("\nR = \n");
    printMatrix(m,n,R);
    return 0;
}