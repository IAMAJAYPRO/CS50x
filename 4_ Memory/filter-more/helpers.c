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
    int su_red = 0, su_green_x = 0, su_blue = 0;
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
            su_green_x += image[h][k].rgbtGreen;
            su_blue += image[h][k].rgbtBlue;
        }
    }
    // set the pixel
    pixel.rgbtRed = round(su_red / ct);
    pixel.rgbtGreen = round(su_green_x / ct);
    pixel.rgbtBlue = round(su_blue / ct);
    return pixel;
}
// Detect edges
RGBTRIPLE G(int i, int j, int height, int width, RGBTRIPLE image[height][width]);
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE canvas[height][width];
    for (int i = 1; i < height - 1; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            canvas[i][j] = G(i, j, height, width, image);
        }
    }
    // copy the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            image[i][j] = canvas[i][j];
        }
    }
}


RGBTRIPLE G(int i, int j, int height, int width, RGBTRIPLE image[height][width])
{
    int arr[3] = {1, 2, 1};
    RGBTRIPLE pixel;
    int su_red_x = 0, su_green_x = 0, su_blue_x = 0;
    int su_red_y = 0, su_green_y = 0, su_blue_y = 0;
    int h, k;
    float ct = 0;

    for (int p = -1; p < 2; p++)
    {
        h = i + p;
        if (h < 0 || h >= height)
        {
            continue;
        }
        for (int q = -1; q < 2; q++)
        {

            k = j + q;
            ct += 1;
            if (k < 0 || k >= width)
            {
                continue;
            }
            // x
            su_red_x += q * arr[p + 1] * image[h][k].rgbtRed;
            su_green_x += q * arr[p + 1] * image[h][k].rgbtGreen;
            su_blue_x += q * arr[p + 1] * image[h][k].rgbtBlue;
            // arr[p+1] as p stars -1
            // y
            su_red_y += p * arr[q + 1] * image[h][k].rgbtRed;
            su_green_y += p * arr[q + 1] * image[h][k].rgbtGreen;
            su_blue_y += p * arr[q + 1] * image[h][k].rgbtBlue;
        }
    }
    su_red_x = round(su_red_x / ct);
    su_green_x = round(su_green_x / ct);
    su_blue_x = round(su_blue_x / ct);

    su_red_y = round(su_red_y / ct);
    su_green_y = round(su_green_y / ct);
    su_blue_y = round(su_blue_y / ct);
    // cap
    int su_red = (int) sqrt(pow(su_red_x, 2) + pow(su_red_y, 2));
    int su_green = (int) sqrt(pow(su_green_x, 2) + pow(su_green_y, 2));
    int su_blue = (int) sqrt(pow(su_blue_x, 2) + pow(su_blue_y, 2));
    if (su_blue > 255)
    {
        su_blue = 255;
    }
    if (su_green > 255)
    {
        su_green = 255;
    }
    if (su_red > 255)
    {
        su_red = 255;
    }

    // set the pixel
    pixel.rgbtRed = su_red;
    pixel.rgbtGreen = su_green;
    pixel.rgbtBlue = su_blue;
    return pixel;
}
/*
RGBTRIPLE Gx(int i, int j, RGBTRIPLE image[i][j])
{
    int arr[3] = {1, 2, 1} RGBTRIPLE pixel;
    int su_red = 0, su_green = 0, su_blue = 0;
    int h, k;
    float ct = 9;

    for (int p = -1; p < 2; p++)
    {
        h = i + p;
        for (int q = -1; q < 2; q++)
        {
            k = j + q;
            // arr[p+1] as p stars -1
            su_red += q * arr[p + 1] * image[h][k].rgbtRed;
            su_green += q * arr[p + 1] * image[h][k].rgbtGreen;
            su_blue += q * arr[p + 1] * image[h][k].rgbtBlue;
        }
    }
    su_red = round(su_red / ct);
    su_green = round(su_green / ct);
    su_blue = round(su_blue / ct);
    // cap

    if (su_blue > 255)
    {
        su_blue = 255;
    }
    if (su_green > 255)
    {
        su_green = 255;
    }
    if (su_red > 255)
    {
        su_red = 255;
    }

    // set the pixel
    pixel.rgbtRed = su_red;
    pixel.rgbtGreen = su_green;
    pixel.rgbtBlue = su_blue;
    return pixel;
} */
