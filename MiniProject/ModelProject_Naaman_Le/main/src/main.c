// Nesrine Naaman & Nguyen Huong Giang LE

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "header.h"

// The main menu of the program
void menu(){
    printf("Main Menu\n");
    printf("1. Naive (Classical) Matrix Multiplication\n");
    printf("2. Strassen Matrix Multiplication\n");
    printf("3. LU decomposition\n");
    printf("4. Inverse Matrix using LU\n");
    printf("5. Inverse Matrix using Strassen\n");
    printf("6. Compare Naive and Strassen Matrix Multiplication\n");
    printf("7. Compare LU and Strassen Matrix Inversion\n");
    printf("8. Exit\n");
}

void Naive_Multiplication(){    
    int m,n,p; // initializing the sizes of the matrices A and B

    // we create a file in a time_testing_output folder which logs the time it will take to compute the naive multiplication of A and B if the user chooses this option
    FILE *file = fopen("../time_testing_output/NaiveMult_Time_testing.txt", "a");

    printf("We're multiplying 2 matrices of size m x n and n x p using the Naive method.\n");

    // Asking the user to enter the sizes of the Matrices A and B (m x n and n x p)
    do{
        printf("Enter a positive number for m: ");
        m=scan_entry(); // returns 0 if the input is invalid (not a positive integer), and the user input otherwise
        if(m==0){
            printf("Wrong input!\n");
        }
    } while(m==0); // asking the user to keep re-entering input until it's a valid one
    do{
        printf("Enter a positive number for n: ");
        n=scan_entry();
        if(n==0){
            printf("Wrong input!\n");
        }
    } while(n==0);

    do{
        printf("Enter a positive number for p: ");
        p=scan_entry();
        if(p==0){
            printf("Wrong input!\n");
        }
    } while(p==0);

    // Storing the sizes of m,n,p to the output file
    fprintf(file ,"Multiplying Matrices of size %dx%d and %dx%d\n", m, n, n, p);

    // Intitializing the matrices using dynamic allocations
    double **A,**B;
    A = (double**)malloc(m* sizeof(double*));
    for(int i=0; i<m;i++){
        A[i] = (double*)malloc(n*sizeof(double));
    }
    B = (double**)malloc(n* sizeof(double*));
    for(int i=0; i<n;i++){
        B[i] = (double*)malloc(p*sizeof(double));
    }

    // Assigning random values to the input matrices A and B
    random_matrix(m,n,A);
    random_matrix(n,p,B);

    // Printing Matrix A
    printf("A = \n");
    printMatrix(m,n,A);

    // Printing Matrix B
    printf("B = \n");
    printMatrix(n,p,B);

    // initializing the result Matrix C = A*B of size m x p
    double **C;
    C = (double**)malloc(m* sizeof(double*));
    for(int i=0; i<m;i++){
        C[i] = (double*)malloc(p*sizeof(double));
    }

    clock_t start_time, end_time;
    double time_taken;

    // Recording the start time
    start_time = clock();

    // Calling our function to compute the Naive Multiplication of A and B
    multiplyNaive(m,n,p,A,B,C);

    // Recording the end time
    end_time = clock();

    // Calculating the time taken to compute naive multiplication in seconds
    time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    // printing the result matrix C and the time it took to compute this matrix
    printf("The resulting matrix using the Naive method is : \n");
    printMatrix(m,p, C);
    printf("Time to compute Naive matrix multiplication is %f seconds\n", time_taken);

    // storing the time to the output log file
    fprintf(file, "Computation time for Naive Matrix Multiplication: %.10f seconds \n\n", time_taken);
    fclose(file);

    // freeing the memory
    for(int i=0; i<m;i++){
        free(A[i]);
        free(C[i]);
    }
    for(int i=0;i<n;i++){free(B[i]);}
    free(A); free(B); free(C);
}

