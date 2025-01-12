#include <cs50.h>
#include <stdio.h>

int main()
{
    int owed;
    do
    {
        owed = get_int("Change owed: ");
    }
    while (owed < 0);

    int coin_types[] = {25, 10, 5, 1};
    int coins = 0;

    for (int i = 0; i < 4; i++)
    {
        int cur_coin = coin_types[i];
        while (owed >= cur_coin)
        {
            owed -= cur_coin;
            coins++;
        }
    }
    printf("%i\n", coins);
}
