#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>


// change the size of the polynomial to a power of 2
// Example: n = 3 => change it to power of 4
int nextPowerOfTwo(int n) {
    int power = 1;
    while (power < n) power *= 2;
    return power;
}

//printed matrix
void printMatrix(int m, int *H){
    for(int i=0;i<m;i++){
            printf("%d\t", H[i]);
    }
    printf("\n");
    return;
}

// caculate polynomial multiplication H = F*G
void Karatsuba(int n, int *F,int *G, int*H){
    // f1 = (2x2 + 3x + 4)x3
    // f0 = x2 + 3x + 1
    // g1 = (x2 - x + 0)x3
    // g0 = 3x2 - 0x + 2
    // f11 = 2x2 + 3x
    // f10 = 4
    // f01 = x2 + 3x
    // f00 = 1
    // g11 = x2 - x
    // g10 = 0
    // g01 = 3x2
    // g00 = 2

    if (n == 1) {
        // Base case: Multiply single coefficients
        H[0] = F[0] * G[0];
        return;
    }

    // divide F to F0 and F1; G to G0 and G1
    int mid = n/2;
    int *F1, *F0, *G0, *G1;

    F1 = (int *)calloc(mid, sizeof(int));
    F0 = (int *)calloc(mid, sizeof(int));  
    G1 = (int *)calloc(mid, sizeof(int));
    G0 = (int *)calloc(mid, sizeof(int));

    // Split F and G into low and high parts
    memcpy(F0, F, mid * sizeof(int));
    memcpy(F1, F + mid, mid * sizeof(int));
    memcpy(G0, G, mid * sizeof(int));
    memcpy(G1, G + mid, mid * sizeof(int));  

    // compute Karatsuba
    int *Z0 = (int *)calloc(2 * mid - 1, sizeof(int));
    int *Z1 = (int *)calloc(2 * mid - 1, sizeof(int));
    int *Z2 = (int *)calloc(2 * mid - 1, sizeof(int));
    int *F0_plus_F1 = (int *)malloc(mid * sizeof(int));
    int *G0_plus_G1 = (int *)malloc(mid * sizeof(int));

    // Recursively calculate Z0 and Z2
    Karatsuba(mid, F0, G0, Z0);
    Karatsuba(mid, F1, G1, Z2);

    // Compute (F0 + F1) and (G0 + G1)
    for (int i = 0; i < mid; i++) {
        F0_plus_F1[i] = F0[i] + F1[i];
        G0_plus_G1[i] = G0[i] + G1[i];
    }

    // Recursively calculate Z1
    Karatsuba(mid, F0_plus_F1, G0_plus_G1, Z1);

    // Combine results into the final result
    for (int i = 0; i < n * 2 - 1; i++){
        H[i] = 0;
    }

    // Add Z0 to the result
    for (int i = 0; i < 2 * mid - 1; i++){
        H[i] += Z0[i];
        H[i + mid] += Z1[i] - Z0[i] - Z2[i];
        H[i + 2 * mid] += Z2[i];
    }
    // printMatrix(2*mid-1,Z0);
    // printMatrix(2*mid-1,Z1);
    // printMatrix(2*mid-1,Z2);

    // Free allocated memory
    free(F0);
    free(F1);
    free(G0);
    free(G1);
    free(Z0);
    free(Z1);
    free(Z2);
    free(F0_plus_F1);
    free(G0_plus_G1);
}

int main(){
    // f = 2x5 + 3x4 + 4x3 + x2 + 3x1 + 1
    // g = x+2
    int F[] = {1,2,3,4};
    int G[] = {4,3,2,1};
    int l = sizeof(F) / sizeof(F[0]);
    int m = sizeof(G) / sizeof(G[0]);

    // size is an power of 2
    int x = l>m? l:m;
    int size = nextPowerOfTwo(x);

    int *F_padded = (int *)calloc(size, sizeof(int));
    int *G_padded = (int *)calloc(size, sizeof(int));

    memcpy(F_padded, F, l* sizeof(int));
    for(int i=size-1;i>=l;i--){
        F_padded[i] = 0;
    }
    memcpy(G_padded, G, m* sizeof(int));
    for(int i=size-1;i>=m;i--){
        G_padded[i] = 0;
    }
    printf("F padded = \n");
    printMatrix(size, F_padded);
    printf("G padded = \n");
    printMatrix(size, G_padded);

    int n = 2*size - 1;
    int actual_n = l+m-1;
    int *H = (int *)calloc(n, sizeof(int));
    int *actual_H = (int *)calloc(actual_n, sizeof(int));
    
    Karatsuba(size,F_padded,G_padded,H);

    memcpy(actual_H, H, actual_n*sizeof(int));
    printf("H = F*G = \n");
    printMatrix(actual_n, actual_H);

    free(F_padded);
    free(G_padded);
    free(H);
    free(actual_H);
    return 0;
}