void Strassen_Multiplication(){
    int m,n,p;

    // we create a file in a time_testing_output folder which logs the time it will take to compute the Strassen multiplication of A and B if the user chooses this option
    FILE *file = fopen("../time_testing_output/StrassenMult_Time_testing.txt", "a");

    printf("We're multiplying 2 matrices of size mxn and nxp using Strassen Algorithm.\n");
    // Asking the user to enter the sizes of the Matrices A and B (m x n and n x p)
    do{
        printf("Enter a positive number for m: ");
        m=scan_entry();
        if(m==0){
            printf("Wrong input!\n");
        }
    } while(m==0);
    do{
        printf("Enter a positive number for n: ");
        n=scan_entry();
        if(n==0){
            printf("Wrong input!\n");
        }
    } while(n==0);

    do{
        printf("Enter a positive number for p: ");
        p=scan_entry();
        if(p==0){
            printf("Wrong input!\n");
        }
    } while(p==0);
    
    // Storing the sizes of m,n,p to the output file
    fprintf(file ,"Multiplying Matrices of size %dx%d and %dx%d\n", m, n, n, p);

    // Initializing the input matrices A and B
    double **A,**B;
    A = (double**)malloc(m* sizeof(double*));
    for(int i=0; i<m;i++){
        A[i] = (double*)malloc(n*sizeof(double));
    }
    B = (double**)malloc(n* sizeof(double*));
    for(int i=0; i<n;i++){
        B[i] = (double*)malloc(p*sizeof(double));
    }

    // Assigning random values to the input matrices A and B
    random_matrix(m,n,A);
    random_matrix(n,p,B);

    // printing matrix A
    printf("A = \n");
    printMatrix(m,n,A);

    // printing matrix B
    printf("B = \n");
    printMatrix(n,p,B);

    // initializing the result Matrix C = A*B of size m x p
    double **C1;
    C1 = (double**)malloc(m* sizeof(double*));
    for(int i=0; i<m;i++){
        C1[i] = (double*)malloc(p*sizeof(double));
    }

    clock_t start_time, end_time;
    double time_taken;

    // Recording the start time
    start_time = clock();

    // Calling our function to compute Strassen Multiplication of A and B
    multiplyStrassen(m,n,p,A,B,C1);

    // Recording the end time
    end_time = clock();

    // Calculating the time taken to compute Strassen Multiplication in seconds
    time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    // printing the result matrix C
    printf("The resulting matrix using Strassen method is : \n");
    printMatrix(m,p, C1);

    // printing the computation time
    printf("Time to compute Strassen matrix multiplication is %f seconds\n", time_taken);
    
    // saving the computation time to the output log file
    fprintf(file, "Computation time for Strassen Matrix Multiplication: %.10f seconds \n\n", time_taken);
    fclose(file);

    // freeing the memory
    for(int i=0; i<m;i++){
        free(A[i]);
        free(C1[i]);
    }
    for(int i=0;i<n;i++){free(B[i]);}
    free(A); free(B); free(C1);
}

void LU_Decomposition(){
    int n;

    // we create a file in a time_testing_output folder which logs the time it will take to compute the naive multiplication of A and B if the user chooses this option
    FILE *file = fopen("../time_testing_output/LU_Time_testing.txt", "a");

    printf("We're computing the LU decomposition of matrix A having size nxn.\n");
    
    // Asking the user to enter the sizes of the Matrix A (n x n)
    do{
        printf("Enter a positive number for n: ");
        n=scan_entry();
        if(n==0){
            printf("Wrong input!\n");
        }
    } while(n==0);

    // Storing the size n to the output file
    fprintf(file ,"Matrix size of %dx%d\n", n, n);

    // initializing the input matrix A and the output matrices L, U
    // all of them are in size n x n
    double **A,**L, **U;
    A = (double**)malloc(n* sizeof(double*));
    L = (double**)malloc(n* sizeof(double*));
    U = (double**)malloc(n* sizeof(double*));

    for(int i=0; i<n;i++){
        A[i] = (double*)malloc(n*sizeof(double));
        L[i] = (double*)malloc(n*sizeof(double));
        U[i] = (double*)malloc(n*sizeof(double));
    }

    // Assigning random values to matrix A
    random_matrix(n,n,A);
    // printing matrix A
    printf("A = \n");
    printMatrix(n,n,A);

    clock_t start_time, end_time;
    double time_taken;

    // Recording the start time
    start_time = clock();

    // Calling our LU function to compute the LU decomposition of matrix A
    LU(n,L,U,A);

    // Recording the end time
    end_time = clock();

    // Calculating the time taken to compute LU decomposition in seconds
    time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    // Printing Matrix L
    printf("L = \n");
    printMatrix(n,n,L);
    // Printing Matrix U
    printf("U = \n");
    printMatrix(n,n,U);
    // printing the computation time of LU
    printf("Time to compute LU decomposition is %f seconds\n", time_taken);
    // Storing the computation time to the output log file
    fprintf(file, "Computation time for LU Decomposition: %.10f seconds \n\n", time_taken);
    fclose(file);

    // freeing the memory
    for(int i=0; i<n;i++){
        free(A[i]);
        free(L[i]);
        free(U[i]);
    }
    free(A); free(L); free(U);
    return;
}

