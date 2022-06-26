#include <cs50.h>
#include <stdio.h>

// Function that given a number returns its length. O(N)
int len(long num);

// function that given a number returns is x first digits O(N)
int firsts_digits(long num, int qty);

// Checks the Banck name of a credit card valid number
void CreditCard(long CreditCardNum);

// Checks if a credit card number is (syntactically) valid
bool LuhnsAlgorithm(long CreditCardNum);

int main(void)
{

    long CreditCardNum = get_long("Credit Card Number: ");

    if (LuhnsAlgorithm(CreditCardNum))
    {
        CreditCard(CreditCardNum);
    }
    else
    {
        printf("INVALID\n");
    }
}

// Function that given a number returns its length. O(N)
int len(long num)
{
    int digits = 0;

    while (num != 0)
    {
        num = num / 10;
        digits += 1;
    }

    return digits;
}

// function that given a number returns is x first digits O(N)
int firsts_digits(long num, int qty)
{
    while (len(num) > qty)
    {
        num = num / 10;
    }

    return num;
}

// Checks the Banck name of a credit card valid number
void CreditCard(long CreditCardNum)
{
    int length = len(CreditCardNum);

    if (length > 12 && length < 17)
    {

        int digits = firsts_digits(CreditCardNum, 2); // Temporal Efficiency > Spacial

        if (firsts_digits(CreditCardNum, 1) == 4)  //  Visa 13 to 16 digits starts with 4
        {
            printf("VISA\n");
            return;
        }
        else if (length == 16 && 50 < digits && digits < 56)  //  Master Card 16 digits and starts with 51, 52, 53, 54, or 55
        {
            printf("MASTERCARD\n");
        }
        else if ((length == 15 && digits == 34) || (length == 15 && digits == 37)) //  American Express 15 digits and starts with 34 or 37
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

// Checks if a credit card number is (syntactically) valid
bool LuhnsAlgorithm(long CreditCardNum)
{
    int checksum = 0;
    int flag = 1;
    int buffer = 0;

    while (CreditCardNum != 0)
    {

        if (flag == 1)
        {
            checksum += (CreditCardNum % 10);
            flag = 0;
        }
        else
        {
            buffer = (CreditCardNum % 10) * 2;
            if (len(buffer) == 2)
            {
                checksum += (buffer % 10);
                buffer = buffer / 10;
                checksum += buffer;
            }
            else
            {
                checksum += buffer;
            }
            flag = 1;
        }
        CreditCardNum = CreditCardNum / 10;
    }

    if ((checksum % 10) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}