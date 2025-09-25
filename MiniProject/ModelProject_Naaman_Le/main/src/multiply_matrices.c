// Nesrine Naaman & Nguyen Huong Giang LE

#include<stdio.h>
#include <stdlib.h>
#include "header.h"

//multiplying 2 matrices A and B using the Naive method
// C = A.B
void multiplyNaive(int m,int n, int p, double **A, double **B,double **C){
    // A is of size mxn, B of size nxp , C of size mxp
    // Considering the rows of A as Ai, and the columns of B as Bj
    // Naive matrix multiplication  => row of A x col of B 
    // Ci,j = sum(A_{i,k}*B_{k,j}) with k from 0->n-1  (n: nbr of cols of A)
    for (int i=0;i<m;i++){ // loop through each row of A
        for(int j=0; j<p;j++){ // loop through each column of B
            double sum = 0;
            for(int k=0;k<n;k++){
                sum += A[i][k]*B[k][j]; // calculate the sum of all the multiplication of element from Ai with element from Bj
            }
            C[i][j] = sum; // Assign element from C in row i and column j with this sum
        }
    }
}

// multiplying 2 matrices A and B using the Strassen method
// C = A.B
void multiplyStrassen(int m, int n, int p, double **A, double **B, double **C){
    // Strassen requires multiplying 2 matrices of size 2kx2k => Zero padding in case the size is not even

    // finding the maximum size between A and B
    int max = 0;
    max =  m > n? (m > p? m: p): (n > p? n: p);
    
    // base case: if A and B have one element only, assign the output C to their product
    if(max ==1){
        C[0][0] = A[0][0]*B[0][0];
        return;
    }

    // change max to even number if it's not
    if(max%2==1){max += 1;}

    // splitting size = k 
    int size = max/2;

    // Initializing the padding Matrix of size max x max of the 2 input Matrices and the output matrix
    double **A_pad, **B_pad, **C_pad;
    A_pad = (double**)malloc(max* sizeof(double*));
    B_pad = (double**)malloc(max* sizeof(double*));
    C_pad = (double**)malloc(max* sizeof(double*));
    for(int i=0; i<max; i++){
         A_pad[i] = (double*)malloc(max * sizeof(double));
         B_pad[i] = (double*)malloc(max * sizeof(double));
         C_pad[i] = (double*)malloc(max * sizeof(double));
    }

    // Applying zero padding
    zeroPadding(m,n, max, A, A_pad);
    zeroPadding(n,p,max,B, B_pad);
    zeroPadding(m,p,max, C, C_pad);

    // Initializing the matrices that will be obtained after splitting the padded A into 4 (elements/submatrices a, b, c, and d)
    // A = (a, b)
    //     (c, d)
    double **a,**b,**c,**d;
    // Initializing the matrices that will be obtained after splitting the padded B into 4 (elements/submatrices x, y, z, and t)
    // B = (x, y)
    //     (z, t)
    double **x,**y,**z,**t;

    // Dynamically allocating the splitting matrices having size half of that of the input padded matrices
    a = (double**)malloc(size * sizeof(double*));
    b = (double**)malloc(size * sizeof(double*));
    c = (double**)malloc(size * sizeof(double*));
    d = (double**)malloc(size * sizeof(double*));
    x = (double**)malloc(size * sizeof(double*));
    y = (double**)malloc(size * sizeof(double*));
    z = (double**)malloc(size * sizeof(double*));
    t = (double**)malloc(size * sizeof(double*));

    // Initializing the intermediate matrices used to compute the output matrix in the Strassen Algorithm
    double **Q1,**Q2,**Q3,**Q4,**Q5,**Q6,**Q7;
    Q1 = (double**)malloc(size* sizeof(double*));
    Q2 = (double**)malloc(size* sizeof(double*));
    Q3 = (double**)malloc(size* sizeof(double*));
    Q4 = (double**)malloc(size* sizeof(double*));
    Q5 = (double**)malloc(size* sizeof(double*));
    Q6 = (double**)malloc(size* sizeof(double*));
    Q7 = (double**)malloc(size* sizeof(double*));

    double **x_plus_z;
    double **y_plus_t;
    double **d_minus_a;
    double **z_minus_y;
    double **b_minus_d;
    double **z_plus_t;
    double **b_minus_a;
    double **c_minus_a;
    double **x_plus_y;
    double **c_minus_d;
    x_plus_z = (double**)malloc(size* sizeof(double*));
    y_plus_t = (double**)malloc(size* sizeof(double*));
    d_minus_a = (double**)malloc(size* sizeof(double*));
    z_minus_y = (double**)malloc(size* sizeof(double*));
    b_minus_d = (double**)malloc(size* sizeof(double*));
    z_plus_t = (double**)malloc(size* sizeof(double*));
    b_minus_a = (double**)malloc(size* sizeof(double*));
    c_minus_a = (double**)malloc(size* sizeof(double*));
    x_plus_y = (double**)malloc(size* sizeof(double*));
    c_minus_d = (double**)malloc(size* sizeof(double*));
    for(int i=0; i<size; i++){
         a[i] = (double*)malloc(size * sizeof(double));
         b[i] = (double*)malloc(size * sizeof(double));
         c[i] = (double*)malloc(size * sizeof(double));
         d[i] = (double*)malloc(size * sizeof(double));
         x[i] = (double*)malloc(size * sizeof(double));
         y[i] = (double*)malloc(size * sizeof(double));
         z[i] = (double*)malloc(size * sizeof(double));
         t[i] = (double*)malloc(size * sizeof(double));
         
         Q1[i] = (double*)malloc(size * sizeof(double));
         Q2[i] = (double*)malloc(size * sizeof(double));
         Q3[i] = (double*)malloc(size * sizeof(double));
         Q4[i] = (double*)malloc(size * sizeof(double));
         Q5[i] = (double*)malloc(size * sizeof(double));
         Q6[i] = (double*)malloc(size * sizeof(double));
         Q7[i] = (double*)malloc(size * sizeof(double));
         
         x_plus_z[i] = (double*)malloc(size * sizeof(double));
         y_plus_t[i] = (double*)malloc(size * sizeof(double));
         d_minus_a[i] = (double*)malloc(size * sizeof(double));
         z_minus_y[i] = (double*)malloc(size * sizeof(double));
         b_minus_d[i] = (double*)malloc(size * sizeof(double));
         z_plus_t[i] = (double*)malloc(size * sizeof(double));
         b_minus_a[i] = (double*)malloc(size * sizeof(double));
         c_minus_a[i] = (double*)malloc(size * sizeof(double));
         x_plus_y[i] = (double*)malloc(size * sizeof(double));
         c_minus_d[i] = (double*)malloc(size * sizeof(double));
    }

    // Splitting the input matrices after padding (Assigning value from padded matrices to the initialized submatrices a,b,c,d and x,y,z,t)
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            a[i][j] = A_pad[i][j];
            b[i][j] = A_pad[i][j+size];
            c[i][j] = A_pad[i+size][j];
            d[i][j] = A_pad[i+size][j+size];

            x[i][j] = B_pad[i][j];
            y[i][j] = B_pad[i][j+size];
            z[i][j] = B_pad[i+size][j];
            t[i][j] = B_pad[i+size][j+size];
        }
    }
    

    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            x_plus_z[i][j]  = x[i][j] + z[i][j];
            y_plus_t[i][j]  = y[i][j] + t[i][j];
            d_minus_a[i][j] = d[i][j] - a[i][j];
            z_minus_y[i][j] = z[i][j] - y[i][j];
            b_minus_d[i][j] = b[i][j] - d[i][j];
            z_plus_t[i][j]  = z[i][j] + t[i][j];
            b_minus_a[i][j] = b[i][j] - a[i][j];
            c_minus_a[i][j] = c[i][j] - a[i][j];
            x_plus_y[i][j]  = x[i][j] + y[i][j];
            c_minus_d[i][j] = c[i][j] - d[i][j];
        }
    }

    // recursive call
    // Q1 = a * (x + z)
    multiplyStrassen(size,size,size,a,x_plus_z, Q1);
    // Q2 = d * (y + t)
    multiplyStrassen(size,size,size,d,y_plus_t,Q2);
    // Q3 = (d - a) * (z - y)
    multiplyStrassen(size,size,size,d_minus_a,z_minus_y,Q3);
    // Q4 = (b - d) * (z + t)
    multiplyStrassen(size,size,size,b_minus_d,z_plus_t,Q4);
    // Q5 = (b - a) * z
    multiplyStrassen(size,size,size,b_minus_a,z,Q5);
    // Q6 = (c - a) * (x + y)
    multiplyStrassen(size,size,size,c_minus_a,x_plus_y,Q6);
    // Q7 = (c - d) * y
    multiplyStrassen(size,size,size,c_minus_d,y,Q7);

    // Calculating the result for each part of the output matrix C and combining results
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            C_pad[i][j] = Q1[i][j] + Q5[i][j];
            C_pad[i][j+size] = Q2[i][j] + Q3[i][j] + Q4[i][j] - Q5[i][j];
            C_pad[i+size][j] = Q1[i][j] + Q3[i][j] + Q6[i][j] - Q7[i][j];
            C_pad[i+size][j+size] = Q2[i][j] + Q7[i][j];
        }
    }

    // removing the zero padding from the output matrix C
    for(int i =0; i<m;i++){
        for(int j=0;j<p;j++){
            C[i][j] = C_pad[i+max-m][j+max-p];
        }
    }

    // freeing the memory
    for (int i = 0; i < max; i++){
        free(A_pad[i]);
        free(B_pad[i]);
        free(C_pad[i]);
    }
    for (int i = 0; i < size; i++){
        free(a[i]);
        free(b[i]);
        free(c[i]);
        free(d[i]);
        free(x[i]);
        free(y[i]);
        free(z[i]);
        free(t[i]);

        free(Q1[i]);
        free(Q2[i]);
        free(Q3[i]);
        free(Q4[i]);
        free(Q5[i]);
        free(Q6[i]);
        free(Q7[i]);

        free(x_plus_z[i]);
        free(y_plus_t[i]);
        free(d_minus_a[i]);
        free(z_minus_y[i]);
        free(b_minus_d[i]);
        free(z_plus_t[i]);
        free(b_minus_a[i]);
        free(c_minus_a[i]);
        free(x_plus_y[i]);
        free(c_minus_d[i]);
    }
    free(A_pad);
    free(B_pad);
    free(C_pad);

    free(a);
    free(b);
    free(c);
    free(d);
    free(x);
    free(y);
    free(z);
    free(t);

    free(Q1);
    free(Q2);
    free(Q3);
    free(Q4);
    free(Q5);
    free(Q6);
    free(Q7);

    free(x_plus_z);
    free(y_plus_t);
    free(d_minus_a);
    free(z_minus_y);
    free(b_minus_d);
    free(z_plus_t);
    free(b_minus_a);
    free(c_minus_a);
    free(x_plus_y);
    free(c_minus_d);
    return;
}