void Inverse_LU(){
    int n;
    // we create a file in a time_testing_output folder which logs the time it will take to compute the Inverse of A using its LU decomposition if the user chooses this option
    FILE *file = fopen("../time_testing_output/InvLU_Time_testing.txt", "a");

    // Asking the user to input the size of the matrix A (n x n)
    printf("We're computing the inverse of matrix A having size nxn using its LU decomposition.\n");
    do{
        printf("Enter a positive number for n: ");
        n=scan_entry();
        if(n==0){
            printf("Wrong input!\n");
        }
    } while(n==0);  

    // Saveing the size n to the output file
    fprintf(file ,"Inverting using LU a Matrix of size %dx%d \n", n, n);

    // Initilizing the input matrix A and the output matrix invA
    double **A,**invA;
    A = (double**)malloc(n* sizeof(double*));
    invA = (double**)malloc(n* sizeof(double*));
    for(int i=0; i<n;i++){
        A[i] = (double*)malloc(n*sizeof(double));
        invA[i] = (double*)malloc(n*sizeof(double));
    }

    // Assigning random values for matrix A
    random_matrix(n,n,A);

    // printing matrix A
    printf("A = \n");
    printMatrix(n,n,A);

    clock_t start_time, end_time;
    double time_taken;

    // Recording the start time
    start_time = clock();

    // Calling our inverse LU function to compute the inverse of matrix A
    inverseMatrix_LU(n,A,invA);

    // Recording the end time
    end_time = clock();

    // Calculating the time taken to compute inversion using LU in seconds
    time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;    

    // printing the result matrix
    printf("A-1 = \n");
    printMatrix(n,n,invA);
    //printing the computation time
    printf("Time to compute the inverse matrix A is %f seconds\n", time_taken);
    
    // Saving the computation time to the output log file
    fprintf(file, "Computation time for Matrix Inversion using LU: %.10f seconds \n\n", time_taken);
    fclose(file);

    // freeing the memory
    for(int i=0; i<n;i++){
        free(A[i]);
        free(invA[i]);
    }
    free(A); free(invA);
    return;
}

