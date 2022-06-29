#########################################################################################################
#                                                                                                       #
# Program that determines whether a provided credit card number is valid according to Luhn’s algorithm  #
# and prints into console the card provider                                                             #
#                                                                                                       #
#########################################################################################################

# Checks credit card bank provider
def Bank(Card, length):

    if 12 < length < 17 and str(Card)[:1] == '4':
        print("VISA")
        return

    first_two = int(str(Card)[:2])

    if length == 15 and (first_two == 34 or first_two == 37):
        print("AMEX")
        return

    if length == 16 and (50 < first_two < 56):
        print("MASTERCARD")


# Algorithm invented by Hans Peter Luhn of IBM.
def Luhns_Algorithm(Card, lenght):

    # Controls odd and even numbers
    flag = 0

    # Stores formula number
    sum = 0

    while (lenght > 0):

        if flag == 0:
            # Sum to the sum of the digits that weren’t multiplied by 2
            sum += int(Card % 10)
            Card = Card / 10
            flag = 1
        else:
            # Multiply every other digit by 2, starting with the number’s second-to-last digit
            product = int(Card % 10) * 2

            # Now let’s add those products’ digits (i.e., not the products themselves)
            if product > 9:
                sum += int(product % 10) + int(product / 10)

            else:
                sum += product

            Card = Card / 10
            flag = 0

        lenght -= 1

    return sum


def main():

    lenght = 0

    # Get number from user
    while(True):

        try:

            Card = int(input("Credit Card Number: "))

            # Check card length
            lenght = len(str(Card))

            if 12 < lenght < 17:
                break
            else:
                print("INVALID")
                return
        except:

            # Keep asking for input
            pass

    if (Luhns_Algorithm(Card, lenght) % 2 == 0):

        Bank(Card, lenght)

    else:

        print("INVALID")


main()
