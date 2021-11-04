#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            double val1 = image[i][j].rgbtBlue;
            double val2 = image[i][j].rgbtGreen;
            double val3 = image[i][j].rgbtRed;
            int rgbtAvg = round((val1 + val2 + val3) / 3);
            image[i][j].rgbtBlue = rgbtAvg;
            image[i][j].rgbtGreen = rgbtAvg;
            image[i][j].rgbtRed = rgbtAvg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            double originalRed = image[i][j].rgbtRed;
            double originalGreen = image[i][j].rgbtGreen;
            double originalBlue = image[i][j].rgbtBlue;
            int sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            int sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            int sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);

            if(sepiaRed > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = sepiaRed;
            }

            if(sepiaGreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = sepiaGreen;
            }
            if(sepiaBlue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = sepiaBlue;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            copy[i][j].rgbtRed = image[i][j].rgbtRed;
            copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            copy[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    if(width % 2 != 0)
    {
        for(int i = 0; i < height; i++)
        {
            for(int j = 0; j < (int)width/2; j++)
            {
                image[i][j].rgbtRed = copy[i][width - 1 - j].rgbtRed;
                image[i][j].rgbtGreen = copy[i][width - 1 - j].rgbtGreen;
                image[i][j].rgbtBlue = copy[i][width - 1 - j].rgbtBlue;
            }
            for(int j = width/2 + 1; j < width; j++)
            {
                image[i][j].rgbtRed = copy[i][width - 1 - j].rgbtRed;
                image[i][j].rgbtGreen = copy[i][width - 1 - j].rgbtGreen;
                image[i][j].rgbtBlue = copy[i][width - 1 - j].rgbtBlue;
            }
        }
    }
    else
    {
        for(int i = 0; i < height; i++)
        {
            for(int j = 0; j < width; j++)
            {
                image[i][j].rgbtRed = copy[i][width - 1 - j].rgbtRed;
                image[i][j].rgbtGreen = copy[i][width - 1 - j].rgbtGreen;
                image[i][j].rgbtBlue = copy[i][width - 1 - j].rgbtBlue;
            }
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    typedef struct
    {
        double  rgbtBlue;
        double  rgbtGreen;
        double  rgbtRed;
    } RGBTRIPLECopy;

    RGBTRIPLECopy copy[height][width];

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            copy[i][j].rgbtRed = image[i][j].rgbtRed;
            copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            copy[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    image[0][0].rgbtRed = round(((copy[0][0].rgbtRed + copy[0][1].rgbtRed + copy[1][1].rgbtRed + copy[1][0].rgbtRed)/4));
    image[0][0].rgbtGreen = round(((copy[0][0].rgbtGreen + copy[0][1].rgbtGreen + copy[1][1].rgbtGreen + copy[1][0].rgbtGreen)/4));
    image[0][0].rgbtBlue = round(((copy[0][0].rgbtBlue + copy[0][1].rgbtBlue + copy[1][1].rgbtBlue + copy[1][0].rgbtBlue)/4));

    image[0][width - 1].rgbtRed = round(((copy[0][width - 1].rgbtRed + copy[1][width - 1].rgbtRed + copy[1][width - 2].rgbtRed + copy[0][width - 2].rgbtRed)/4));
    image[0][width - 1].rgbtGreen = round(((copy[0][width - 1].rgbtGreen + copy[1][width - 1].rgbtGreen + copy[1][width - 2].rgbtGreen + copy[0][width - 2].rgbtGreen)/4));
    image[0][width - 1].rgbtBlue = round(((copy[0][width - 1].rgbtBlue + copy[1][width - 1].rgbtBlue + copy[1][width - 2].rgbtBlue + copy[0][width - 2].rgbtBlue)/4));

    image[height - 1][0].rgbtRed = round(((copy[height - 1][0].rgbtRed + copy[height - 2][0].rgbtRed + copy[height - 2][1].rgbtRed + copy[height - 1][1].rgbtRed)/4));
    image[height - 1][0].rgbtGreen = round(((copy[height - 1][0].rgbtGreen + copy[height - 2][0].rgbtGreen + copy[height - 2][1].rgbtGreen + copy[height - 1][1].rgbtGreen)/4));
    image[height - 1][0].rgbtBlue = round(((copy[height - 1][0].rgbtBlue + copy[height - 2][0].rgbtBlue + copy[height - 2][1].rgbtBlue + copy[height - 1][1].rgbtBlue)/4));

    image[height - 1][width - 1].rgbtRed = round(((copy[height -1][width - 1].rgbtRed + copy[height -1][width - 2].rgbtRed + copy[height - 2][width - 2].rgbtRed + copy[height - 2][width - 1].rgbtRed)/4));
    image[height - 1][width - 1].rgbtGreen = round(((copy[height -1][width - 1].rgbtGreen + copy[height -1][width - 2].rgbtGreen + copy[height - 2][width - 2].rgbtGreen + copy[height - 2][width - 1].rgbtGreen)/4));
    image[height - 1][width - 1].rgbtBlue = round(((copy[height -1][width - 1].rgbtBlue + copy[height -1][width - 2].rgbtBlue + copy[height - 2][width - 2].rgbtBlue + copy[height - 2][width - 1].rgbtBlue)/4));

    for(int i = 1; i < width - 1; i++)
    {
        image[0][i].rgbtRed = round(((copy[0][i].rgbtRed + copy[0][i - 1].rgbtRed + copy[1][i - 1].rgbtRed + copy[1][i].rgbtRed + copy[1][i + 1].rgbtRed + copy[0][i + 1].rgbtRed)/6));
        image[0][i].rgbtGreen = round(((copy[0][i].rgbtGreen + copy[0][i - 1].rgbtGreen + copy[1][i - 1].rgbtGreen + copy[1][i].rgbtGreen + copy[1][i + 1].rgbtGreen + copy[0][i + 1].rgbtGreen)/6));
        image[0][i].rgbtBlue = round(((copy[0][i].rgbtBlue + copy[0][i - 1].rgbtBlue + copy[1][i - 1].rgbtBlue + copy[1][i].rgbtBlue + copy[1][i + 1].rgbtBlue + copy[0][i + 1].rgbtBlue)/6));

        image[height - 1][i].rgbtRed = round(((copy[height - 1][i].rgbtRed + copy[height - 1][i - 1].rgbtRed + copy[height - 2][i - 1].rgbtRed + copy[height - 2][i].rgbtRed + copy[height - 2][i + 1].rgbtRed + copy[height - 1][i + 1].rgbtRed)/6));
        image[height - 1][i].rgbtGreen = round(((copy[height - 1][i].rgbtGreen + copy[height - 1][i - 1].rgbtGreen + copy[height - 2][i - 1].rgbtGreen + copy[height - 2][i].rgbtGreen + copy[height - 2][i + 1].rgbtGreen + copy[height - 1][i + 1].rgbtGreen)/6));
        image[height - 1][i].rgbtBlue = round(((copy[height - 1][i].rgbtBlue + copy[height - 1][i - 1].rgbtBlue + copy[height - 2][i - 1].rgbtBlue + copy[height - 2][i].rgbtBlue + copy[height - 2][i + 1].rgbtBlue + copy[height - 1][i + 1].rgbtBlue)/6));
    }

    for(int i = 1; i < height - 1; i++)
    {
        image[i][0].rgbtRed = round(((copy[i][0].rgbtRed + copy[i - 1][0].rgbtRed + copy[i - 1][1].rgbtRed + copy[i][1].rgbtRed + copy[i + 1][1].rgbtRed + copy[i + 1][0].rgbtRed)/6));
        image[i][0].rgbtGreen = round(((copy[i][0].rgbtGreen + copy[i - 1][0].rgbtGreen + copy[i - 1][1].rgbtGreen + copy[i][1].rgbtGreen + copy[i + 1][1].rgbtGreen + copy[i + 1][0].rgbtGreen)/6));
        image[i][0].rgbtBlue = round(((copy[i][0].rgbtBlue + copy[i - 1][0].rgbtBlue + copy[i - 1][1].rgbtBlue + copy[i][1].rgbtBlue + copy[i + 1][1].rgbtBlue + copy[i + 1][0].rgbtBlue)/6));

        image[width - 1][i].rgbtRed = round(((copy[width - 1][i].rgbtRed + copy[width - 1][i - 1].rgbtRed + copy[width - 2][i - 1].rgbtRed + copy[width - 2][i].rgbtRed + copy[width - 2][i + 1].rgbtRed + copy[width - 1][i + 1].rgbtRed)/6));
        image[width - 1][i].rgbtGreen = round(((copy[width - 1][i].rgbtGreen + copy[width - 1][i - 1].rgbtGreen + copy[width - 2][i - 1].rgbtGreen + copy[width - 2][i].rgbtGreen + copy[width - 2][i + 1].rgbtGreen + copy[width - 1][i + 1].rgbtGreen)/6));
        image[width - 1][i].rgbtBlue = round(((copy[width - 1][i].rgbtBlue + copy[width - 1][i - 1].rgbtBlue + copy[width - 2][i - 1].rgbtBlue + copy[width - 2][i].rgbtBlue + copy[width - 2][i + 1].rgbtBlue + copy[width - 1][i + 1].rgbtBlue)/6));
    }

    for(int i = 1; i < height - 1; i++)
    {
        for(int j = 1; j < width - 1; j++)
        {
            image[i][j].rgbtRed = round(((image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed)/9));
            image[i][j].rgbtGreen = round(((image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen)/9));
            image[i][j].rgbtBlue = round(((image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue)/9));
        }
    }

    return;
}