void Inverse_Strassen(){
    int n;
    // we create a file in a time_testing_output folder which logs the time it will take to compute the Inverse of A using Strassen Algorithm if the user chooses this option
    FILE *file = fopen("../time_testing_output/InvStrassen_Time_testing.txt", "a");
    
    // Asking the user to input the size of the matrix A (n x n)
    printf("We're computing the inverse of matrix A having size nxn using Strassen Algorithm.\n");
    do{
        printf("Enter a positive number for n: ");
        n=scan_entry();
        if(n==0){
            printf("Wrong input!\n");
        }
    } while(n==0); 

    // Saving the size n to the output file
    fprintf(file ,"Inverting using Strassen a Matrix of size %dx%d \n", n, n);

    // Initializing the input matrix A of size n x n and the output matrix invA of size n x n
    double **A,**invA;
    A = (double**)malloc(n* sizeof(double*));
    invA = (double**)malloc(n* sizeof(double*));
    for(int i=0; i<n;i++){
        A[i] = (double*)malloc(n*sizeof(double));
        invA[i] = (double*)malloc(n*sizeof(double));
    }

    // Assigning the random values to the matrix A and printing it
    random_matrix(n,n,A);
    printf("original matrix:\n");
    printMatrix(n,n,A);
    printf("\n");

    clock_t start_time1, end_time1;
    double time_taken1;

    // Recording the start time
    start_time1 = clock();

    // Calling our Inverse Strassen function which uses Strassen multiplication
    inverseMatrix_Strassen_Strassen(n,A,invA);

    // Recording the end time
    end_time1 = clock();

    // Calculating the time taken to compute inverse Strassen using Strassen multiplication in seconds
    time_taken1 = ((double)(end_time1 - start_time1)) / CLOCKS_PER_SEC;   
    
    // printing the output inverse Matrix
    printf("Inverse using Strassen and Strassen Mult: \n");
    printMatrix(n,n,invA);
    printf("\n");

    clock_t start_time2, end_time2;
    double time_taken2;

    // Recording the start time
    start_time2 = clock();

    // Calling our Inverse Strassen function which uses the naive multiplication
    inverseMatrix_Strassen_Naive(n,A,invA);

    // Recording the end time
    end_time2 = clock();

    // Calculating the time taken to compute Inverse Strassen using Naive Multiplication in seconds
    time_taken2 = ((double)(end_time2 - start_time2)) / CLOCKS_PER_SEC; 

    // printing the output inverse Matrix
    printf("Inverse using Strassen and Naive Mult: \n");
    printMatrix(n,n,invA);

    // Saving the time to compute Inverse Strassen Algorithm to the output log file
    fprintf(file, "Computation time for Matrix Inversion using Strassen and Strassen Multiplication: %.10f seconds \n", time_taken1);
    printf("Time to compute the inverse matrix A using Strassen and Strassen multiplication is %f seconds\n", time_taken1);

    fprintf(file, "Computation time for Matrix Inversion using Strassen and Naive Multiplication: %.10f seconds \n\n", time_taken2);
    printf("Time to compute the inverse matrix A using Strassen and Naive multiplication is %f seconds\n", time_taken2);
    
    fclose(file);

    // freeing the memory
    for(int i=0; i<n;i++){
        free(A[i]);
        free(invA[i]);
    }
    free(A); free(invA);
    return;
}

void Compare_Mult(){
    int m,n,p;
    
    // we create a file in a time_testing_output folder which logs the time it will take to compute matrix multiplication using the Naive method and Strassen's method if the user chooses this option
    FILE *file = fopen("../time_testing_output/MatrixMult_Time_testing.txt", "a");
    
    printf("We're multiplying 2 matrices of size mxn and nxp.\n");
    // Asking the user to input the sizes of the Matrices A and B (m x n and n x p)
    do{
        printf("Enter a positive number for m: ");
        m=scan_entry();
        if(m==0){
            printf("Wrong input!\n");
        }
    } while(m==0);
    do{
        printf("Enter a positive number for n: ");
        n=scan_entry();
        if(n==0){
            printf("Wrong input!\n");
        }
    } while(n==0);

    do{
        printf("Enter a positive number for p: ");
        p=scan_entry();
        if(p==0){
            printf("Wrong input!\n");
        }
    } while(p==0);

    // Initializing the input matrices A and B
    double **A,**B;
    A = (double**)malloc(m* sizeof(double*));
    for(int i=0; i<m;i++){
        A[i] = (double*)malloc(n*sizeof(double));
    }
    B = (double**)malloc(n* sizeof(double*));
    for(int i=0; i<n;i++){
        B[i] = (double*)malloc(p*sizeof(double));
    }

    // Saving the size m,n,p to the output file
    fprintf(file ,"Matrix size of %dx%d and %dx%d\n", m, n, n, p);

    random_matrix(m,n,A);
    random_matrix(n,p,B);

    printf("A = \n");
    printMatrix(m,n,A);

    printf("B = \n");
    printMatrix(n,p,B);

    // Initializing the output matrices
    double **C1, **C2;
    C1 = (double**)malloc(m* sizeof(double*));
    C2 = (double**)malloc(m* sizeof(double*));
    for(int i=0; i<m;i++){
        C1[i] = (double*)malloc(p*sizeof(double));
        C2[i] = (double*)malloc(p*sizeof(double));
    }

    clock_t start_time1, end_time1;
    double time_taken1;

    // Recording the start time
    start_time1 = clock();

    // Calling our Naive Matrix Multiplication function 
    multiplyNaive(m,n,p,A,B,C1);

    // Recording the end time
    end_time1 = clock();

    // Calculating the time taken to compute Naive Multiplication in seconds
    time_taken1 = ((double)(end_time1 - start_time1)) / CLOCKS_PER_SEC; 
    // Printing the result matrix of Naive Multiplication
    printf("The resulting matrix using the Naive method is : \n");
    printMatrix(m,p, C1);

    clock_t start_time2, end_time2;
    double time_taken2;

    // Recording the start time
    start_time2 = clock();

    // Calling our Strassen Multiplication function
    multiplyStrassen(m,n,p,A,B,C2);

    // Recording the end time
    end_time2 = clock();

    // Calculating the time taken to compute Strassen Multiplication in seconds
    time_taken2 = ((double)(end_time2 - start_time2)) / CLOCKS_PER_SEC;  
    // Printing the result matrix of Strassen Multiplication  
    printf("The resulting matrix using Strassen method is : \n");
    printMatrix(m,p, C2);

    // Printing the computation time of Naive Multiplication
    printf("Time to compute the Naive Matrix Multiplication is %f seconds\n", time_taken1);
    // Printing the computation time of Strassen Multiplication
    printf("Time to compute the Strassen Matrix Multiplication is %f seconds\n", time_taken2);

    // Saving the computation time for both the Naive and the Strassen matrix Multiplication to the output log file
    fprintf(file, "Computation time Naive: %.10f seconds \n", time_taken1);
    fprintf(file, "Computation time Strassen: %.10f seconds \n\n", time_taken2);
    fclose(file);

    // freeing the memory
    for(int i=0; i<m;i++){
        free(A[i]);
        free(C1[i]);
        free(C2[i]);
    }
    for(int i=0;i<n;i++){free(B[i]);}
    free(A); free(B); free(C1); free(C2);
    return;
}

