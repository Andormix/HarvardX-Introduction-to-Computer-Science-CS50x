#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

//  Size in bytes of a FAT block.
int const FAT_SIZE = 512;

// FAT file system whose “block size” is 512 bytes (ADT FAT)
typedef struct
{
    uint8_t MEMO[512];
}
FAT;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // First we need to open the file wich has the photos we need to recover.
    FILE *input_ptr = fopen(argv[1], "r");
    if (input_ptr == NULL)
    {
        printf("Could not open.\n");
        return 1;
    }

    // We need to create a buffer to stere 1 block.
    FAT buffer;

    // Counter (Image title)
    int recount = 0;
    char str[8]; // 3 + '\0'
    int first = 1;

    // IMPORTANT WE NEED TO INITIALIZE TO NULL THE POINTER BEFORE! If not we can't do the logic behind this pset.
    FILE *output_ptr = NULL;

    // Then we need to iterate the file Read 1 block(512 bytes) at a time until fread returns 0
    while (fread(&buffer, FAT_SIZE, 1, input_ptr))
    {
        // We need to check if the block is the start of a JPEG // fread doc: This function returns the number of items read, which equals the number of bytes read when size is 1.
        if (buffer.MEMO[0] == 0xff && buffer.MEMO[1] == 0xd8 && buffer.MEMO[2] == 0xff && (buffer.MEMO[3] / 16 == 0xe))
        {
            // If its the first time we open for writing we only open for writing and then write
            if (output_ptr == NULL)
            {
                snprintf(str, 8, "%.3d.jpg", recount);
                printf("%s\n", str);
                recount++;

                output_ptr = fopen(str, "w");
                if (output_ptr == NULL)
                {
                    printf("Could not create.\n");
                    return 2;
                }

                fwrite(&buffer, FAT_SIZE, 1, output_ptr);
            }
            else
            {
                // If it is not the first time we open for writing we need to close the last file first!
                fclose(output_ptr);

                snprintf(str, 8, "%.3d.jpg", recount);
                printf("%s\n", str);
                recount++;

                output_ptr = fopen(str, "w");
                if (output_ptr == NULL)
                {
                    printf("Could not create.\n");
                    return 2;
                }

                fwrite(&buffer, FAT_SIZE, 1, output_ptr);
            }

        }
        else
        {
            // If we have already opened a file we need to keep writing BLOCKS to the current open file
            if (output_ptr != NULL)
            {
                fwrite(&buffer, FAT_SIZE, 1, output_ptr);
            }
        }
    }

    printf("\n");
    // we need to close the file wich has the photos we needed to recover.
    fclose(output_ptr);
    fclose(input_ptr);
}