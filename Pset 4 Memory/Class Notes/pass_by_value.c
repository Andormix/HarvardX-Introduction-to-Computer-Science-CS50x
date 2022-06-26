#include <stdio.h>

void swap(int x, int y);

int main(void)
{
    int x = 1;
    int y = 2;

    printf("Before swap: %i\n", x);
    printf("Before swap: %i\n", y);

    swap(x,y);

    printf("After swap: %i\n", x);
    printf("After swap: %i\n", y);
}

void swap(int x, int y)
{
    int aux = x;
    x = y;
    y = aux;
}