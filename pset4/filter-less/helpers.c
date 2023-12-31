#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int ave = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = ave;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // sepia color
            int sepiaRed = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue);

            if (sepiaRed > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = sepiaRed;
            }

            if (sepiaGreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = sepiaGreen;
            }

            if (sepiaBlue > 255)
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
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < height; j++)
        {
            tmp[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sum_red, sum_green, sum_blue;
            sum_red = sum_green = sum_blue = 0;
            float count = 0;

            /* calculate the value of 9 pixels
               define image[i][j] as the center of 9 pixels */

            // top left
            if (i - 1 >= 0 && j - 1 >= 0)
            {
                sum_red += tmp[i - 1][j - 1].rgbtRed;
                sum_green += tmp[i - 1][j - 1].rgbtGreen;
                sum_blue += tmp[i - 1][j - 1].rgbtBlue;
                count++;
            }

            // top center
            if (i - 1 >= 0)
            {
                sum_red += tmp[i - 1][j].rgbtRed;
                sum_green += tmp[i - 1][j].rgbtGreen;
                sum_blue += tmp[i - 1][j].rgbtBlue;
                count++;
            }

            // top right
            if (i - 1 >= 0 && j + 1 < width)
            {
                sum_red += tmp[i - 1][j + 1].rgbtRed;
                sum_green += tmp[i - 1][j + 1].rgbtGreen;
                sum_blue += tmp[i - 1][j + 1].rgbtBlue;
                count++;
            }

            // center left
            if (j - 1 >= 0)
            {
                sum_red += tmp[i][j - 1].rgbtRed;
                sum_green += tmp[i][j - 1].rgbtGreen;
                sum_blue += tmp[i][j - 1].rgbtBlue;
                count++;
            }

            // center
            sum_red += tmp[i][j].rgbtRed;
            sum_green += tmp[i][j].rgbtGreen;
            sum_blue += tmp[i][j].rgbtBlue;
            count++;

            // center right
            if (j + 1 < width)
            {
                sum_red += tmp[i][j + 1].rgbtRed;
                sum_green += tmp[i][j + 1].rgbtGreen;
                sum_blue += tmp[i][j + 1].rgbtBlue;
                count++;
            }

            // bottom left
            if (i + 1 < height && j - 1 >= 0)
            {
                sum_red += tmp[i + 1][j - 1].rgbtRed;
                sum_green += tmp[i + 1][j - 1].rgbtGreen;
                sum_blue += tmp[i + 1][j - 1].rgbtBlue;
                count++;
            }

            // bottom center
            if (i + 1 < height)
            {
                sum_red += tmp[i + 1][j].rgbtRed;
                sum_green += tmp[i + 1][j].rgbtGreen;
                sum_blue += tmp[i + 1][j].rgbtBlue;
                count++;
            }

            // bottom right
            if (i + 1 < height && j + 1 < width)
            {
                sum_red += tmp[i + 1][j + 1].rgbtRed;
                sum_green += tmp[i + 1][j + 1].rgbtGreen;
                sum_blue += tmp[i + 1][j + 1].rgbtBlue;
                count++;
            }

            image[i][j].rgbtRed = round(sum_red / count);
            image[i][j].rgbtGreen = round(sum_green / count);
            image[i][j].rgbtBlue = round(sum_blue / count);
        }
    }
    return;
}
