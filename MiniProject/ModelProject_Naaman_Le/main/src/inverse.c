// Nesrine Naaman & Nguyen Huong Giang LE

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "header.h"

// computing the Inverse of a matrix of size n x n using LU linear system solving
// A.A-1 = Id
// LU. A-1 = Id
void inverseMatrix_LU(int n, double **A, double **invA){
    double **invAi; // we want to calculate the value for each column of the inverse Matrix (column i)
    double **Idi; // the column of the Identity matrix (column i)
    double **L; // matrix L in LU decomposition
    double **U; // matrix U in LU decomposition

    // initializing all of the matrices via dynamic allocation
    invAi = (double**)malloc(n* sizeof(double*));
    Idi = (double**)malloc(n* sizeof(double*));
    L = (double**)malloc(n* sizeof(double*));
    U = (double**)malloc(n* sizeof(double*));
    for(int i=0; i<n; i++){
        invAi[i] = (double*)malloc(sizeof(double));
        Idi[i] = (double*)malloc(sizeof(double));
        L[i] = (double*)malloc(n * sizeof(double));
        U[i] = (double*)malloc(n * sizeof(double));
    }

    // computing the LU decomposition of matrix A and storing the output in matrix L and U
    LU(n, L, U, A);

    // looping through each column
    for(int i =0; i<n;i++){
        // computing the column i of the Identity matrix where all the values are 0 except row i
        for(int j=0;j<n;j++){Idi[j][0]=0;}
        Idi[i][0]=1;

        // we compute the column i of inverse matrix of A by using the LU_linear_solving function to solve the linear system LUx=b
        // LU x = b
        // x -> vector of column i of invA
        // b -> vector of column i of the Identity Matrix
        LU_linear_solving(n, L, U, invAi, Idi);
        // storing the value from invAi to the inverse matrix invA
        for(int j=0;j<n;j++){
            invA[j][i]= invAi[j][0];
        }
    }

    // freeing the memory
    for(int i=0; i<n; i++){
        free(invAi[i]);
        free(Idi[i]);
        free(L[i]);
        free(U[i]);
    }
    free(invAi);
    free(Idi);
    free(L);
    free(U);
}

