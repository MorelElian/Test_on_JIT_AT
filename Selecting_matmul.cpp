#include <cstdio>
#include <cstdlib>
// Fonction pour effectuer la multiplication matricielle (ordre ijk)
void matmul1(int** A, int** B, int** C, int N) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < N; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
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
[[clang::jit]]int launch_matmul(void (*funcArray[])(int**, int**, int**, int),int ** A, int ** B, int **C,int N)       
{
    funcArray[*id_param](A,B,C,N);
    return *id_param ;

}

int main(int argc,char * argv[]) {
     // Taille des matrices (N x N)

    // Allocation et initialisation des matrices A, B et C
    

    // Appel de matmul1, matmul2 et matmul3 pour effectuer la multiplication
    
    void (*matmulFunctions[3])(int**, int**, int**, int) = {matmul1, matmul2, matmul3};
    int tab[3] = {0,1,2};
    int N = std::atoi(argv[1]);
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
    for(int i = 0; i < 10; i++)
    {
        
        long long t1 = __rdtsc();
        int result = launch_matmul<&tab>(matmulFunctions,A,B,C,N);
        long long t2 = __rdtsc();
        FILE* fichier = fopen("../data/trace_selecting_matmul.csv", "a");
        fprintf(fichier, "%d;%d;%d;%lld\n",N,i,result,t2-t1);
        fclose(fichier);
    }
    
    return 0;
}
