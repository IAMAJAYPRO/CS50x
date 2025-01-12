#include <cs50.h>
#include <stdio.h>

int main()
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1);
    for (int h = 1; h <= n; h++)
    {
        int spaces = n - h;
        int hashes = h;
        for (int j = 0; j < spaces; j++)
        {
            printf(" ");
        };
        for (int j = 0; j < hashes; j++)
        {
            printf("#");
        };
        printf("  "); // print 2 spaces
        for (int j = 0; j < hashes; j++)
        {
            printf("#");
        };

        printf("\n");
    }
}
