//#include <iostream>
#include <cstdio>
#include <cstdlib>
template <int x,__autotune__ int** y>
[[clang::jit]] int run_c(){
    int *a;
    int c = 0;
    int d = 4;
    for(int i = 0;i < *y;i ++)
    {
        c = i +c +4;
        d = c*2 -5;
    }
    printf("fin boucle\n");
    return d;
}
int main(int argc, char *argv[])
{
    int z[3];
    int q[2];
    int a = std::atoi(argv[1]);
    int y = std::atoi(argv[2]);
    //std::cout << "a and y initialized \n";
    
    z[0] = y;
    z[1] = 100000000;
    z[2] = 1000000;
    q[0] = y+1;
    q[1] = 3;
    int * c;
    c = (int *) malloc(sizeof(int));
    *c = 1200;
    int d = a;
    
    int test = run_c<z[0],&z>();
    long long time2 = __rdtsc();
    int test2 = run_c<z[0],&z>();
    long long time3 = __rdtsc();
    int test3 = run_c<z[0],&z>();
    run_c<z[0],&z>();
    run_c<z[0],&z>();
    run_c<z[0],&z>();
    printf("pas de galère\n");
}