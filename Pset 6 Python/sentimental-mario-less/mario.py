# Program that prints out a half-pyramid of a specified height.

# Get number from user
def main():
    while(True):

        try:
            height = int(input("Height: "))

            # Check number is a positive number
            if height > 0 and height < 9:
                break
            else:
                print("This is not a valid number, try again")
        except:
            print("This is not a valid number, try again")

    # Once we got user integer print the left half of the pyramid.

    print_left_half_pyramid_rec(height, height)


def print_left_half_pyramid_rec(level, height):

    # RECURSIVE CASE
    if level != 0:

        print_left_half_pyramid_rec(level - 1, height)
        print(" " * (height - level), end='')
        print("#" * level)


main()
