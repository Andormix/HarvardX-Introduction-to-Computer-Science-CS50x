#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

// Encrypt messages using Caesar’s cipher.
string cipher(string plaintext, int key);

int main(int argc, string argv[])
{
    // Checks command line arg number
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Chencks if input from command line arg is a alpha
    int x = 0;
    string str = argv[1];
    while (str[x] != '\0')
    {
        if (!isdigit(str[x]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
        x++;
    }

    string plaintext = get_string("Plaintext: ");
    string ciphertext = cipher(plaintext, atoi(argv[1]));
    printf("ciphertext: %s\n", ciphertext);

}

// Encrypt messages using Caesar’s cipher.
string cipher(string plaintext, int key)
{
    int x = 0;
    char letter = ' ';
    int index = 0;

    while (plaintext[x] != '\0') // Iterates every character of a string
    {
        if isalpha(plaintext[x]) // If the character is a letter
        {
            // Gets the index of the letter (1 to 26
            index = (tolower(plaintext[x]) - 96 + key) % 26;

            if (isupper(plaintext[x]))
            {
                plaintext[x] = 64 + index;  // Its upper
            }
            else
            {
                plaintext[x] = 96 + index;  // Its lowe
            }
        }
        x++;
    }
    return plaintext;
}