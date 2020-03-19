#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// <param name="string"> A string of numbers separated by spaces.</param> 
void StringToSequence(char* string, int* sequence, int *sequenceLength)
{
    int sequence_index = 0;
    int offset = 0;

    int current_number = 0;
    int characters_read_count = 0;
    int arguments_read_count = 0;

    arguments_read_count = sscanf(string + offset, "%d%n", &current_number, &characters_read_count);

    while (arguments_read_count > 0)
    {
        sequence[sequence_index] = current_number;
        offset += characters_read_count;
        sequence_index++;
        arguments_read_count = sscanf(string + offset, "%d%n", &current_number, &characters_read_count);
    }

    *sequenceLength = sequence_index;
}

void PrintSequence(int* sequence, int sequenceLength)
{
    for (int i = 0; i < sequenceLength; i++)
    {
        printf("%d ", sequence[i]);
    }

    printf("\n");
}

int Absolute(int number)
{
    if (number < 0)
    {
        return -number;
    }
    else
    {
        return number;
    }
}

int IsPrime(int number)
{
    number = Absolute(number);

    if (number == 0 || number == 1)
    {
        return 0;
    }

    if (number == 2)
    {
        return 1;
    }

    for (int i = 2; i * i < number; i++)
    {
        if (number % i == 0)
        {
            return 0;
        }
    }

    return 1;
}

typedef int(*SequenceValidator)(int* sequence, int sequenceLength);

void GenerateSubsequenceLengths(int* sequence, int sequenceLength, SequenceValidator isValid, int* subsequencesLengths)
{
    for (int i = 0; i < sequenceLength; i++)
    {
        int current_length = 1;

        for (int j = i + 1; j < sequenceLength; j++)
        {
            if (isValid(sequence + i, j - i + 1) == 0)
            {
                break;
            }

            current_length++;   
         }

        subsequencesLengths[i] = current_length;
    }
}

void LongestContiguousSubsequence(int* sequence, int sequenceLength, SequenceValidator isValid, int* subsequence, int* subsequenceLength)
{
    int* subsequences_lengths = (int*)malloc(100 * sizeof(int));

    GenerateSubsequenceLengths(sequence, sequenceLength, isValid, subsequences_lengths);

    int longest_subsequence_index = 0;
    int longest_subsequence_length = subsequences_lengths[longest_subsequence_index];

    for (int i = 1; i < sequenceLength; i++)
    {
        if (subsequences_lengths[i] > longest_subsequence_length)
        {
            longest_subsequence_index = i;
            longest_subsequence_length = subsequences_lengths[longest_subsequence_index];
        }
    }

    for (int i = 0; i < longest_subsequence_length; i++)
    {
        subsequence[i] = sequence[longest_subsequence_index + i];
    }

    *subsequenceLength = longest_subsequence_length;
}

int LastElementsDifferenceIsPrime(int* sequence, int sequenceLength)
{
    if (sequenceLength <= 1)
    {
        return 1;
    }

    int last_element = sequence[sequenceLength - 1];
    int second_last_element = sequence[sequenceLength - 2];

    int difference = last_element - second_last_element;

    return IsPrime(difference);
}

int main()
{
    int* input_sequence = (int*)malloc(100 * sizeof(int));
    memset(input_sequence, 0, sizeof(*input_sequence));
    int input_sequence_length = 0;

    char* input = (char*)malloc(100 * sizeof(int));
    memset(input, 0, sizeof(*input));

    gets(input);

    StringToSequence(input, input_sequence, &input_sequence_length);

    //print_sequenceay(sequence, sequence_length);

    int* longest_contiguous_subsequence = (int*)malloc(100 * sizeof(int));
    memset(longest_contiguous_subsequence, 0, sizeof(*longest_contiguous_subsequence));
    int longest_contiguous_subsequence_length = 0;

    //generate_lengths(sequence, sequence_length, sequence_difference_is_prime, subsequence);
    //subsequence_length = sequence_length;

    LongestContiguousSubsequence(input_sequence, input_sequence_length, LastElementsDifferenceIsPrime, longest_contiguous_subsequence, &longest_contiguous_subsequence_length);
    PrintSequence(longest_contiguous_subsequence, longest_contiguous_subsequence_length);

    free(longest_contiguous_subsequence);
    free(input);
    free(input_sequence);

    return 0;
}
