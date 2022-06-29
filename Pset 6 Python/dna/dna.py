import csv
import sys


def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        return

    # Read database file into a variable
    persons = []

    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        for person in reader:
            persons.append(person)

    # Read DNA sequence file into a variable
    sequence = ''
    with open(sys.argv[2]) as file:
        for c in file:
            sequence = sequence + c

    # Find longest match of each STR in DNA sequence

    # First i will create a dictionary
    STRs = {}

    # Ope the file
    with open(sys.argv[1]) as file:

        # Get the first row
        first_row = next(file)

        # Split it into a list (pythonic way)
        first_row = [x.strip('\n') for x in first_row.split(",")]

        # From second to last add tinto a dict the sequences paired with 0
        for camp in first_row[1:]:
            STRs[camp] = 0

    # Then for each sequence of nucleotide
    for subsequence in STRs:
        STRs[subsequence] = longest_match(sequence, subsequence)

    number_subsequences = len(STRs)
    # Check database for matching profiles
    for person in persons:
        recount = 0

        # Check all subsequences from every person in the database
        for subsequence in STRs:
            if int(person[subsequence]) == STRs[subsequence]:
                recount += 1

        # If match print person
        if number_subsequences == recount:
            print(person["name"])
            return

    print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
