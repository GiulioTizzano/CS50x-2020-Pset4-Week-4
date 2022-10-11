#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])

//Take the average of the red, green, and blue values to determine what shade of grey to make the new pixel.
{
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            RGBTRIPLE pixel = image[j][i];

            int average = round((pixel.rgbtRed + pixel.rgbtGreen + pixel.rgbtBlue) / 3.0);

            image[j][i].rgbtRed = average;
            image[j][i].rgbtBlue = average;
            image[j][i].rgbtGreen = average;
            
            //If you apply that to each pixel in the image, the result will be an image converted to grayscale.



        }
    }
    return;
}
float cap(int value)
{
    if (value > 255) 
    {
        value = 255;
    }
    return value;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            RGBTRIPLE pixel = image[j][i];

            float sepiaRed = cap(round(0.393 * pixel.rgbtRed + 0.769 * pixel.rgbtGreen + 0.189 * pixel.rgbtBlue));
            float sepiaGreen = cap(round(0.349 * pixel.rgbtRed + 0.686 * pixel.rgbtGreen + 0.168 * pixel.rgbtBlue));
            float sepiaBlue = cap(round(0.272 * pixel.rgbtRed + 0.534 * pixel.rgbtGreen + 0.131 * pixel.rgbtBlue));

            image[j][i].rgbtRed = sepiaRed;
            image[j][i].rgbtGreen = sepiaGreen;
            image[j][i].rgbtBlue = sepiaBlue;


        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp;
    for (int j = 0;  j < height; j++)
    {
        for (int i = 0; i < width / 2; i++)
        {
            tmp = image[j][i];
            image[j][i] = image[j][width - 1 - i];
            image[j][width - 1 - i] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int avg_red;
    int avg_blue;
    int avg_green;
    float pixels;

    //use the defined datatype to store temporary array
    RGBTRIPLE temp[height][width];

    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {

            avg_red = 0;
            avg_blue = 0;
            avg_green = 0;
            pixels = 0.00;


            //introduce box blur algorithm with new loop
            for (int l = -1; l < 2; l++)
            {
                //Checks if pixel is within height limits
                if (j + l < 0 || j + l > height - 1)
                {
                    continue;
                }

                //Check if pixel is within width limits
                for (int h = -1; h < 2; h++)
                {
                    if (i + h < 0 || i + h > width - 1)
                    {
                        continue;
                    }

                    avg_red += image[j + l][i + h].rgbtRed;
                    avg_green += image[j + l][i + h].rgbtGreen;
                    avg_blue += image[j + l][i + h].rgbtBlue;
                    pixels++;




                    temp[j][i].rgbtBlue = round(avg_blue / pixels);
                    temp[j][i].rgbtGreen = round(avg_green / pixels);
                    temp[j][i].rgbtRed = round(avg_red / pixels);

                    //Build the 3x3 box

                    //Right and left pixels templates: [removed]

                    //Up and down pixels, right and left from there [removed]


                }
            }

        }
    
    }
        
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            image[j][i].rgbtRed = temp[j][i].rgbtRed;
            image[j][i].rgbtBlue = temp[j][i].rgbtBlue;
            image[j][i].rgbtGreen = temp[j][i].rgbtGreen;
        }
    }




    return;

}
