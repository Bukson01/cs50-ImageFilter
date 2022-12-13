#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Get RGBTriple values
            float blue = image[i][j].rgbtBlue;
            float green = image[i][j].rgbtGreen;
            float red = image[i][j].rgbtRed;
            // Calculate average
            int average = round((red + blue + green) / 3.0);

            // replacing the RGB colors at the pixels with the average
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float blue = image[i][j].rgbtBlue;
            float green = image[i][j].rgbtGreen;
            float red = image[i][j].rgbtRed;
           //Converting the pixel colors to the sepia colors
            int sepiaRed = round(.393 * red + .769 * green + .189 * blue);
            if(sepiaRed > 255)//checks if the value of red exceeds 255
            {
               image[i][j].rgbtRed = 255;
            }
            else {
                image[i][j].rgbtRed = sepiaRed;
            }

            int sepiaGreen =round(.349 * red + .686 * green + .168 * blue);
            if(sepiaGreen > 255)//checks if the value of blue exceeds 255
            {
               image[i][j].rgbtGreen = 255;
            }
            else{
                image[i][j].rgbtGreen = sepiaGreen;
            }

            int sepiaBlue = round(.272 * red + .534 * green + .131 * blue);
            if(sepiaBlue >255)//checks if the value of blue exceeds 255
            {
                image[i][j].rgbtBlue = 255;
            }
            else{
                image[i][j].rgbtBlue = sepiaBlue;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width/2; j++)
        {
            temp[i][j] = image[i][j];
            image[i][j] = image[i][width - (j+1)];
            image[i][width - (j+1)] = temp[i][j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
     //create a temporary image to be blurred
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sum_blue;
            int sum_green;
            int sum_red;
            float counter;
            sum_blue = sum_green = sum_red = counter = 0;
//CORNERS
            //corner pixel on bottom right
            if (i >= 0 && j >= 0)
            {
                sum_red += temp[i][j].rgbtRed;
                sum_green += temp[i][j].rgbtGreen;
                sum_blue += temp[i][j].rgbtBlue;
                counter++;
            }
            //corner pixel on bottom left
            if (i >= 0 && j - 1 >= 0)
            {
                sum_red += temp[i][j-1].rgbtRed;
                sum_green += temp[i][j-1].rgbtGreen;
                sum_blue += temp[i][j-1].rgbtBlue;
                counter++;
            }
            //corner pixel on top left
            if (i - 1 >= 0 && j >= 0)
            {
                sum_red += temp[i-1][j].rgbtRed;
                sum_green += temp[i-1][j].rgbtGreen;
                sum_blue += temp[i-1][j].rgbtBlue;
                counter++;
            }
            //corner pixel on top right
            if (i - 1 >= 0 && j - 1 >= 0)
            {
                sum_red += temp[i-1][j-1].rgbtRed;
                sum_green += temp[i-1][j-1].rgbtGreen;
                sum_blue += temp[i-1][j-1].rgbtBlue;
                counter++;
            }
//FOUR EDGES
            //pixels on bottom edge
            if ((i >= 0 && j + 1 >= 0) && (i >= 0 && j + 1 < width))
            {
                sum_red += temp[i][j+1].rgbtRed;
                sum_green += temp[i][j+1].rgbtGreen;
                sum_blue += temp[i][j+1].rgbtBlue;
                counter++;
            }
            //pixels on top edge
            if ((i - 1 >= 0 && j + 1 >= 0) && (i - 1 >= 0 && j + 1 < width))
            {
                sum_red += temp[i-1][j+1].rgbtRed;
                sum_green += temp[i-1][j+1].rgbtGreen;
                sum_blue += temp[i-1][j+1].rgbtBlue;
                counter++;
            }
            //pixels on left edge
            if ((i + 1 >= 0 && j >= 0) && (i + 1 < height && j >= 0))
            {
                sum_red += temp[i+1][j].rgbtRed;
                sum_green += temp[i+1][j].rgbtGreen;
                sum_blue += temp[i+1][j].rgbtBlue;
                counter++;
            }
            //pixels on right edge
            if ((i + 1 >= 0 && j - 1 >= 0) && (i + 1 < height && j - 1 >= 0))
            {
                sum_red += temp[i+1][j-1].rgbtRed;
                sum_green += temp[i+1][j-1].rgbtGreen;
                sum_blue += temp[i+1][j-1].rgbtBlue;
                counter++;
            }
//MIDDLE PIXELS
            //middle pixels
            if ((i + 1 >= 0 && j + 1 >= 0) && (i + 1 < height && j + 1 < width))
            {
                sum_red += temp[i+1][j+1].rgbtRed;
                sum_green += temp[i+1][j+1].rgbtGreen;
                sum_blue += temp[i+1][j+1].rgbtBlue;
                counter++;
            }
            //find average colour value
            image[i][j].rgbtRed = round(sum_red / counter);
            image[i][j].rgbtGreen = round(sum_green / counter);
            image[i][j].rgbtBlue = round(sum_blue / counter);
        }
    }
    return;
}
