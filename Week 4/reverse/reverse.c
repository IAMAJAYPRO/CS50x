#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if (argc != 3)
    {
        perror("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }
    // Open input file for reading
    // TODO #2
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        perror("Could not open file.\n");
        return 1;
    }

    // Read header
    // TODO #3
    WAVHEADER header;
    fread(&header, sizeof(WAVHEADER), 1, input);

    // Use check_format to ensure WAV format
    // TODO #4
    if (check_format(header) == 0)
    {
        perror("Invalid format");
        return 1;
    }

    // Open output file for writing
    // TODO #5
    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        perror("Could not open file.\n");
        return 1;
    }

    // Write header to file
    // TODO #6
    fwrite(&header, sizeof(WAVHEADER), 1, output);

    // Use get_block_size to calculate size of block
    // TODO #7
    int block_size = get_block_size(header);
    // Write reversed audio to file
    // TODO #8
    int nChunks = header.subchunk2Size / block_size;
    BYTE tmp[nChunks][block_size];
    for (int i = nChunks - 1; i >= 0; i--)
        fread(tmp[i], sizeof(char), block_size, input);
    for (int i = 0; i < nChunks; i++)
        fwrite(tmp[i], sizeof(char), block_size, output);

    fclose(input);
    fclose(output);
}

int check_format(WAVHEADER header)
{
    char *str = "WAVE";
    for (int i = 0; i < 4; i++)
        if (header.format[i] != str[i])
            return 0;
    return 1;
}

int get_block_size(WAVHEADER header)
{
    return (int) header.blockAlign;
}