// computing the Inverse of a matrix A of size n x n using Strassen Algorithm and Strassen multiplication
void inverseMatrix_Strassen_Strassen(int n, double **A, double **C){
    // base case
    // if input matrix A has size 1 x 1
    // directly calculate inverse matrix C = 1/A
    if(n==1){
        // if denominator=0
        if(A[0][0]==0){
            C[0][0]=0;
        }
        else C[0][0]=1/A[0][0];
        return;
    }
    // if n>1, we make it a multiple of 2, pad if necessary, and split n by 2.
    int new_n = n;
    if(n%2==1){new_n += 1;}

    // splitting size = k
    int size = new_n/2;

    // Initializing the padded input matrix and padded output matrix
    double **A_pad, **C_pad;
    A_pad = (double**)malloc(new_n * sizeof(double*));
    C_pad = (double**)malloc(new_n * sizeof(double*));
    for(int i=0; i<new_n; i++){
        A_pad[i] = (double*)malloc(new_n * sizeof(double));
        C_pad[i] = (double*)malloc(new_n * sizeof(double));
    }

    // Applying zero padding
    zeroPadding(n,n, new_n, A, A_pad);
    zeroPadding(n,n,new_n, C, C_pad);

    // Initializing the submatrices of padded A
    // A = (a, b)
    //     (c, d)
    double **a,**b,**c,**d;
    // Initializing the intermediate matrices that will be used to compute the inversion according to the Strassen Inverse Algorithm
    double **e,**Z,**t,**y,**z,**x;
    double **ce, **ceb, **eb, **ebt, **tc, **tce, **ebtc, **ebtce;

    // Dynamically allocating the matrices
    a = (double**)malloc(size * sizeof(double*));
    b = (double**)malloc(size * sizeof(double*));
    c = (double**)malloc(size * sizeof(double*));
    d = (double**)malloc(size * sizeof(double*));
    e = (double**)malloc(size * sizeof(double*));
    Z = (double**)malloc(size * sizeof(double*));
    t = (double**)malloc(size * sizeof(double*));
    y = (double**)malloc(size * sizeof(double*));
    z = (double**)malloc(size * sizeof(double*));
    x = (double**)malloc(size * sizeof(double*));
    ce = (double**)malloc(size * sizeof(double*));
    ceb = (double**)malloc(size * sizeof(double*));
    eb = (double**)malloc(size * sizeof(double*));
    ebt = (double**)malloc(size * sizeof(double*));
    tc = (double**)malloc(size * sizeof(double*));
    tce = (double**)malloc(size * sizeof(double*));
    ebtc = (double**)malloc(size * sizeof(double*));
    ebtce = (double**)malloc(size * sizeof(double*));
    for(int i=0; i<size; i++){
        a[i] = (double*)malloc(size * sizeof(double));
        b[i] = (double*)malloc(size * sizeof(double));
        c[i] = (double*)malloc(size * sizeof(double));
        d[i] = (double*)malloc(size * sizeof(double));
        e[i] = (double*)malloc(size * sizeof(double));
        Z[i] = (double*)malloc(size * sizeof(double));
        t[i] = (double*)malloc(size * sizeof(double));
        y[i] = (double*)malloc(size * sizeof(double));
        z[i] = (double*)malloc(size * sizeof(double));
        x[i] = (double*)malloc(size * sizeof(double));
        ce[i] = (double*)malloc(size * sizeof(double));
        ceb[i] = (double*)malloc(size * sizeof(double));
        eb[i] = (double*)malloc(size * sizeof(double));
        ebt[i] = (double*)malloc(size * sizeof(double));
        tc[i] = (double*)malloc(size * sizeof(double));
        tce[i] = (double*)malloc(size * sizeof(double));
        ebtc[i] = (double*)malloc(size * sizeof(double));
        ebtce[i] = (double*)malloc(size * sizeof(double));
    }

    // Splitting the input matrix after padding (Assigning value from the padded matrices to the initialized submatrices a,b,c,d)
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            a[i][j] = A_pad[i][j];
            b[i][j] = A_pad[i][j+size];
            c[i][j] = A_pad[i+size][j];
            d[i][j] = A_pad[i+size][j+size];
        }
    }

    // recursive call
    // e = a^-1
    inverseMatrix_Strassen_Strassen(size, a, e);
    
    // ceb = c*e*b. We will use multiplyStrassen() function for all matrix multiplications that we will do here 
    multiplyStrassen(size, size, size, c, e, ce);
    multiplyStrassen(size, size, size, ce, b, ceb);

    // Z = d-ceb
    for(int i=0; i<size;i++){
        for(int j=0; j<size; j++){
            Z[i][j]=d[i][j]-ceb[i][j];
        }
    }

    // recursive call
    // t = Z^-1
    inverseMatrix_Strassen_Strassen(size, Z, t);

    // ebt = e*b*t
    multiplyStrassen(size, size, size, e, b, eb);
    multiplyStrassen(size, size, size, eb, t, ebt);

    // y = -ebt
    for(int i=0; i<size;i++){
        for(int j=0; j<size; j++){
            y[i][j]=-ebt[i][j];
        }
    }

    // tce = t*c*e
    multiplyStrassen(size, size, size, t, c, tc);
    multiplyStrassen(size, size, size, tc, e, tce);

    // z = -tce
    for(int i=0; i<size;i++){
        for(int j=0; j<size; j++){
            z[i][j]=-tce[i][j];
        }
    }

    // ebtce = ebt*c*e
    multiplyStrassen(size, size, size, ebt, c, ebtc);
    multiplyStrassen(size, size, size, ebtc, e, ebtce);

    // x = e + ebtce
    for(int i=0; i<size;i++){
        for(int j=0; j<size; j++){
            x[i][j]=e[i][j]+ebtce[i][j];
        }
    }

    // Populating the output matrix C
    // C = (x, y)
    //     (z, t)
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            C_pad[i][j] = x[i][j];
            C_pad[i][j+size] = y[i][j];
            C_pad[i+size][j] = z[i][j];
            C_pad[i+size][j+size] = t[i][j];
        }
    }
    // removing the zero padding
    for(int i =0; i<n;i++){
        for(int j=0;j<n;j++){
            C[i][j] = C_pad[i+new_n-n][j+new_n-n];
        }
    }

    // freeing the memory
    for(int i=0;i<new_n;i++){
        free(A_pad[i]);
        free(C_pad[i]);
    }
    for(int i=0; i<size;i++){
        free(a[i]);
        free(b[i]);
        free(c[i]);
        free(d[i]);
        free(e[i]);
        free(Z[i]);
        free(t[i]);
        free(y[i]);
        free(z[i]);
        free(x[i]);
        free(ce[i]);
        free(ceb[i]);
        free(eb[i]);
        free(ebt[i]);
        free(ebtc[i]);
        free(ebtce[i]);
    }
    free(A_pad);
    free(C_pad);
    free(a);
    free(b);
    free(c);
    free(d);
    free(e);
    free(Z);
    free(t);
    free(y);
    free(z);
    free(x);
    free(ce);
    free(ceb);
    free(eb);
    free(ebt);
    free(ebtc);
    free(ebtce);

    return;   
}

