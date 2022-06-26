#include <cs50.h>
#include <stdio.h>

// Recursive function that prints the left half of a pyramid
void RECURSIVE_LEFT_PYRAMID(int blocks, int size)
{
    // BASE CASE Blocks = 0
    // RECURSIVE CASE
    if (blocks > 0) // We can change it to iterative and skip go to base case.
    {
        RECURSIVE_LEFT_PYRAMID(blocks - 1, size);

        for (int i = 0; i < size - blocks; i++) // Left spaces
        {
            printf(" ");
        }

        for (int i = 0; i < blocks ; i++) // Left bricks
        {
            printf("#");
        }

        printf("  "); // Central spcae

        for (int i = 0; i < blocks ; i++) // Right bricks
        {
            printf("#");
        }

        printf("\n");
    }
}

int main(void)
{
    int height = -1;

    // Request pyramid height. Chacks limit cases.
    do
    {
        printf("\n");
        height = get_int("Height: ");
        printf("\n");
    }
    while (height > 8 || height <= 0);

    // Prints left side of the pyramid
    RECURSIVE_LEFT_PYRAMID(height, height); // First recursive call
}