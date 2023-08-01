//Optimizing Blocksize Matmul without AT
#include <cstdio>
#include <cstdlib>

//#include <random>
template<typename T>
T myMin(T a, T b) {
    return (a < b) ? a : b;
}

int multiplyMatrixByBlocks(int** A, int** B, int** C, int n,int taille_block) {
   // Taking care of the loop ordrer in order to minimize cache misses 
    for (int i = 0; i < n; i += taille_block) {
        for (int k = 0; k < n; k += taille_block) {
            for (int j = 0; j < n; j += taille_block) {
                for (int ii = i; ii < myMin(i + taille_block, n); ++ii) {
                    for (int kk = k; kk < myMin(k + taille_block, n); ++kk) {
                        for (int jj = j; jj < myMin(j + taille_block, n); ++jj) {
                            C[ii][jj] += A[ii][kk] * B[kk][jj];
                        }
                    }
                }
            }
        }
    }
    return taille_block;
}
int** generateMat(int N) {
    /*std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 100);*/

    int** mat = new int*[N];

    for (int i = 0; i < N; ++i) {
        mat[i] = new int[N];
        for (int j = 0; j < N; ++j) {
            mat[i][j] = i+j;
        }
    }

    return mat;
}
int** initialiseMat(int N) {
    int** mat = new int*[N];

    for (int i = 0; i < N; ++i) {
        mat[i] = new int[N];
        for (int j = 0; j < N; ++j) {
            mat[i][j] = 0;
        }
    }

    return mat;
}
int main(int argc, char * argv[])
{
    int N = std::atoi(argv[1]);
    int** A = generateMat(N);
    int** B = generateMat(N);
    int** C = initialiseMat(N);
    printf("%d \n",N);
    int taille_block[9] = {2,4,8,16,32,64,128,256,512};
    for (int j = 0; j <9; j++)
    {
        for(int i = 0; i<10; i++)
        {
            long long t1 = __rdtsc();
            multiplyMatrixByBlocks(A,B,C,N,j);
            long long t2 = __rdtsc();
            FILE* fichier = fopen("trace_blocksizeMatmul_withoutAT.csv", "a");
            fprintf(fichier, "%d;%d;%d;%lld;%d\n",i,j,t2-t1,N);
            fclose(fichier);    
        }
    }
    
}
