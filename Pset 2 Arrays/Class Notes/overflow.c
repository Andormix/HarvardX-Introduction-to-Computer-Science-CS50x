#include <stdio.h>
#include <cs50.h>

int main()
{
    int x = 1;
    while(x != 0)
    {
        printf("%i\n", x);
        x = (x * 2);
    }
}