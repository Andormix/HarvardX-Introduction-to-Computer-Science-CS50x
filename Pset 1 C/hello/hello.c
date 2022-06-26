// Libs
#include <stdio.h>
#include <cs50.h>

// Program that request user name and welcomes the user.
int main(void)
{
    string Name = get_string("Whats your name?\n-  ");

    printf("Hello %s!\n", Name);

}