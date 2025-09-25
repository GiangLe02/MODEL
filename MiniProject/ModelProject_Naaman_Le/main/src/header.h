// Nesrine Naaman & Nguyen Huong Giang LE

#ifndef MY_HEADER_H
#define MY_HEADER_H

// GENERAL FUNCTIONS
/** 1. printing a matrix to output 
 *      input:  m - height of matrix
 *              n - width of matrix
 *              H - matrix of size mxn */
void printMatrix(int m, int n, double **H);

/** 2. padding a matrix with zero columns and rows
 *      input:  m,n - matrix A's size
 *              A - matrix with size mxn
 *      output: A_pad - matrix after zero-padding with size max x max */
void zeroPadding(int m, int n, int max, double **A, double **A_pad);

/** 3. Creating a matrix with random  floating-point double-precision coefficients in range [-1;1]
*       input:  m,n - matrix size
*       output: A - matrix with random coefs */
void random_matrix(int m, int n, double **A);

/** 4. Checking if a user input is a positive integer
 *      output: 0 - if not a positive integer
 *              the user input in int - if a positive integer
 */
int scan_entry();

// MATRIX MULTIPLICATION
/** 5. Computing the matrix multiplication of A and B using Naive method
*       input:  m,n,p - sizes of A and B (mxn, nxp)
                A - matrix of size mxn
*               B - matrix of size nxp
*       output: C - matrix of size mxp, the result of A.B */
void multiplyNaive(int m,int n, int p, double **A, double **B,double **C);

/** 6. Computing the matrix multiplication of A and B using Strassen method
*       input:  m,n,p - sizes of A and B (mxn, nxp)
                A - matrix of size mxn
*               B - matrix of size nxp
*       output: C - matrix of size mxp, the result of A.B */ 
void multiplyStrassen(int m, int n, int p, double **A, double **B, double **C);


// LU decomposition
/** 7. Computing LU decomposition of matrix A
*       input:  n - size of matrix A
                A - matrix of size nxn
*       output: L - lower triangular matrix with 1s on the diagonal
*               U - upper triangular matrix */
void LU(int n, double **L, double **U, double **A);

/** 8. Solving the linear system Ax=b using A's LU decomposition
*       input:  n - size of matrix A
                L,U -  LU matrices decomposition of A
                b - vector in system  the Ax=b
*       ouput:  x - the unknown vector we are solving in Ax=b */
void LU_linear_solving(int n, double **L, double **U, double **x, double **b);

// INVERSION
/** 9. Computing the Inverse of matrix A using its LU decomposition
*       input:  n - size of matrix A
                A - matrix of size nxn
        output: invA - inverse A matrix*/
void inverseMatrix_LU(int n, double **A, double **invA);

/** 10. Computing the Inverse of matrix A using Strassen Algorithm with Strassen-based Multiplication
 *      input:  n - size of matrix A 
 *              A - matrix of size nxn
 *      output: C - inverse of matrix A */
void inverseMatrix_Strassen_Strassen(int n, double **A, double **C);

/** 11. Computing the Inverse of matrix A using Strassen Algorithm with Naive-based Multiplication
 *      input:  n - size of matrix A 
 *              A - matrix of size nxn
 *      output: C - inverse of matrix A */
void inverseMatrix_Strassen_Naive(int n, double **A, double **C);
#endif