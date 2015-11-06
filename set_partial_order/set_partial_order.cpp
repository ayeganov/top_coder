#include <cstdio>

template <typename T, std::size_t N_X, std::size_t N_Y>
const char* compare(T (&x)[N_X], T (&y)[N_Y]) noexcept
{
    int map[100] = {0};
    if(N_X == N_Y)
    {
        for(int v : y) { map[v] = 1; }
        for(int v : x) { ++map[v]; }
        for(int v : map) if (v == 1) return "Incomparable";
        return "Equal";
    }
    if(N_X > N_Y)
    {
        for(int v : x) { map[v] = 1; }
        for(int v : y) { if(map[v] != 1) return "Incomparable"; }
        return "Greater";
    }
    else
    {
        for(int v : y) { map[v] = 1; }
        for(int v : x) { if(map[v] != 1) return "Incomparable"; }
        return "Less";
    }
}

int main(int argc, char* argv[])
{
    int x[] = {1,2,3,5,8};
    int y[] = {3,2,1,5,8};
    printf("%s\n", compare(x, y));

    int a[] = {2,3,5,7};
    int b[] = {1,2,3,4,5,6,7,8,9,10};
    printf("%s\n", compare(a, b));

    int c[] = {2,4,6,8,10,12,14,16};
    int d[] = {2,4,8,16};
    printf("%s\n", compare(c, d));

    int e[] = {42,23,17};
    int f[] = {15,23,31};
    printf("%s\n", compare(e, f));
    return 0;
}
