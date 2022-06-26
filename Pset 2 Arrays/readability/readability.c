#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

// Returns readability index based on Coleman-Liau index
int Coleman_Liau_index(string txt);

int main(void)
{
    string text;

    text = get_string("Text: ");

    int grade = Coleman_Liau_index(text); // Returns readability index based on Coleman-Liau index
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }

}

/*  index = 0.0588 * L - 0.296 * S - 15.8
 *  where L is the average number of letters per 100 words in the text,
 *  and S is the average number of sentences per 100 words in the text.
 */
int Coleman_Liau_index(string text)
{

    int i = 0;
    int words = 1;
    int letters = 0;
    int sentences = 0;

    // Iterates all the text character by character
    while (text[i] != '\0')
    {
        switch (text[i])
        {
            case ' ':
                words++;
                break;
            case '.':
                sentences++;
                break;
            case '!':
                sentences++;
                break;
            case '?':
                sentences++;
                break;
            case ',':
                break;
            case '-':
                break;
            case ';':
                break;
            case '\'':
                break;
            default:
                letters++;
                break;
        }
        i++;
    }

    float L = (100 * letters) / (float) words;
    float S = (100 * sentences) / (float) words;

    //printf("Letters: %i\n", letters);
    //printf("Words: %i\n", words);
    //printf("Sentences: %i\n", sentences);
    // printf("L: %f\n", L);
    // printf("S: %f\n", S);
    //printf("Grade: %f\n", (0.0588 * L - 0.296 * S - 15.8));
    return nearbyint((0.0588 * L - 0.296 * S - 15.8));


}