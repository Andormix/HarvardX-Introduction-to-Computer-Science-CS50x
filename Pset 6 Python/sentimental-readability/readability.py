# program that first asks the user to type in some text, and then outputs the grade level for the text,
# according to the Coleman-Liau formula.

# First we need to get user input.
while(True):

    text = input("Text: ")

    # Check text is not empty
    if len(text) != 0:
        break

# For Coleman-Liau we need to declare some variables. (For clarity)
letters = 0
words = 1
sentences = 0
L = 0
S = 0

# Then we need to iterate every char in the text

for c in text:
    if c.isalpha():
        letters += 1
    elif c == ' ':
        words += 1
    elif c == ".":
        sentences += 1
    elif c == "!":
        sentences += 1
    elif c == "?":
        sentences += 1

# print(letters)
# print(words)
# print(sentences)

# We proceed to calculate:
L = (letters * 100) / words
S = (sentences * 100) / words

# Then we cant compute Coleman-Liau index
index = round(0.0588 * L - 0.296 * S - 15.8)
print(index)

# Once we have the index we need to print the grade of readability
if index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print("Grade", index)