void Compare_Inv(){
    int n;
    // we create a file in a time_testing_output folder which logs the time it will take to compute the inverse of a matrix using both the LU decomposition method and Strassen's method if the user chooses this option
    FILE *file = fopen("../time_testing_output/MatrixInverse_Time_testing.txt", "a");

    // Asking the user to input the size of the matrix A (n x n)
    printf("We're computing the inverse of matrix A having size nxn.\n");
    do{
        printf("Enter a positive number for n: ");
        n=scan_entry();
        if(n==0){
            printf("Wrong input!\n");
        }
    } while(n==0);

    // Saving the size n to the output file
    fprintf(file ,"Matrix size of %dx%d\n", n, n);

    // Initializing the input matrix A
    // and the ouput matrix: invA1 - inverse matrix computed using LU decomposition
    //                       invA2 - inverse matrix computed using Strassen Algorithm with Strassen Multiplication
    //                       invA3 - inverse matrix computed using Strassen Algorithm with Naive Multiplication
    double **A,**invA1, **invA2, **invA3;
    A = (double**)malloc(n* sizeof(double*));
    invA1 = (double**)malloc(n* sizeof(double*));
    invA2 = (double**)malloc(n* sizeof(double*));
    invA3 = (double**)malloc(n* sizeof(double*));
    for(int i=0; i<n;i++){
        A[i] = (double*)malloc(n*sizeof(double));
        invA1[i] = (double*)malloc(n*sizeof(double));
        invA2[i] = (double*)malloc(n*sizeof(double));
        invA3[i] = (double*)malloc(n*sizeof(double));
    }

    // Assigning random values to input matrix A
    random_matrix(n,n,A);

    // printing matrix A
    printf("A = \n");
    printMatrix(n,n,A);

    clock_t start_time1, end_time1;
    double time_taken1;

    // Recording the start time
    start_time1 = clock();

    // Calling our inverse LU function
    inverseMatrix_LU(n,A,invA1);

    // Recording the end time
    end_time1 = clock();

    // Calculating the time taken using inverse LU in seconds
    time_taken1 = ((double)(end_time1 - start_time1)) / CLOCKS_PER_SEC;   

    // printing the ouput matrix A-1
    printf("A-1 using LU = \n");
    printMatrix(n,n,invA1);

    clock_t start_time2, end_time2;
    double time_taken2;

    // Recording the start time
    start_time2 = clock();

    // Calling our Strassen Inversion with Strassen Multiplication function
    inverseMatrix_Strassen_Strassen(n,A,invA2);

    // Recording the end time
    end_time2 = clock();

    // Calculating the time taken using Strassen Inversion with Strassen Multiplication in seconds
    time_taken2 = ((double)(end_time2 - start_time2)) / CLOCKS_PER_SEC;    
    // printing the output matrix A-1
    printf("A-1 using Strassen with Strassen-Multiplication = \n");
    printMatrix(n,n,invA2); 

    clock_t start_time3, end_time3;
    double time_taken3;

    // Recording the start time
    start_time3 = clock();

    // Calling our Strassen Inversion with Naive Multiplication function
    inverseMatrix_Strassen_Naive(n,A,invA3);

    // Recording the end time
    end_time3 = clock();

    // Calculating the time taken using Strassen Inversion with Naive Multiplication in seconds
    time_taken3 = ((double)(end_time3 - start_time3)) / CLOCKS_PER_SEC;   

    // printing the output matrix A-1
    printf("A-1 using Strassen with Naive-Multiplication = \n");
    printMatrix(n,n,invA3);       

    // printing the computation time of Matrix Inversion using LU, Strassen with Strassen Multiplication and Strassen with Naive Multiplication
    printf("Time to compute inversion using LU is %f seconds\n", time_taken1);
    printf("Time to compute inversion using Strassen Strassen is %f seconds\n", time_taken2);
    printf("Time to compute inversion using Strassen Naive is %f seconds\n", time_taken3);
    
    // saving the computation time results to the output log file
    fprintf(file, "Computation time LU: %.10f seconds \n", time_taken1);
    fprintf(file, "Computation time Strassen Strassen: %.10f seconds \n", time_taken2);
    fprintf(file, "Computation time Strassen Naive: %.10f seconds \n\n", time_taken3);
    fclose(file);
    
    // freeing the memory
    for(int i=0; i<n;i++){
        free(A[i]);
        free(invA1[i]);
        free(invA2[i]);
        free(invA3[i]);
    }
    free(A); free(invA1); free(invA2); free(invA3);
}

