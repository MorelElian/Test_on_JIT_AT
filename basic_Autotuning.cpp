//#include <iostream>
#include <cstdio>
#include <cstdlib>
template <__autotune__ int** y>
[[clang::jit]] int run_c(){
    
    int *a;
    int c = 0;
    int d = 4;
    for(int i = 0;i < *y;i ++)
    {
        c = i +c +4;
        d = c*2 -5;
    }
    
    
    return *y;
}
int main(int argc, char *argv[])
{
    int z[3];
    int y = std::atoi(argv[1]);
    z[0] = 100;
    z[1] = 1000000000;
    z[2] = y;
    for(int i = 0 ; i <10; i++)
    {
        long long t1 = __rdtsc();
        int result = run_c<&z>();
        long long t2 = __rdtsc();
        //printf("ttttt");
        FILE* fichier = fopen("data/trace_basic_autotuning.csv", "a");
        fprintf(fichier, "%d;%d;%lld\n",i,result,t2-t1);
        fclose(fichier);
        
    }
    ;
}