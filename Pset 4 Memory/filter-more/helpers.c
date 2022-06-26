#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int sum = 0;
    float avg = 0;

    for (int i = 0; i < height; i++) // Loop the bitmap
    {
        for (int j = 0; j < width; j++)
        {
            // We need to reset sum
            sum = 0;

            // Get the summ of the RGB values of that pixel
            sum += image[i][j].rgbtRed;
            sum += image[i][j].rgbtGreen;
            sum += image[i][j].rgbtBlue;

            // Get the average
            avg = round(sum / 3.0);

            // Prints
            if (avg > 255)
            {
                printf("s: %i\n ", sum);
                printf("a: %f\n ", avg);
                printf("r: %i\n ", image[i][j].rgbtRed);
                printf("g: %i\n ", image[i][j].rgbtGreen);
                printf("b: %i\n\n\n ", image[i][j].rgbtBlue);
            }

            // Set the average to those RGB values of that pixel
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepiaRed;
    int sepiaGreen;
    int sepiaBlue;
    RGBTRIPLE pixel;

    for (int i = 0; i < height; i++) // Loop the bitmap
    {
        for (int j = 0; j < width; j++)
        {
            // We need to compute all values before change the current pixel or make a new variable called "pixel" and use it.
            sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen  + .189 * image[i][j].rgbtBlue);
            sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen  + .168 * image[i][j].rgbtBlue);
            sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen  + .131 * image[i][j].rgbtBlue);

            // Set red pixel
            if (sepiaRed > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else if (sepiaRed < 0)
            {
                image[i][j].rgbtRed = 0;
            }
            else
            {
                image[i][j].rgbtRed = sepiaRed;
            }

            // Set green pixel
            if (sepiaGreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else if (sepiaGreen < 0)
            {
                image[i][j].rgbtGreen = 0;
            }
            else
            {
                image[i][j].rgbtGreen = sepiaGreen;
            }

            // set blue pixel
            if (sepiaBlue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else if (sepiaBlue < 0)
            {
                image[i][j].rgbtBlue = 0;
            }
            else
            {
                image[i][j].rgbtBlue = sepiaBlue;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int midpoint = floor(width / 2.0); // If its odd we don't need to change central column.
    RGBTRIPLE buffer;

    for (int i = 0; i < height; i++) // Loop the bitmap
    {
        for (int j = 0; j < midpoint; j++)
        {
            // Like the swap de did in class with 2 wine glasses filled with water of different colors with an additional one
            buffer = image[i][width - j - 1];
            image[i][width - j - 1] = image[i][j];
            image[i][j] = buffer;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // First we need to make a copy. If we update pixels on the image directly it will afect the global output.
    RGBTRIPLE image_copy[height][width];
    for (int i = 0; i < height; i++) // Loop the bitmap
    {
        for (int j = 0; j < width; j++)
        {
            image_copy[i][j] = image[i][j];
        }
    }

    // RGB values we need to compute
    float sumRed;
    float sumGreen;
    float sumBlue;

    // Borders of our 3x3 box
    int UpperRow;
    int LowerRow;
    int UpperCol;
    int LowerCol;

    // Valid pixels in our 3x3 box
    int pixelCount;

    for (int i = 0; i < height; i++) // Loop the bitmap
    {
        for (int j = 0; j < width; j++)
        {
            // Reset variables
            sumRed = 0;
            sumGreen = 0;
            sumBlue = 0;
            pixelCount = 0;

            // Before create our box we need to check de borders
            UpperRow = i - 1;
            if (UpperRow < 0)
            {
                UpperRow = i;
            }
            LowerRow = i + 1;
            if (LowerRow > height - 1)
            {
                LowerRow = i;
            }
            UpperCol = j + 1;
            if (UpperCol > width - 1)
            {
                UpperCol = j;
            }
            LowerCol = j - 1;
            if (LowerCol < 0)
            {
                LowerCol = j;
            }

            // Then we do the magic eg. sum all nearby pixels
            for (int k = UpperRow; k <= LowerRow; k++) // Maybe 4 for loops its not the best way to do it but Im lazy to think right know.
            {
                for (int l = LowerCol; l <= UpperCol; l++)
                {
                    pixelCount++;
                    sumRed += image_copy[k][l].rgbtRed;
                    sumGreen += image_copy[k][l].rgbtGreen;
                    sumBlue += image_copy[k][l].rgbtBlue;
                }
            }

            // finally we need to asign those values to the actual pixel eg. central.
            image[i][j].rgbtRed = round(sumRed / pixelCount);
            image[i][j].rgbtGreen = round(sumGreen / pixelCount);
            image[i][j].rgbtBlue = round(sumBlue / pixelCount);
            // To pass check50 we need to round floats I think... Values are very near 177 vs 176
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // We need to create Gx & Gy
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // First we need to make a copy. If we update pixels on the image directly it will afect the global output.
    RGBTRIPLE image_copy[height][width];
    for (int i = 0; i < height; i++) // Loop the bitmap
    {
        for (int j = 0; j < width; j++)
        {
            image_copy[i][j] = image[i][j];
        }
    }

    // RGB values we need to compute
    float sumRedGx;
    float sumRedGy;
    float sumGreenGx;
    float sumGreenGy;
    float sumBlueGx;
    float sumBlueGy;

    // Borders of our 3x3 box
    int UpperRow;
    int LowerRow;
    int UpperCol;
    int LowerCol;

    // Cord for Gx and Gy matrix
    int cord_x;
    int x;
    int cord_y;
    int y;

    // Store Sober value
    int value;

    for (int i = 0; i < height; i++) // Loop the bitmap
    {
        for (int j = 0; j < width; j++)
        {
            // Reset variables
            sumRedGx = 0;
            sumRedGy = 0;
            sumGreenGx = 0;
            sumGreenGy = 0;
            sumBlueGx = 0;
            sumBlueGy = 0;
            cord_x = 0;
            x = 0;
            cord_y = 0;
            y = 0;

            // Before create our box we need to check borders
            UpperRow = i - 1;
            if (UpperRow < 0)
            {
                UpperRow = i;
                cord_y = 1;
            }
            LowerRow = i + 1;
            if (LowerRow > height - 1)
            {
                LowerRow = i;
            }
            UpperCol = j + 1;
            if (UpperCol > width - 1)
            {
                UpperCol = j;
            }
            LowerCol = j - 1;
            if (LowerCol < 0)
            {
                LowerCol = j;
                cord_x = 1;
            }

            y = cord_y;

            // Then we do the magic eg. sum all nearby pixels
            for (int k = UpperRow; k <= LowerRow; k++) // Maybe 4 for loops its not the best way to do it but Im lazy to think right know.
            {
                x = cord_x;

                for (int l = LowerCol; l <= UpperCol; l++)
                {
                    sumRedGx += image_copy[k][l].rgbtRed  * Gx[y][x];
                    sumRedGy += image_copy[k][l].rgbtRed  * Gy[y][x];
                    sumGreenGx += image_copy[k][l].rgbtGreen * Gx[y][x];
                    sumGreenGy += image_copy[k][l].rgbtGreen * Gy[y][x];
                    sumBlueGx += image_copy[k][l].rgbtBlue * Gx[y][x];
                    sumBlueGy += image_copy[k][l].rgbtBlue * Gy[y][x];
                    x++;
                }

                y++;
            }

            // finally we need to asign those values to the actual pixel eg. central.
            value = round(sqrt((pow(sumRedGx, 2) + pow(sumRedGy, 2))));
            if (value > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else if (value < 0)
            {
                image[i][j].rgbtRed = 0;
            }
            else
            {
                image[i][j].rgbtRed = value;
            }

            value = round(sqrt((pow(sumGreenGx, 2) + pow(sumGreenGy, 2))));
            if (value > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else if (value < 0)
            {
                image[i][j].rgbtGreen = 0;
            }
            else
            {
                image[i][j].rgbtGreen = value;
            }

            value = round(sqrt((pow(sumBlueGx, 2) + pow(sumBlueGy, 2))));
            if (value > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else if (value < 0)
            {
                image[i][j].rgbtBlue = 0;
            }
            else
            {
                image[i][j].rgbtBlue = value;
            }
        }
    }
    return;
}
