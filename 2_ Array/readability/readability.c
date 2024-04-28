#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count(string para, string diff);
int is_sent_sep(int num);
int main(void)
{
    // Prompt the user for some text
    string sentence = get_string("Text: ");
    // Count the number of letters, words, and sentences in the text
    int words = count(sentence, "words");
    int letters = count(sentence, "letters");
    int sents = count(sentence, "sents");
    // Compute the Coleman-Liau index

    float L = (float) letters * 100 / words;
    float S = (float) sents * 100 / words;

    float index = 0.0588 * L - 0.296 * S - 15.8;
    // Print the grade level
    // printf("f:%f\tw:%i\tl:%i\ts:%i\tL:%f\tS:%f\t\n", index, words, letters, sents, L, S);
    if (index < 1.0)
    {
        printf("Before Grade 1");
    }
    else if (index >= 1 && index < 16)
    {
        printf("Grade %i", (int) round(index));
    }
    else
    {
        printf("Grade 16+");
    }
    printf("\n");
}
int is_sent_sep(int num)
{
    char ch = (char) num;
    return (ch == '.' || ch == '?' || ch == '!');
};
int count(string para, string di_str)
{
    int ct = 0;
    int (*func)(int);
    if (strcmp(di_str, "words") == 0)
    {
        func = isspace;
        ct = 1;
    }
    else if (strcmp(di_str, "letters") == 0)
    {
        func = isalpha;
    }
    else if (strcmp(di_str, "sents") == 0)
    {
        func = is_sent_sep;
    }
    else
    {
        printf("Error function not found");
        return -1;
    }

    for (int i = 0; i < strlen(para); i++)
    {

        if (func(para[i]))
        {
            ct += 1;
        };
    };
    return ct;
};
