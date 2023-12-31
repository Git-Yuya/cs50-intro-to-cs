import csv
import sys


def main():

    # Ensure correct usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    # Open the databases csv file and read its contents into memory.
    data_file = sys.argv[1]
    with open(data_file, "r") as csv_file:
        dict_reader = csv.DictReader(csv_file)
        # Convert to dictionary list
        data_list = list(dict_reader)

    # Open the sequences txt file and read its contents into memory.
    seq_file = sys.argv[2]
    with open(seq_file, "r") as txt_file:
        dna_seq = txt_file.read()

    # Max repeats list of STRs
    max_repeats = max_repeats_STR(dict_reader, dna_seq)
    # Print the result
    print_result(dict_reader, data_list, max_repeats)


# Compute STR counts
def max_repeats_STR(reader, seq):
    max_repeats = []

    # Find STRs
    for i in range(1, len(reader.fieldnames)):
        STR = reader.fieldnames[i]
        max_repeats.append(0)

        for j in range(len(seq)):
            STR_count = 0

            if seq[j:(j + len(STR))] == STR:
                offset = 0
                while seq[(j + offset):(j + offset + len(STR))] == STR:
                    STR_count += 1
                    offset += len(STR)
                if STR_count > max_repeats[i - 1]:
                    max_repeats[i - 1] = STR_count

    return max_repeats


# Compare data_list with max_repeats and print the result
def print_result(reader, data, repeats):
    for i in range(len(data)):
        matches = 0

        for j in range(1, len(reader.fieldnames)):
            if int(repeats[j - 1]) == int(data[i][reader.fieldnames[j]]):
                matches += 1

            # Make sure the number of STRs is equal
            if matches == (len(reader.fieldnames) - 1):
                print(data[i]["name"])
                sys.exit(0)

    print("No match")


if __name__ == "__main__":
    main()
