#include <cstdio>
// Fonction pour effectuer la multiplication matricielle (ordre ijk)
void matmul1(int** A, int** B, int** C, int N) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < N; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    int d = 3, c =2;
    for(int i = 0 ; i <1000000; i++)
    {
        d = d- 4 *2 + c;
        c = d +4 +c;
    }
}

// Fonction pour effectuer la multiplication matricielle (ordre ikj)
void matmul2(int** A, int** B, int** C, int N) {
    for (int i = 0; i < N; ++i) {
        for (int k = 0; k < N; ++k) {
            for (int j = 0; j < N; ++j) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    int d = 3, c =2;
    for(int i = 0 ; i <1000000; i++)
    {
        d = d- 4 *2 + c;
        c = d +4 +c;
    }
}

// Fonction pour effectuer la multiplication matricielle (ordre jik)
void matmul3(int** A, int** B, int** C, int N) {
    for (int j = 0; j < N; ++j) {
        for (int i = 0; i < N; ++i) {
            for (int k = 0; k < N; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

template<__autotune__ int** id_param>
[[clang::jit]]void test(void (*funcArray[])(int**, int**, int**, int))       
{
   
    int N = 3;
    int** A = new int*[N];
    int** B = new int*[N];
    int** C = new int*[N];
    for (int i = 0; i < N; ++i) {
        A[i] = new int[N];
        B[i] = new int[N];
        C[i] = new int[N];
        for (int j = 0; j < N; ++j) {
            A[i][j] = i + j;
            B[i][j] = i - j;
            C[i][j] = 0;
        }
    }
    funcArray[*id_param](A,B,C,N);

}

int main() {
     // Taille des matrices (N x N)

    // Allocation et initialisation des matrices A, B et C
    

    // Appel de matmul1, matmul2 et matmul3 pour effectuer la multiplication
    
    
    void (*matmulFunctions[3])(int**, int**, int**, int) = {matmul1, matmul2, matmul3};
    int tab[3] = {0,1,2};

    for(int i = 0; i < 10; i++)
    {
        test<&tab>(matmulFunctions);
    }
    return 0;
}
