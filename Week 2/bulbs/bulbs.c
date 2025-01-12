#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);
void print_byte_bulbs(char byte);
int main(void)
{
    char *str = get_string("Message: ");
    for (int i = 0; i < strlen(str); i++)
        print_byte_bulbs(str[i]);
}
void print_byte_bulbs(char byte)
{
    int tmp;
    for (int i = 1; i <= BITS_IN_BYTE; i++)
    {
        tmp = byte;
        for (int j = i; j < BITS_IN_BYTE; j++)
            tmp /= 2;
        tmp %= 2;
        print_bulb(tmp);
    }
    printf("\n");
}
void print_bulb(int bit)
{
    if (bit == 0)
        // Dark emoji
        printf("\U000026AB");

    else if (bit == 1)
        // Light emoji
        printf("\U0001F7E1");
}