void inverseMatrix_Strassen_Naive(int n, double **A, double **C){
    // base case
    // if input matrix A has size 1 x 1
    // directly calculate inverse matrix C = 1/A
    if(n==1){
        // if denominator=0
        if(A[0][0]==0){
            C[0][0]=0;
        }
        else C[0][0]=1/A[0][0];
        return;
    }
    // if n>1, we make it a multiple of 2, pad if necessary, and split n by 2.
    int new_n = n;
    if(n%2==1){new_n += 1;}

    // splitting size = k
    int size = new_n/2;

    // Initializing the padded input matrix and padded output matrix
    double **A_pad, **C_pad;
    A_pad = (double**)malloc(new_n * sizeof(double*));
    C_pad = (double**)malloc(new_n * sizeof(double*));
    for(int i=0; i<new_n; i++){
        A_pad[i] = (double*)malloc(new_n * sizeof(double));
        C_pad[i] = (double*)malloc(new_n * sizeof(double));
    }

    // Applying zero padding
    zeroPadding(n,n, new_n, A, A_pad);
    zeroPadding(n,n,new_n, C, C_pad);

    // Initializing the submatrices of padded A
    // A = (a, b)
    //     (c, d)
    double **a,**b,**c,**d;
    // Initializing the intermediate matrices that will be used to compute the inversion according to the Strassen Inverse Algorithm
    double **e,**Z,**t,**y,**z,**x;
    double **ce, **ceb, **eb, **ebt, **tc, **tce, **ebtc, **ebtce;

    // Dynamically allocating the matrices
    a = (double**)malloc(size * sizeof(double*));
    b = (double**)malloc(size * sizeof(double*));
    c = (double**)malloc(size * sizeof(double*));
    d = (double**)malloc(size * sizeof(double*));
    e = (double**)malloc(size * sizeof(double*));
    Z = (double**)malloc(size * sizeof(double*));
    t = (double**)malloc(size * sizeof(double*));
    y = (double**)malloc(size * sizeof(double*));
    z = (double**)malloc(size * sizeof(double*));
    x = (double**)malloc(size * sizeof(double*));
    ce = (double**)malloc(size * sizeof(double*));
    ceb = (double**)malloc(size * sizeof(double*));
    eb = (double**)malloc(size * sizeof(double*));
    ebt = (double**)malloc(size * sizeof(double*));
    tc = (double**)malloc(size * sizeof(double*));
    tce = (double**)malloc(size * sizeof(double*));
    ebtc = (double**)malloc(size * sizeof(double*));
    ebtce = (double**)malloc(size * sizeof(double*));
    for(int i=0; i<size; i++){
        a[i] = (double*)malloc(size * sizeof(double));
        b[i] = (double*)malloc(size * sizeof(double));
        c[i] = (double*)malloc(size * sizeof(double));
        d[i] = (double*)malloc(size * sizeof(double));
        e[i] = (double*)malloc(size * sizeof(double));
        Z[i] = (double*)malloc(size * sizeof(double));
        t[i] = (double*)malloc(size * sizeof(double));
        y[i] = (double*)malloc(size * sizeof(double));
        z[i] = (double*)malloc(size * sizeof(double));
        x[i] = (double*)malloc(size * sizeof(double));
        ce[i] = (double*)malloc(size * sizeof(double));
        ceb[i] = (double*)malloc(size * sizeof(double));
        eb[i] = (double*)malloc(size * sizeof(double));
        ebt[i] = (double*)malloc(size * sizeof(double));
        tc[i] = (double*)malloc(size * sizeof(double));
        tce[i] = (double*)malloc(size * sizeof(double));
        ebtc[i] = (double*)malloc(size * sizeof(double));
        ebtce[i] = (double*)malloc(size * sizeof(double));
    }

    // Splitting the input matrix after padding (Assigning value from the padded matrices to the initialized submatrices a,b,c,d)
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            a[i][j] = A_pad[i][j];
            b[i][j] = A_pad[i][j+size];
            c[i][j] = A_pad[i+size][j];
            d[i][j] = A_pad[i+size][j+size];
        }
    }

    // recursive call
    // e = a^-1
    inverseMatrix_Strassen_Naive(size, a, e);
    
    // ceb = c*e*b. We will use multiplyNaive() function for all matrix multiplications that we will do here 
    multiplyNaive(size, size, size, c, e, ce);
    multiplyNaive(size, size, size, ce, b, ceb);

    // Z = d - ceb
    for(int i=0; i<size;i++){
        for(int j=0; j<size; j++){
            Z[i][j]=d[i][j]-ceb[i][j];
        }
    }

    // recursive call
    // t = Z^-1
    inverseMatrix_Strassen_Naive(size, Z, t);

    // ebt = e*b*t
    multiplyNaive(size, size, size, e, b, eb);
    multiplyNaive(size, size, size, eb, t, ebt);

    // y = -ebt
    for(int i=0; i<size;i++){
        for(int j=0; j<size; j++){
            y[i][j]=-ebt[i][j];
        }
    }

    // tce = t*c*e
    multiplyNaive(size, size, size, t, c, tc);
    multiplyNaive(size, size, size, tc, e, tce);

    // z = -tce
    for(int i=0; i<size;i++){
        for(int j=0; j<size; j++){
            z[i][j]=-tce[i][j];
        }
    }

    // ebtce = ebt*c*e
    multiplyNaive(size, size, size, ebt, c, ebtc);
    multiplyNaive(size, size, size, ebtc, e, ebtce);

    // x = e+ebtce
    for(int i=0; i<size;i++){
        for(int j=0; j<size; j++){
            x[i][j]=e[i][j]+ebtce[i][j];
        }
    }      

    // Populating the output matrix C
    // C = (x, y)
    //     (z, t)
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            C_pad[i][j] = x[i][j];
            C_pad[i][j+size] = y[i][j];
            C_pad[i+size][j] = z[i][j];
            C_pad[i+size][j+size] = t[i][j];
        }
    }

    // removing the zero padding
    for(int i =0; i<n;i++){
        for(int j=0;j<n;j++){
            C[i][j] = C_pad[i+new_n-n][j+new_n-n];
        }
    }
    
    // freeing the memory
    for(int i=0;i<new_n;i++){
        free(A_pad[i]);
        free(C_pad[i]);
    }
    for(int i=0; i<size;i++){
        free(a[i]);
        free(b[i]);
        free(c[i]);
        free(d[i]);
        free(e[i]);
        free(Z[i]);
        free(t[i]);
        free(y[i]);
        free(z[i]);
        free(x[i]);
        free(ce[i]);
        free(ceb[i]);
        free(eb[i]);
        free(ebt[i]);
        free(ebtc[i]);
        free(ebtce[i]);
    }
    free(A_pad);
    free(C_pad);
    free(a);
    free(b);
    free(c);
    free(d);
    free(e);
    free(Z);
    free(t);
    free(y);
    free(z);
    free(x);
    free(ce);
    free(ceb);
    free(eb);
    free(ebt);
    free(ebtc);
    free(ebtce);
    return;   
}