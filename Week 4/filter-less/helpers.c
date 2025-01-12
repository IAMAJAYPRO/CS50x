#include "helpers.h"
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int avg;
    // RGBTRIPLE cur_pixel;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // cur_pixel = image[i][j]; this creates new struct ;(
            avg = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = avg;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepiaRed, sepiaGreen, sepiaBlue;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen +
                             .189 * image[i][j].rgbtBlue);
            sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen +
                               .168 * image[i][j].rgbtBlue);
            sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen +
                              .131 * image[i][j].rgbtBlue);
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            tmp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = tmp;
        }
    }
}
RGBTRIPLE calculate_blur(int i, int j, int height, int width, RGBTRIPLE image[height][width]);

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE blured[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            blured[i][j] = calculate_blur(i, j, height, width, image);
        }
    }
    // copy to main image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = blured[i][j];
        }
    }
}

RGBTRIPLE calculate_blur(int i, int j, int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE pixel;
    int su_red = 0, su_green = 0, su_blue = 0;
    int h, k;
    float ct = 0;

    for (int p = -1; p < 2; p++)
    {
        h = i + p;
        if (!(h >= 0 && h < height))
        {
            continue;
        }

        for (int q = -1; q < 2; q++)
        {
            k = j + q;
            if (!(k >= 0 && k < width))
            {
                continue;
            }
            // at point h,k
            ct++;
            su_red += image[h][k].rgbtRed;
            su_green += image[h][k].rgbtGreen;
            su_blue += image[h][k].rgbtBlue;
        }
    }
    // set the pixel
    pixel.rgbtRed = round(su_red / ct);
    pixel.rgbtGreen = round(su_green / ct);
    pixel.rgbtBlue = round(su_blue / ct);
    return pixel;
}

/*
//function to change the values;
void copy_from(RGBTRIPLE *fr, RGBTRIPLE *to)
{
    to->rgbtRed = fr->rgbtRed;
    to->rgbtGreen = fr->rgbtGreen;
    to->rgbtBlue = fr->rgbtBlue;
}
*/
