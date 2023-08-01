#include <cstdio>
template <__autotune__ int **  a>
[[clang::jit]]void run()
{
    printf("oooo\n");
    int c;
    c = *a;
}
int main()
{
    int z[1];
    z[0]  = 2;
    run<&z>();
}