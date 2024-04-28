#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char caesar(char ch, int key);
bool is_num(string str);

int main(int argc, string argv[])
{
    // Make sure program was run with just one command-line argument
    if (argc != 2 || !is_num(argv[1]))
    {
        // Make sure every character in argv[1] is a digit
        printf("Usage: %s key", argv[0]);
        return 1;
    }

    // Convert argv[1] from a `string` to an `int`
    int key = atoi(argv[1]);

    // Prompt user for plaintext
    string plaintext = get_string("plaintext:  ");
    printf("ciphertext: ");
    // For each character in the plaintext:
    for (int i = 0; i < strlen(plaintext); i++)
    {
        // Rotate the character if it's a letter
        printf("%c", caesar(plaintext[i], key));
    }
    printf("\n");
};

char caesar(char ch, int key)
{
    if (isupper(ch))
    {
        ch -= 64;
        ch = (ch + key) % 26;
        ch += 64;
        return ch;
    }
    else if (islower(ch))
    {
        ch -= 96;
        ch = (ch + key) % 26;
        ch += 96;
        return ch;
    }
    else
    {
        return ch;
    }
};

bool is_num(string str)
{
    for (int i = 0; i < strlen(str); i++)
    {
        if (!isdigit(str[i]))
        {
            return false;
        }
    }
    return true;
}
