# Program that calculates the minimum number of coins required to give a user change.

coins = 0

# Get number from user
while(True):

    try:
        num = float(input("Change owed: "))

        # Check if num is negative
        if num >= 0:

            # If the number is correct I will transform it to an int due to
            # floating point imprecision bugs.
            num = (int)(num * 100)
            break
    except:

        # Keep asking for input
        pass

# Quarters
while(num >= 25):

    num -= 25
    coins += 1


# Dimes
while(num >= 10):

    num -= 10
    coins += 1


# Nickels
while(num >= 5):

    num -= 5
    coins += 1


# Pennies
while(num >= 1):

    num -= 1
    coins += 1


print(coins)
