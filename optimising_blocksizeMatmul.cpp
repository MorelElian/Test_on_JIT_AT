#include <cstdio>
#include <cstdlib>
#include <algorithm>
//#include <random>
template<typename T>
T myMin(T a, T b) {
    return (a < b) ? a : b;
}
template <__autotune__ int** taille_block>
[[clang::jit]]void multiplyMatrixByBlocks(int** A, int** B, int** C, int n) {
   
    for (int i = 0; i < n; i += *taille_block) {
        for (int j = 0; j < n; j += *taille_block) {
            for (int k = 0; k < n; k += *taille_block) {
                for (int ii = i; ii < myMin(i + *taille_block, n); ++ii) {
                    for (int jj = j; jj < myMin(j + *taille_block, n); ++jj) {
                        for (int kk = k; kk < myMin(k + *taille_block, n); ++kk) {
                            C[ii][jj] += A[ii][kk] * B[kk][jj];
                        }
                    }
                }
            }
        }
    }
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
int main()
{
    int N = 1024;
    int** A = generateMat(N);
    int** B = generateMat(N);
    int** C = initialiseMat(N);

    int taille_block[9] = {2,4,8,16,32,64,128,256,512};
    for(int i = 0; i<50; i++)
    {
        multiplyMatrixByBlocks<&taille_block>(A,B,C,N);
    }
    
    
}
