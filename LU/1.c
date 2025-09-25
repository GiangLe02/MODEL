#include <stdio.h>

int main(){
    float A[4][4] = {{4,4,8,1},{2,8,7,1},{1,3,6,1},{-4,6,5,1}};
    float L[4][4]={0}, U[4][4]={0};
    
    // initialize L = I
    for(int i = 0; i<4;i++){
        L[i][i] = 1;
    }
    int n=4;
    
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
    printf("L = {");
    for(int i=0;i<n;i++){
        for(int j=0;j<4;j++){
            printf("%f ",L[i][j]);
        }
        printf("\n");
    }
    printf("U = ");
    for(int i=0;i<n;i++){
        for(int j=0;j<4;j++){
            printf("%f ",U[i][j]);
        }
        printf("\n");
    }
    return 0;
}