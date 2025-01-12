#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
char encr(char ch, string key);
bool valid(string key);

int main(int argc, string argv[])
{
    // Make sure program was run with just one command-line argument
    if (argc != 2)
    {
        // Make sure every character in argv[1] is a digit
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }
    else if (!valid(argv[1]))
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // Convert argv[1] from a `string` to an `int`
    string key = argv[1];

    // Prompt user for plaintext
    string plaintext = get_string("plaintext:  ");
    printf("ciphertext: ");
    // For each character in the plaintext:
    for (int i = 0; i < strlen(plaintext); i++)
    {
        // Rotate the character if it's a letter
        printf("%c", encr(plaintext[i], key));
    }
    printf("\n");
};
bool valid(string key)
{
    if (strlen(key) != 26)
    {
        return false;
    }
    int end = 0;
    char arr[26];
    // check both symbols and repetition in same
    for (int i = 0; i < strlen(key); i++)
    {
        char ch = toupper(key[i]);
        if (!isalpha(ch))
        {
            return false;
        }
        for (int j = 0; j < end; j++)
        {
            if (arr[j] == ch)
            {
                return false;
            }
        }
        arr[end] = ch;
        end++;
    }

    return true;
};
char encr(char ch, string key)
{
    if (isalpha(ch))
    {
        if (isupper(ch))
        {
            return toupper(key[ch - 65]);
        }
        else if (islower(ch))
        {
            return tolower(key[ch - 97]);
        }
    }
    return ch;
};
