#include <stdio.h>
int do_smth(int x);

int main(void)
{
    int x = 10;
    do_smth(x);
}

int do_smth(int x)
{
    printf("%i\n", x);
    if (x > 0)
    {
        do_smth(x - 1);
        do_smth(x - 1);
    }
    return x;
}