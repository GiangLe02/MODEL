#include<stdio.h>
#include <stdlib.h>
#include<gmp.h>
#include<string.h>
#include<mpfr.h>

void printMatrix(int n, mpfr_t **A){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            // printf("%f ",A[i][j]);
            mpfr_printf("%.50Rf \t", A[i][j]);
        }
        printf("\n");
    }
}

void updateLU(int n, int x, mpfr_t **L, mpfr_t **U)
{               
    for(int i =x; i <n;i++)
    {
        mpfr_div(L[i][x-1],U[i][x-1],U[x-1][x-1],MPFR_RNDN);
        // mpfr_printf("%.5Rf ",U[i][x-1]);
        // mpfr_printf("%.5Rf ",U[x-1][x-1]);
        // mpfr_printf("%.5Rf ",L[i][x-1]);
        for(int j=0; j<n;j++){
            mpfr_t temp; mpfr_init(temp);
            mpfr_mul(temp,U[x-1][j],L[i][x-1],MPFR_RNDN);
            mpfr_sub(U[i][j],U[i][j],temp,MPFR_RNDN);
        }
        // printf("\n");
    }
}

void swapRow(int n, int x, int y, mpfr_t **U, mpfr_t **P, mpfr_t **L){
    // i, j: row ith swap with row jth
    // U[x][0-n-1] <-> U[y][0-n-1]
    for(int i=0;i<n;i++){
        mpfr_swap(U[x][i],U[y][i]);

        // swap P also
        mpfr_swap(P[i][x],P[i][y]);
    }
    if(x>0){
        for(int i=0;i<x;i++){
            mpfr_swap(L[x][i],L[y][i]);
        }
    }

}
void swapColumn(int n, int x, int y, mpfr_t **U, mpfr_t **Q){
    // x,y: column xth swap with column xth
    for(int i=0;i<n;i++){
        mpfr_swap(U[i][x],U[i][y]);

        // swap Q also
        mpfr_swap(Q[x][i],Q[y][i]);
    }
}

int main(){
    // pow(2,20) = mpfr_pow(mpfr_t x,mpfr_t 2,mpfr_t 20, ROunded)
    int a[3][3] = {{0,20,40},{1,40,108},{30,54,10}};
    int n =3;
    
    // Declare a 2D array of mpfr_t using pointers
    mpfr_t **A;
    // Step 2: Allocate memory for the row pointers
    A = (mpfr_t **)malloc(n * sizeof(mpfr_t *));

    // Step 3: Allocate memory for each row (columns of mpfr_t variables)
    for (int i = 0; i < n; i++) {
        A[i] = (mpfr_t *)malloc(n * sizeof(mpfr_t));
        if (A[i] == NULL) {
            return 1;
        }
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            mpfr_init(A[i][j]);
            mpfr_ui_pow_ui(A[i][j], 2, a[i][j], MPFR_RNDN);
        }
    }
    
    mpfr_t **P, **L, **U, **Q;

    // Step 2: Allocate memory for the row pointers
    P = (mpfr_t **)malloc(n * sizeof(mpfr_t *));
    L = (mpfr_t **)malloc(n * sizeof(mpfr_t *));
    U = (mpfr_t **)malloc(n * sizeof(mpfr_t *));
    Q = (mpfr_t **)malloc(n * sizeof(mpfr_t *));

    // Step 3: Allocate memory for each row (which contains mpfr_t elements)
    for (int i = 0; i < n; i++) {
        P[i] = (mpfr_t *)malloc(n * sizeof(mpfr_t));
        L[i] = (mpfr_t *)malloc(n * sizeof(mpfr_t));
        U[i] = (mpfr_t *)malloc(n * sizeof(mpfr_t));
        Q[i] = (mpfr_t *)malloc(n * sizeof(mpfr_t));
    }

    // Step 4: Initialize each element in the 2D array and set it to 0
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            mpfr_init(P[i][j]); 
            mpfr_init(L[i][j]); 
            mpfr_init(Q[i][j]); 
            if(i==j){
                mpfr_set_ui(P[i][j],1,MPFR_RNDN);
                mpfr_set_ui(L[i][j],1,MPFR_RNDN);
                mpfr_set_ui(Q[i][j],1,MPFR_RNDN);
            }
            else{
                mpfr_set_zero(P[i][j], 1);
                mpfr_set_zero(L[i][j], 1);
                mpfr_set_zero(Q[i][j], 1); 
            }
            
        }
    }

    // initialize U = A
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            mpfr_init(U[i][j]);
            mpfr_set(U[i][j],A[i][j],MPFR_RNDN);
        }
    }
        
    for(int x=1;x<n;x++){
        // calculate max value in matrix
        mpfr_t max;
        mpfr_init(max);
        mpfr_set_zero(max,1);
        int row = 0;
        int column = 0;
        for(int i =x-1;i<n;i++){
            for(int j =x-1;j<n;j++){
                mpfr_t temp;
                mpfr_init(temp);
                mpfr_abs(temp, U[i][j], MPFR_RNDN);
                if(mpfr_cmp(temp,max)>0){
                    mpfr_set(max, U[i][j], MPFR_RNDN);
                    row = i;
                    column = j;
                }
            } 
        }
        swapRow(n,x-1,row,U,P,L);
        swapColumn(n, x-1,column,U,Q);
        updateLU(n,x,L,U);
    }
    printf("P={");
    printMatrix(n,P);

    printf("L = {");
    printMatrix(n,L);

    printf("U = ");
    printMatrix(n,U);

    printf("Q={");
    printMatrix(n,Q);

    // Clear the memory for each element
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            mpfr_clear(A[i][j]);  // Clear each mpfr_t element
            mpfr_clear(P[i][j]);
            mpfr_clear(L[i][j]);
            mpfr_clear(U[i][j]);
            mpfr_clear(Q[i][j]);
        }
        free(A[i]);  // Free each row
        free(P[i]); 
        free(L[i]); 
        free(U[i]); 
        free(Q[i]); 
    }

    // Step 8: Free the row pointer array
    free(A);
    free(P);
    free(L);
    free(U);
    free(Q);
    return 0;
}