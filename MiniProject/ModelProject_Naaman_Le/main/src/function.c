// Nesrine Naaman & Nguyen Huong Giang LE

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "header.h"
#include <ctype.h> 

//printed a dynamic allocation matrix of size mxn
void printMatrix(int m, int n, double **H){
    // looping through each element of the matrix
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            printf("%.10f\t", H[i][j]); // print the element with 10 numbers after the decimal point
        }   
        printf("\n");
    }
    printf("\n");
    return;
}

// Padding a dynamic allocation matrix of size m x n to size max x max
// Storing the new matrix of size max x max to A_pad
void zeroPadding(int m, int n, int max, double **A, double **A_pad){
    // looping through each element of A_pad
    for(int i =0; i<max;i++){
        for(int j = 0; j<max;j++){
            A_pad[i][j] = 0; // initializing the element value = 0 (zero padding)
            // we have a zero padding on the top and left of the matrix
            if(i>=max-m & j >= max-n){
                A_pad[i][j] = A[i-max+m][j-max+n]; // copying the elements from A to A_pad to the right and bottom
            }
        }
    }
}

// Assigning the random matrix A of size m x n with value of floating-point number in double precision in range [-1;1]
void random_matrix(int m, int n, double **A){
    srand(time(NULL));

    // looping through each element of A
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++){
            // creating a random number from [-1,1]
            double r = ((double)rand() / RAND_MAX) * 2.0f - 1.0f;
            // storing this number to the element of A
            A[i][j] = r;
        }
    }
}

// Checking if the user input value is a positive integer 
// returning 0 if it's not a positive integer
// returning the number input by the user itself if it's a positive integer
int scan_entry(){
    char str[10];
    scanf("%s",str); // getting the user input as a string

    // checking through each char of the string
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) { // if the character is not a digit => either a string or a negative sign => not a positive integer
            return 0; // Non-digit character found
        }
    }
    int n = strtol(str, NULL, 10); // if it's a positive integer => we change the string to a number
    // returning this number
    return n;
} 