#include <stdio.h>
#include <stdlib.h>

// This code will compile but i didn't initialize the array.
int main(void)
{
    int scores[40];

    // Will show the garbage values currently at memory
    for (int i = 0; i < 40; i++)
    {
        printf("%i\n", scores[i]); // Who knows what will be printed
    }
}