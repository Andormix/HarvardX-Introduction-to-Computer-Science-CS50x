# We can also send return values like in C with exit
from sys import argv, exit

if len(argv) == 2:
    print("Wellcome!")
    exit(0)
else:
    print("Bye!")
    exit(1)

# We can also sys.exit() to avoid colisions.
# echo$?
 