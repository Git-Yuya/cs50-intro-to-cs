#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Caluculate average
            int ave = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = ave;
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
            // Swap pixels
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
    // Make temporally array
    RGBTRIPLE tmp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tmp[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Declare variables for the total value
            int sum_red, sum_green, sum_blue;
            sum_red = sum_green = sum_blue = 0;
            // Declare a variable to count
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

            // Caluculate the average of each value
            image[i][j].rgbtRed = round(sum_red / count);
            image[i][j].rgbtGreen = round(sum_green / count);
            image[i][j].rgbtBlue = round(sum_blue / count);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Make temporally array
    RGBTRIPLE tmp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tmp[i][j] = image[i][j];
        }
    }

    // Make Gx and Gy kernels
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Declare variables
            int Gxred, Gxgreen, Gxblue, Gyred, Gygreen, Gyblue;
            Gxred = Gxgreen = Gxblue = Gyred = Gygreen = Gyblue = 0;

            /* Calculate the value of 9 pixels
               Define image[i][j] as the center of 9 pixels */

            // top left
            if (i - 1 >= 0 && j - 1 >= 0)
            {
                Gxred += Gx[0][0] * tmp[i - 1][j - 1].rgbtRed;
                Gxgreen += Gx[0][0] * tmp[i - 1][j - 1].rgbtGreen;
                Gxblue += Gx[0][0] * tmp[i - 1][j - 1].rgbtBlue;
                Gyred += Gy[0][0] * tmp[i - 1][j - 1].rgbtRed;
                Gygreen += Gy[0][0] * tmp[i - 1][j - 1].rgbtGreen;
                Gyblue += Gy[0][0] * tmp[i - 1][j - 1].rgbtBlue;
            }

            // top center
            if (i - 1 >= 0)
            {
                Gxred += Gx[0][1] * tmp[i - 1][j].rgbtRed;
                Gxgreen += Gx[0][1] * tmp[i - 1][j].rgbtGreen;
                Gxblue += Gx[0][1] * tmp[i - 1][j].rgbtBlue;
                Gyred += Gy[0][1] * tmp[i - 1][j].rgbtRed;
                Gygreen += Gy[0][1] * tmp[i - 1][j].rgbtGreen;
                Gyblue += Gy[0][1] * tmp[i - 1][j].rgbtBlue;
            }

            // top right
            if (i - 1 >= 0 && j + 1 < width)
            {
                Gxred += Gx[0][2] * tmp[i - 1][j + 1].rgbtRed;
                Gxgreen += Gx[0][2] * tmp[i - 1][j + 1].rgbtGreen;
                Gxblue += Gx[0][2] * tmp[i - 1][j + 1].rgbtBlue;
                Gyred += Gy[0][2] * tmp[i - 1][j + 1].rgbtRed;
                Gygreen += Gy[0][2] * tmp[i - 1][j + 1].rgbtGreen;
                Gyblue += Gy[0][2] * tmp[i - 1][j + 1].rgbtBlue;
            }

            // center left
            if (j - 1 >= 0)
            {
                Gxred += Gx[1][0] * tmp[i][j - 1].rgbtRed;
                Gxgreen += Gx[1][0] * tmp[i][j - 1].rgbtGreen;
                Gxblue += Gx[1][0] * tmp[i][j - 1].rgbtBlue;
                Gyred += Gy[1][0] * tmp[i][j - 1].rgbtRed;
                Gygreen += Gy[1][0] * tmp[i][j - 1].rgbtGreen;
                Gyblue += Gy[1][0] * tmp[i][j - 1].rgbtBlue;
            }

            // center
            Gxred += Gx[1][1] * tmp[i][j].rgbtRed;
            Gxgreen += Gx[1][1] * tmp[i][j].rgbtGreen;
            Gxblue += Gx[1][1] * tmp[i][j].rgbtBlue;
            Gyred += Gy[1][1] * tmp[i][j].rgbtRed;
            Gygreen += Gy[1][1] * tmp[i][j].rgbtGreen;
            Gyblue += Gy[1][1] * tmp[i][j].rgbtBlue;

            // center right
            if (j + 1 < width)
            {
                Gxred += Gx[1][2] * tmp[i][j + 1].rgbtRed;
                Gxgreen += Gx[1][2] * tmp[i][j + 1].rgbtGreen;
                Gxblue += Gx[1][2] * tmp[i][j + 1].rgbtBlue;
                Gyred += Gy[1][2] * tmp[i][j + 1].rgbtRed;
                Gygreen += Gy[1][2] * tmp[i][j + 1].rgbtGreen;
                Gyblue += Gy[1][2] * tmp[i][j + 1].rgbtBlue;
            }

            // bottom left
            if (i + 1 < height && j - 1 >= 0)
            {
                Gxred += Gx[2][0] * tmp[i + 1][j - 1].rgbtRed;
                Gxgreen += Gx[2][0] * tmp[i + 1][j - 1].rgbtGreen;
                Gxblue += Gx[2][0] * tmp[i + 1][j - 1].rgbtBlue;
                Gyred += Gy[2][0] * tmp[i + 1][j - 1].rgbtRed;
                Gygreen += Gy[2][0] * tmp[i + 1][j - 1].rgbtGreen;
                Gyblue += Gy[2][0] * tmp[i + 1][j - 1].rgbtBlue;
            }

            // bottom center
            if (i + 1 < height)
            {
                Gxred += Gx[2][1] * tmp[i + 1][j].rgbtRed;
                Gxgreen += Gx[2][1] * tmp[i + 1][j].rgbtGreen;
                Gxblue += Gx[2][1] * tmp[i + 1][j].rgbtBlue;
                Gyred += Gy[2][1] * tmp[i + 1][j].rgbtRed;
                Gygreen += Gy[2][1] * tmp[i + 1][j].rgbtGreen;
                Gyblue += Gy[2][1] * tmp[i + 1][j].rgbtBlue;
            }

            // bottom right
            if (i + 1 < height && j + 1 < width)
            {
                Gxred += Gx[2][2] * tmp[i + 1][j + 1].rgbtRed;
                Gxgreen += Gx[2][2] * tmp[i + 1][j + 1].rgbtGreen;
                Gxblue += Gx[2][2] * tmp[i + 1][j + 1].rgbtBlue;
                Gyred += Gy[2][2] * tmp[i + 1][j + 1].rgbtRed;
                Gygreen += Gy[2][2] * tmp[i + 1][j + 1].rgbtGreen;
                Gyblue += Gy[2][2] * tmp[i + 1][j + 1].rgbtBlue;
            }

            // Caluculate Sobel
            int red = round(sqrt(Gxred * Gxred + Gyred * Gyred));
            int green = round(sqrt(Gxgreen * Gxgreen + Gygreen * Gygreen));
            int blue = round(sqrt(Gxblue * Gxblue + Gyblue * Gyblue));

            if (red > 255)
            {
                red = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            if (blue > 255)
            {
                blue = 255;
            }

            // Substitute new values
            image[i][j].rgbtRed = red;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue = blue;
        }
    }
    return;
}
