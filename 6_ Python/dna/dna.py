import csv
import sys
import argparse
from pathlib import Path


def main():

    # TODO: Check for command-line usage
    parser = argparse.ArgumentParser(description="Does something")
    parser.add_argument("csv", help="database file (csv)")
    parser.add_argument("dna", help="sequence file (txt)")
    args = parser.parse_args()

    # TODO: Read database file into a variable
    with open(args.csv) as f:
        reader = csv.DictReader(f)
        sequences = reader.fieldnames[1:]
        database = [x for x in reader]
    # TODO: Read DNA sequence file into a variable
    dna = Path(args.dna).read_text()

    # TODO: Find longest match of each STR in DNA sequence
    l_matches = {sub: longest_match(dna, sub) for sub in sequences}
    # TODO: Check database for matching profiles
    people_matches = []
    for person in database:
        for sub in sequences:
            if int(person[sub]) != l_matches[sub]:
                break
        else:
            people_matches.append(person["name"])

    if people_matches:
        for name in people_matches:
            print(name)
    else:
        print("No match")


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
