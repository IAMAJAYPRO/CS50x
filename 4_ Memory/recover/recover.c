#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }
    int ct = 0;
    char file_name[12];
    // Open the memory card
    FILE *card = fopen(argv[1], "r");
    // Create a buffer for a block of data
    uint8_t buffer[512];
    // While there's still data left to read from the memory card
    FILE *img = NULL;
    while (fread(buffer, 1, 512, card))
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff)
        {
            // is start
            if (img)
            {
                fclose(img);
            }
            // open new file
            sprintf(file_name, "%03i.jpg", ct++);
            img = fopen(file_name, "w");
        }
        // Create JPEGs from the data
        if (img)
        {
            fwrite(buffer, 1, 512, img);
        }
    }
    if (img)
    {
        // still open
        fclose(img);
    }
    fclose(card);
}