int main() {
    int menu_option; // contains the menu options that the user will choose from
    printf("\n");
    printf("        MODEL PROJECT PROGRAM!!!\n");
    printf("------------------------------------------\n\n");
    do {
        menu(); // printing the menu
        do{
            // Asking the user to enter an option from 1-8
            printf("\nPlease enter an option from the main menu: ");
            menu_option=scan_entry();
            // checking if the user has entered a number from 1 to 8
            if(menu_option<=0 || menu_option>8){
                printf("Wrong input!\n");
            }
        } while(menu_option<=0 || menu_option>8); // We keep asking the user to enter the option again if the input is invalid (not 1-8)

        switch (menu_option)
        {
        // Option 1: Calling function to compute Matrix Multiplication using Naive method
        case 1:
            Naive_Multiplication();
            break;
        // Option 2: Calling function to compute Matrix Multiplication using Strassen Algorithm
        case 2:
            Strassen_Multiplication();
            break;
        // Option 3: Calling function to compute LU Decomposition of a matrix
        case 3:
            LU_Decomposition();
            break;
        // Option 4: Calling function to compute Matrix Inversion using LU Decomposition
        case 4:
            Inverse_LU();
            break;
        // Option 5: Calling function to compute Matrix Inversion using Strassen Algorithm
        case 5:
            Inverse_Strassen();
            break;
        // Option 6: Calling function to compare the 2 methods for Matrix Multiplication (Strassen and Naive)
        case 6:
            Compare_Mult();
            break;
        // Option 7: Calling function to compare the 3 methods for Matrix Inversion (LU, Strassen/Strassen, and Strassen/Naive)
        case 7:
            Compare_Inv();
            break;
        // Option 8: Exit the program
        case 8:
            break;
        default: // Wrong input
            printf("Invalid input! Please enter a number from 1 to 8\n");
            break;
        }
    } while(menu_option != 8); // loop the menu until the user chooses the option to exit the program
    return 0;
}