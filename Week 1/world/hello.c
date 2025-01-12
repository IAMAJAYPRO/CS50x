#include <cs50.h>
#include <stdio.h>

int main()
{
    string name = get_string("Name? ");
    printf("hello, %s\n", name);
}
