#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

string cipher(string plaintext, string key);

int main(int argc, string argv[])
{
    if (argc != 2)  // Checks command line arg number
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else  // Chencks if input from command line arg is a alpha
    {
        int x = 0;
        string str = argv[1];
        while (str[x] != '\0')
        {
            if (isdigit(str[x]))
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
            x++;

            for (int i = x + 1; i < 26; i++) // Is is not a digit check for duplicates
            {
                if (str[x] == str[i])
                {
                    printf("Usage: ./caesar key\n");
                    return 1;
                }
            }
        }

        if (x != 26)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
    }

    string plaintext = get_string("Plaintext: ");
    string ciphertext = cipher(plaintext, argv[1]);
    printf("ciphertext: %s\n", ciphertext);

}

string cipher(string plaintext, string key)
{
    int x = 0;
    char letter = ' ';
    int index = 0;

    while (plaintext[x] != '\0') // Iterates every character of a string
    {
        if isalpha(plaintext[x]) // If the character is a letter
        {
            // Gets the index of the letter (1 to 26
            index = ((tolower(plaintext[x]) - 96)) - 1;

            if (isupper(plaintext[x]))
            {
                plaintext[x] = toupper(key[index]);  // Its upper
            }
            else
            {
                plaintext[x] = tolower(key[index]);  // Its lower
            }
        }
        x++;
    }
    return plaintext;
}