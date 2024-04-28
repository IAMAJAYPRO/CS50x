#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int getScore(string s);
int main(void)
{

    // Prompt the user for two words
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");
    // Compute the score of each word
    int score1 = getScore(word1);
    int score2 = getScore(word2);
    // Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins");
    }
    else
    {
        printf("Tie!");
    }
    printf("\n");
}

const int helper[26] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                        1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int getScore(string s)
{
    int sc = 0;
    for (int i = 0; i < strlen(s); i++)
    {
        char letter = toupper(s[i]);
        if (isalpha(letter))
        {
            sc += helper[letter - 65];
        };
    };
    return sc;
};
