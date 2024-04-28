#include <cs50.h>
#include <stdio.h>

bool checksum(long number);
int last_two(long number);
int get_length(long number);

int main()
{
    long number;
    do
    {
        number = get_long("Number: ");
    }
    while (number <= 0); // non negative
    if (!checksum(number))
    {
        // invalid
        printf("INVALID");
    }
    else
    {
        int front_two = last_two(number);
        int length = get_length(number);
        // check card
        if (length == 15 && (front_two == 34 || front_two == 37))
        {
            printf("AMEX");
        }
        else if (length == 16 && (front_two >= 51 && front_two <= 55))
        {
            printf("MASTERCARD");
        }
        else if ((length == 13 || length == 16) && (front_two / 10 == 4))
        {
            printf("VISA");
        }
        else
        {
            printf("INVALID");
        }
    }
    printf("\n");
}

bool checksum(long number)
{
    long num = number / 10; // copy of numbers
    int su_o = 0;
    int su_e2 = 0;

    while (num > 0)
    {
        int dig2 = (num % 10) * 2; // digit*2
        int su_dig2 = (dig2 / 10) + (dig2 % 10);
        su_e2 += su_dig2;
        num /= 100;
    } // even places

    num = number; // reset for new

    while (num > 0)
    {
        int dig = num % 10;
        su_o += dig;
        num /= 100;

    } // odd places
    int sum = su_o + su_e2;
    if (sum % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    };
};

int last_two(long number)
{
    while (number >= 100)
    {
        number /= 10;
    }
    return number;
};

int get_length(long number)
{
    int length = 0;
    while (number > 0)
    {
        length++;
        number /= 10;
    }
    return length;
}
