#include "helpers.h"
#include <math.h>
#include <stdlib.h>

// Convert image to grayscale
//Various conversion methods for Filters
//Method 1 Grayscale
//  converts the image to a black and white
//  image based on the avrage values of
//  RGB for a given pixel
//Method 2 Reflect
//  Creates a mirror Image of the given image
//  It does it by reversing the values of each pixel row by row
//Method 3 Blur
//  Makes the image blur by
//  taking the avrage of all the
//  adjcent pixel values and calculates
//  the avrage for each pixel
//  making a blurry effect
//Method 4 Edge
//  Detects the edge based on the matrix :
//      Gx = -1  0  1
//           -2  0  2
//           -1  0  1
//
//      Gy = -1 -2 -1
//            0  0  0
//            1  2  1
//
//  it calculates the value of each pixel based on the value recieved from these
//  matrixes and finding the squared root of the sum of Gx and Gy
// It returns the answer back to the main executable
// where it is processed and otputted as an image

void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int a = (int)image[i][j].rgbtBlue + (int)image[i][j].rgbtGreen + (int)image[i][j].rgbtRed;
            a = round((float)a / 3);
            BYTE avj = (BYTE) a;
            image[i][j].rgbtBlue = avj;
            image[i][j].rgbtGreen = avj;
            image[i][j].rgbtRed = avj;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        RGBTRIPLE temp;
        int start = 0;
        int end = width - 1;
        while (start < end)
        {
            temp = image[i][start];
            // temp.rgbtGreen = image[i][start];
            // temp.rgbtRed = image[i][start];
            image[i][start] = image[i][end];
            image[i][end] = temp;
            start++;
            end--;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*temp)[width] = calloc(height, width * sizeof(RGBTRIPLE));        //temp storage for the orignal image
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
            if (i == 0)
            {
                if (j == 0)                                     //fot top left pixel
                {
                    int avgR = (int) temp[i][j].rgbtRed + (int) temp[i][j + 1].rgbtRed + (int) temp[i + 1][j].rgbtRed +
                               (int) temp[i + 1][j + 1].rgbtRed;
                    int avgG = (int) temp[i][j].rgbtGreen + (int) temp[i][j + 1].rgbtGreen + (int) temp[i + 1][j].rgbtGreen +
                               (int) temp[i + 1][j + 1].rgbtGreen;
                    int avgB = (int) temp[i][j].rgbtBlue + (int) temp[i][j + 1].rgbtBlue + (int) temp[i + 1][j].rgbtBlue +
                               (int) temp[i + 1][j + 1].rgbtBlue;
                    avgR = round((float)avgR / 4);
                    avgG = round((float)avgG / 4);
                    avgB = round((float)avgB / 4);
                    image[i][j].rgbtRed = (BYTE) avgR;
                    image[i][j].rgbtGreen = (BYTE) avgG;
                    image[i][j].rgbtBlue = (BYTE) avgB;
                }
                else if (j == width - 1)                    //for top right pixel
                {
                    int avgR = (int) temp[i][j].rgbtRed + (int) temp[i][j - 1].rgbtRed + (int) temp[i + 1][j].rgbtRed +
                               (int) temp[i + 1][j - 1].rgbtRed;
                    int avgG = (int) temp[i][j].rgbtGreen + (int) temp[i][j - 1].rgbtGreen + (int) temp[i + 1][j].rgbtGreen +
                               (int) temp[i + 1][j - 1].rgbtGreen;
                    int avgB = (int) temp[i][j].rgbtBlue + (int) temp[i][j - 1].rgbtBlue + (int) temp[i + 1][j].rgbtBlue +
                               (int) temp[i + 1][j - 1].rgbtBlue;
                    avgR = round((float)avgR / 4);
                    avgG = round((float)avgG / 4);
                    avgB = round((float)avgB / 4);
                    image[i][j].rgbtRed = (BYTE) avgR;
                    image[i][j].rgbtGreen = (BYTE) avgG;
                    image[i][j].rgbtBlue = (BYTE) avgB;
                }
                else                    //for top row
                {
                    int avgR = (int) temp[i][j].rgbtRed + (int) temp[i][j - 1].rgbtRed + (int) temp[i + 1][j].rgbtRed +
                               (int) temp[i + 1][j - 1].rgbtRed + (int) temp[i][j + 1].rgbtRed + (int) temp[i + 1][j + 1].rgbtRed;
                    int avgG = (int) temp[i][j].rgbtGreen + (int) temp[i][j - 1].rgbtGreen + (int) temp[i + 1][j].rgbtGreen +
                               (int) temp[i + 1][j - 1].rgbtGreen + (int) temp[i][j + 1].rgbtGreen + (int) temp[i + 1][j + 1].rgbtGreen;
                    int avgB = (int) temp[i][j].rgbtBlue + (int) temp[i][j - 1].rgbtBlue + (int) temp[i + 1][j].rgbtBlue +
                               (int) temp[i + 1][j - 1].rgbtBlue + (int) temp[i][j + 1].rgbtBlue + (int) temp[i + 1][j + 1].rgbtBlue;
                    avgR = round((float)avgR / 6);
                    avgG = round((float)avgG / 6);
                    avgB = round((float)avgB / 6);
                    image[i][j].rgbtRed = (BYTE) avgR;
                    image[i][j].rgbtGreen = (BYTE) avgG;
                    image[i][j].rgbtBlue = (BYTE) avgB;
                }
            }
            else if (i == height - 1)
            {
                if (j == 0)                         //for bottom left pixel
                {
                    int avgR = (int) temp[i][j].rgbtRed + (int) temp[i][j + 1].rgbtRed + (int) temp[i - 1][j].rgbtRed +
                               (int) temp[i - 1][j + 1].rgbtRed;
                    int avgG = (int) temp[i][j].rgbtGreen + (int) temp[i][j + 1].rgbtGreen + (int) temp[i - 1][j].rgbtGreen +
                               (int) temp[i - 1][j + 1].rgbtGreen;
                    int avgB = (int) temp[i][j].rgbtBlue + (int) temp[i][j + 1].rgbtBlue + (int) temp[i - 1][j].rgbtBlue +
                               (int) temp[i - 1][j + 1].rgbtBlue;
                    avgR = round((float)avgR / 4);
                    avgG = round((float)avgG / 4);
                    avgB = round((float)avgB / 4);
                    image[i][j].rgbtRed = (BYTE) avgR;
                    image[i][j].rgbtGreen = (BYTE) avgG;
                    image[i][j].rgbtBlue = (BYTE) avgB;
                }
                else if (j == width - 1)                //for bottom right pixel
                {
                    int avgR = (int) temp[i][j].rgbtRed + (int) temp[i][j - 1].rgbtRed + (int) temp[i - 1][j].rgbtRed +
                               (int) temp[i - 1][j - 1].rgbtRed;
                    int avgG = (int) temp[i][j].rgbtGreen + (int) temp[i][j - 1].rgbtGreen + (int) temp[i - 1][j].rgbtGreen +
                               (int) temp[i - 1][j - 1].rgbtGreen;
                    int avgB = (int) temp[i][j].rgbtBlue + (int) temp[i][j - 1].rgbtBlue + (int) temp[i - 1][j].rgbtBlue +
                               (int) temp[i - 1][j - 1].rgbtBlue;
                    avgR = round((float)avgR / 4);
                    avgG = round((float)avgG / 4);
                    avgB = round((float)avgB / 4);
                    image[i][j].rgbtRed = (BYTE) avgR;
                    image[i][j].rgbtGreen = (BYTE) avgG;
                    image[i][j].rgbtBlue = (BYTE) avgB;
                }
                else                //for bottom row
                {
                    int avgR = (int) temp[i][j].rgbtRed + (int) temp[i][j - 1].rgbtRed + (int) temp[i - 1][j].rgbtRed +
                               (int) temp[i - 1][j - 1].rgbtRed + (int) temp[i][j + 1].rgbtRed + (int) temp[i - 1][j + 1].rgbtRed;
                    int avgG = (int) temp[i][j].rgbtGreen + (int) temp[i][j - 1].rgbtGreen + (int) temp[i - 1][j].rgbtGreen +
                               (int) temp[i - 1][j - 1].rgbtGreen + (int) temp[i][j + 1].rgbtGreen + (int) temp[i - 1][j + 1].rgbtGreen;
                    int avgB = (int) temp[i][j].rgbtBlue + (int) temp[i][j - 1].rgbtBlue + (int) temp[i - 1][j].rgbtBlue +
                               (int) temp[i - 1][j - 1].rgbtBlue + (int) temp[i][j + 1].rgbtBlue + (int) temp[i - 1][j + 1].rgbtBlue;
                    avgR = round((float)avgR / 6);
                    avgG = round((float)avgG / 6);
                    avgB = round((float)avgB / 6);
                    image[i][j].rgbtRed = (BYTE) avgR;
                    image[i][j].rgbtGreen = (BYTE) avgG;
                    image[i][j].rgbtBlue = (BYTE) avgB;
                }
            }
            else if (j == 0)            //for left rwo of pixels
            {
                int avgR = (int) temp[i][j].rgbtRed + (int) temp[i][j + 1].rgbtRed + (int) temp[i - 1][j].rgbtRed +
                           (int) temp[i - 1][j + 1].rgbtRed + (int) temp[i + 1][j].rgbtRed + (int) temp[i + 1][j + 1].rgbtRed;
                int avgG = (int) temp[i][j].rgbtGreen + (int) temp[i][j + 1].rgbtGreen + (int) temp[i - 1][j].rgbtGreen +
                           (int) temp[i - 1][j + 1].rgbtGreen + (int) temp[i + 1][j].rgbtGreen + (int) temp[i + 1][j + 1].rgbtGreen;
                int avgB = (int) temp[i][j].rgbtBlue + (int) temp[i][j + 1].rgbtBlue + (int) temp[i - 1][j].rgbtBlue +
                           (int) temp[i - 1][j + 1].rgbtBlue + (int) temp[i + 1][j].rgbtBlue + (int) temp[i + 1][j + 1].rgbtBlue;
                avgR = round((float)avgR / 6);
                avgG = round((float)avgG / 6);
                avgB = round((float)avgB / 6);
                image[i][j].rgbtRed = (BYTE) avgR;
                image[i][j].rgbtGreen = (BYTE) avgG;
                image[i][j].rgbtBlue = (BYTE) avgB;
            }
            else if (j == width - 1)            //for right row of pixels
            {
                int avgR = (int) temp[i][j].rgbtRed + (int) temp[i][j - 1].rgbtRed + (int) temp[i - 1][j].rgbtRed +
                           (int) temp[i - 1][j - 1].rgbtRed + (int) temp[i + 1][j].rgbtRed + (int) temp[i + 1][j - 1].rgbtRed;
                int avgG = (int) temp[i][j].rgbtGreen + (int) temp[i][j - 1].rgbtGreen + (int) temp[i - 1][j].rgbtGreen +
                           (int) temp[i - 1][j - 1].rgbtGreen + (int) temp[i + 1][j].rgbtGreen + (int) temp[i + 1][j - 1].rgbtGreen;
                int avgB = (int) temp[i][j].rgbtBlue + (int) temp[i][j - 1].rgbtBlue + (int) temp[i - 1][j].rgbtBlue +
                           (int) temp[i - 1][j - 1].rgbtBlue + (int) temp[i + 1][j].rgbtBlue + (int) temp[i + 1][j - 1].rgbtBlue;
                avgR = round((float)avgR / 6);
                avgG = round((float)avgG / 6);
                avgB = round((float)avgB / 6);
                image[i][j].rgbtRed = (BYTE) avgR;
                image[i][j].rgbtGreen = (BYTE) avgG;
                image[i][j].rgbtBlue = (BYTE) avgB;
            }
            else                    //for rest of the image
            {
                int avgR = (int) temp[i][j].rgbtRed + (int) temp[i][j - 1].rgbtRed + (int) temp[i - 1][j].rgbtRed +
                           (int) temp[i - 1][j - 1].rgbtRed + (int) temp[i + 1][j].rgbtRed + (int) temp[i + 1][j - 1].rgbtRed +
                           (int) temp[i][j + 1].rgbtRed + (int) temp[i - 1][j + 1].rgbtRed + (int) temp[i + 1][j + 1].rgbtRed;
                int avgG = (int) temp[i][j].rgbtGreen + (int) temp[i][j - 1].rgbtGreen + (int) temp[i - 1][j].rgbtGreen +
                           (int) temp[i - 1][j - 1].rgbtGreen + (int) temp[i + 1][j].rgbtGreen + (int) temp[i + 1][j - 1].rgbtGreen +
                           (int) temp[i][j + 1].rgbtGreen + (int) temp[i - 1][j + 1].rgbtGreen + (int) temp[i + 1][j + 1].rgbtGreen;
                int avgB = (int) temp[i][j].rgbtBlue + (int) temp[i][j - 1].rgbtBlue + (int) temp[i - 1][j].rgbtBlue +
                           (int) temp[i - 1][j - 1].rgbtBlue + (int) temp[i + 1][j].rgbtBlue + (int) temp[i + 1][j - 1].rgbtBlue +
                           (int) temp[i][j + 1].rgbtBlue + (int) temp[i - 1][j + 1].rgbtBlue + (int) temp[i + 1][j + 1].rgbtBlue;
                avgR = round((float)avgR / 9);
                avgG = round((float)avgG / 9);
                avgB = round((float)avgB / 9);
                image[i][j].rgbtRed = (BYTE) avgR;
                image[i][j].rgbtGreen = (BYTE) avgG;
                image[i][j].rgbtBlue = (BYTE) avgB;
            }
        }
    }
    free(temp);
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width]) //uses the matrix to detect and give edges colour
{
    RGBTRIPLE(*temp)[width] = calloc(height, width * sizeof(RGBTRIPLE));  //Temp storage for orignal image
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
            if (i == 0)
            {
                if (j == 0)                                 //for the top right corner
                {

                    int GxR = (2 * (int) temp[i][j + 1].rgbtRed) + (int) temp[i + 1][j + 1].rgbtRed;
                    int GxG = (2 * (int) temp[i][j + 1].rgbtGreen) + (int) temp[i + 1][j + 1].rgbtGreen;
                    int GxB = (2 * (int) temp[i][j + 1].rgbtBlue) + (int) temp[i + 1][j + 1].rgbtBlue;
                    int GyR = (2 * (int) temp[i + 1][j].rgbtRed) + (int) temp[i + 1][j + 1].rgbtRed;
                    int GyG = (2 * (int) temp[i + 1][j].rgbtGreen) + (int) temp[i + 1][j + 1].rgbtGreen;
                    int GyB = (2 * (int) temp[i + 1][j].rgbtBlue) + (int) temp[i + 1][j + 1].rgbtBlue;
                    int avgR = pow(GxR, 2) + pow(GyR, 2);
                    avgR = round(sqrt(avgR));
                    int avgG = pow(GxG, 2) + pow(GyG, 2);
                    avgG = round(sqrt(avgG));
                    int avgB = pow(GxB, 2) + pow(GyB, 2);
                    avgB = round(sqrt(avgB));
                    if (avgR >= 255)
                    {
                        avgR = 255;
                    }
                    if (avgG >= 255)
                    {
                        avgG = 255;
                    }
                    if (avgB >= 255)
                    {
                        avgB = 255;
                    }
                    image[i][j].rgbtRed = (BYTE) avgR;
                    image[i][j].rgbtGreen = (BYTE) avgG;
                    image[i][j].rgbtBlue = (BYTE) avgB;
                }
                else if (j == width - 1)                //for the top left corner
                {
                    int GxR = (-2 * (int) temp[i][j - 1].rgbtRed) - (int) temp[i + 1][j - 1].rgbtRed;
                    int GxG = (-2 * (int) temp[i][j - 1].rgbtGreen) - (int) temp[i + 1][j - 1].rgbtGreen;
                    int GxB = (-2 * (int) temp[i][j - 1].rgbtBlue) - (int) temp[i + 1][j - 1].rgbtBlue;
                    int GyR = (-2 * (int) temp[i + 1][j].rgbtRed) - (int) temp[i + 1][j - 1].rgbtRed;
                    int GyG = (-2 * (int) temp[i + 1][j].rgbtGreen) - (int) temp[i + 1][j - 1].rgbtGreen;
                    int GyB = (-2 * (int) temp[i + 1][j].rgbtBlue) - (int) temp[i + 1][j - 1].rgbtBlue;
                    int avgR = pow(GxR, 2) + pow(GyR, 2);
                    avgR = round(sqrt(avgR));
                    int avgG = pow(GxG, 2) + pow(GyG, 2);
                    avgG = round(sqrt(avgG));
                    int avgB = pow(GxB, 2) + pow(GyB, 2);
                    avgB = round(sqrt(avgB));
                    if (avgR >= 255)
                    {
                        avgR = 255;
                    }
                    if (avgG >= 255)
                    {
                        avgG = 255;
                    }
                    if (avgB >= 255)
                    {
                        avgB = 255;
                    }
                    image[i][j].rgbtRed = (BYTE) avgR;
                    image[i][j].rgbtGreen = (BYTE) avgG;
                    image[i][j].rgbtBlue = (BYTE) avgB;
                }
                else                                    //for the top row
                {
                    int GxR = (-2 * (int) temp[i][j - 1].rgbtRed) - (int) temp[i + 1][j - 1].rgbtRed + (2 * (int) temp[i][j + 1].rgbtRed) +
                              (int) temp[i + 1][j + 1].rgbtRed;
                    int GxG = (-2 * (int) temp[i][j - 1].rgbtGreen) - (int) temp[i + 1][j - 1].rgbtGreen + (2 * (int) temp[i][j + 1].rgbtGreen) +
                              (int) temp[i + 1][j + 1].rgbtGreen;
                    int GxB = (-2 * (int) temp[i][j - 1].rgbtBlue) - (int) temp[i + 1][j - 1].rgbtBlue + (2 * (int) temp[i][j + 1].rgbtBlue) +
                              (int) temp[i + 1][j + 1].rgbtBlue;
                    int GyR = (2 * (int) temp[i + 1][j].rgbtRed) + (int) temp[i + 1][j - 1].rgbtRed + (int) temp[i + 1][j + 1].rgbtRed;
                    int GyG = (2 * (int) temp[i + 1][j].rgbtGreen) + (int) temp[i + 1][j - 1].rgbtGreen + (int) temp[i + 1][j + 1].rgbtGreen;
                    int GyB = (2 * (int) temp[i + 1][j].rgbtBlue) + (int) temp[i + 1][j - 1].rgbtBlue + (int) temp[i + 1][j + 1].rgbtBlue;
                    int avgR = pow(GxR, 2) + pow(GyR, 2);
                    avgR = round(sqrt(avgR));
                    int avgG = pow(GxG, 2) + pow(GyG, 2);
                    avgG = round(sqrt(avgG));
                    int avgB = pow(GxB, 2) + pow(GyB, 2);
                    avgB = round(sqrt(avgB));
                    if (avgR >= 255)
                    {
                        avgR = 255;
                    }
                    if (avgG >= 255)
                    {
                        avgG = 255;
                    }
                    if (avgB >= 255)
                    {
                        avgB = 255;
                    }
                    image[i][j].rgbtRed = (BYTE) avgR;
                    image[i][j].rgbtGreen = (BYTE) avgG;
                    image[i][j].rgbtBlue = (BYTE) avgB;
                }
            }
            else if (i == height - 1)
            {
                if (j == 0)                         //for the bottom left corner
                {
                    int GxR = (2 * (int) temp[i][j + 1].rgbtRed) + (int) temp[i - 1][j + 1].rgbtRed;
                    int GxG = (2 * (int) temp[i][j + 1].rgbtGreen) + (int) temp[i - 1][j + 1].rgbtGreen;
                    int GxB = (2 * (int) temp[i][j + 1].rgbtBlue) + (int) temp[i - 1][j + 1].rgbtBlue;
                    int GyR = (-2 * (int) temp[i - 1][j].rgbtRed) - (int) temp[i - 1][j + 1].rgbtRed;
                    int GyG = (-2 * (int) temp[i - 1][j].rgbtGreen) - (int) temp[i - 1][j + 1].rgbtGreen;
                    int GyB = (-2 * (int) temp[i - 1][j].rgbtBlue) - (int) temp[i - 1][j + 1].rgbtBlue;
                    int avgR = pow(GxR, 2) + pow(GyR, 2);
                    avgR = round(sqrt(avgR));
                    int avgG = pow(GxG, 2) + pow(GyG, 2);
                    avgG = round(sqrt(avgG));
                    int avgB = pow(GxB, 2) + pow(GyB, 2);
                    avgB = round(sqrt(avgB));
                    if (avgR >= 255)
                    {
                        avgR = 255;
                    }
                    if (avgG >= 255)
                    {
                        avgG = 255;
                    }
                    if (avgB >= 255)
                    {
                        avgB = 255;
                    }
                    image[i][j].rgbtRed = (BYTE) avgR;
                    image[i][j].rgbtGreen = (BYTE) avgG;
                    image[i][j].rgbtBlue = (BYTE) avgB;
                }
                else if (j == width - 1)                    //for the bottom right corner
                {
                    int GxR = (-2 * (int) temp[i][j - 1].rgbtRed) - (int) temp[i - 1][j - 1].rgbtRed;
                    int GxG = (-2 * (int) temp[i][j - 1].rgbtGreen) - (int) temp[i - 1][j - 1].rgbtGreen;
                    int GxB = (-2 * (int) temp[i][j - 1].rgbtBlue) - (int) temp[i - 1][j - 1].rgbtBlue;
                    int GyR = (-2 * (int) temp[i - 1][j].rgbtRed) - (int) temp[i - 1][j - 1].rgbtRed;
                    int GyG = (-2 * (int) temp[i - 1][j].rgbtGreen) - (int) temp[i - 1][j - 1].rgbtGreen;
                    int GyB = (-2 * (int) temp[i - 1][j].rgbtBlue) - (int) temp[i - 1][j - 1].rgbtBlue;
                    int avgR = pow(GxR, 2) + pow(GyR, 2);
                    avgR = round(sqrt(avgR));
                    int avgG = pow(GxG, 2) + pow(GyG, 2);
                    avgG = round(sqrt(avgG));
                    int avgB = pow(GxB, 2) + pow(GyB, 2);
                    avgB = round(sqrt(avgB));
                    if (avgR >= 255)
                    {
                        avgR = 255;
                    }
                    if (avgG >= 255)
                    {
                        avgG = 255;
                    }
                    if (avgB >= 255)
                    {
                        avgB = 255;
                    }
                    image[i][j].rgbtRed = (BYTE) avgR;
                    image[i][j].rgbtGreen = (BYTE) avgG;
                    image[i][j].rgbtBlue = (BYTE) avgB;
                }
                else                                    //for the bottom most line
                {
                    int GxR = (-2 * (int) temp[i][j - 1].rgbtRed) - (int) temp[i - 1][j - 1].rgbtRed + (2 * (int) temp[i][j + 1].rgbtRed) +
                              (int) temp[i - 1][j + 1].rgbtRed;
                    int GxG = (-2 * (int) temp[i][j - 1].rgbtGreen) - (int) temp[i - 1][j - 1].rgbtGreen + (2 * (int) temp[i][j + 1].rgbtGreen) +
                              (int) temp[i - 1][j + 1].rgbtGreen;
                    int GxB = (-2 * (int) temp[i][j - 1].rgbtBlue) - (int) temp[i - 1][j - 1].rgbtBlue + (2 * (int) temp[i][j + 1].rgbtBlue) +
                              (int) temp[i - 1][j + 1].rgbtBlue;
                    int GyR = (2 * (int) temp[i - 1][j].rgbtRed) + (int) temp[i - 1][j - 1].rgbtRed + (int) temp[i - 1][j + 1].rgbtRed;
                    int GyG = (2 * (int) temp[i - 1][j].rgbtGreen) + (int) temp[i - 1][j - 1].rgbtGreen + (int) temp[i - 1][j + 1].rgbtGreen;
                    int GyB = (2 * (int) temp[i - 1][j].rgbtBlue) + (int) temp[i - 1][j - 1].rgbtBlue + (int) temp[i - 1][j + 1].rgbtBlue;
                    int avgR = pow(GxR, 2) + pow(GyR, 2);
                    avgR = round(sqrt(avgR));
                    int avgG = pow(GxG, 2) + pow(GyG, 2);
                    avgG = round(sqrt(avgG));
                    int avgB = pow(GxB, 2) + pow(GyB, 2);
                    avgB = round(sqrt(avgB));
                    if (avgR >= 255)
                    {
                        avgR = 255;
                    }
                    if (avgG >= 255)
                    {
                        avgG = 255;
                    }
                    if (avgB >= 255)
                    {
                        avgB = 255;
                    }
                    image[i][j].rgbtRed = (BYTE) avgR;
                    image[i][j].rgbtGreen = (BYTE) avgG;
                    image[i][j].rgbtBlue = (BYTE) avgB;
                }
            }
            else if (j == 0)                                    //for the left most line
            {
                int GxR = (2 * (int) temp[i][j + 1].rgbtRed) + (int) temp[i - 1][j + 1].rgbtRed + (int) temp[i + 1][j + 1].rgbtRed;
                int GxG = (2 * (int) temp[i][j + 1].rgbtGreen) + (int) temp[i - 1][j + 1].rgbtGreen + (int) temp[i + 1][j + 1].rgbtGreen;
                int GxB = (2 * (int) temp[i][j + 1].rgbtBlue) + (int) temp[i - 1][j + 1].rgbtBlue + (int) temp[i + 1][j + 1].rgbtBlue;
                int GyR = (-2 * (int) temp[i - 1][j].rgbtRed) - (int) temp[i - 1][j + 1].rgbtRed + (2 * (int) temp[i + 1][j].rgbtRed) +
                          (int) temp[i + 1][j + 1].rgbtRed;
                int GyG = (-2 * (int) temp[i - 1][j].rgbtGreen) - (int) temp[i - 1][j + 1].rgbtGreen + (2 * (int) temp[i + 1][j].rgbtGreen) +
                          (int) temp[i + 1][j + 1].rgbtGreen;
                int GyB = (-2 * (int) temp[i - 1][j].rgbtBlue) - (int) temp[i - 1][j + 1].rgbtBlue + (2 * (int) temp[i + 1][j].rgbtBlue) +
                          (int) temp[i + 1][j + 1].rgbtBlue;
                int avgR = pow(GxR, 2) + pow(GyR, 2);
                avgR = round(sqrt(avgR));
                int avgG = pow(GxG, 2) + pow(GyG, 2);
                avgG = round(sqrt(avgG));
                int avgB = pow(GxB, 2) + pow(GyB, 2);
                avgB = round(sqrt(avgB));
                if (avgR >= 255)
                {
                    avgR = 255;
                }
                if (avgG >= 255)
                {
                    avgG = 255;
                }
                if (avgB >= 255)
                {
                    avgB = 255;
                }
                image[i][j].rgbtRed = (BYTE) avgR;
                image[i][j].rgbtGreen = (BYTE) avgG;
                image[i][j].rgbtBlue = (BYTE) avgB;
            }
            else if (j == width - 1)                        //for the right most line
            {
                //err
                int GxR = (-2 * (int) temp[i][j - 1].rgbtRed) - (int) temp[i - 1][j - 1].rgbtRed - (int) temp[i + 1][j - 1].rgbtRed;
                int GxG = (-2 * (int) temp[i][j - 1].rgbtGreen) - (int) temp[i - 1][j - 1].rgbtGreen - (int) temp[i + 1][j - 1].rgbtGreen;
                int GxB = (-2 * (int) temp[i][j - 1].rgbtBlue) - (int) temp[i - 1][j - 1].rgbtBlue - (int) temp[i + 1][j - 1].rgbtBlue;
                int GyR = (-2 * (int) temp[i - 1][j].rgbtRed) - (int) temp[i - 1][j - 1].rgbtRed + (2 * (int) temp[i + 1][j].rgbtRed) +
                          (int) temp[i + 1][j - 1].rgbtRed;
                int GyG = (-2 * (int) temp[i - 1][j].rgbtGreen) - (int) temp[i - 1][j - 1].rgbtGreen + (2 * (int) temp[i + 1][j].rgbtGreen) +
                          (int) temp[i + 1][j - 1].rgbtGreen;
                int GyB = (-2 * (int) temp[i - 1][j].rgbtBlue) - (int) temp[i - 1][j - 1].rgbtBlue + (2 * (int) temp[i + 1][j].rgbtBlue) +
                          (int) temp[i + 1][j - 1].rgbtBlue;
                int avgR = pow(GxR, 2) + pow(GyR, 2);
                avgR = round(sqrt(avgR));
                int avgG = pow(GxG, 2) + pow(GyG, 2);
                avgG = round(sqrt(avgG));
                int avgB = pow(GxB, 2) + pow(GyB, 2);
                avgB = round(sqrt(avgB));
                if (avgR >= 255)
                {
                    avgR = 255;
                }
                if (avgG >= 255)
                {
                    avgG = 255;
                }
                if (avgB >= 255)
                {
                    avgB = 255;
                }
                image[i][j].rgbtRed = (BYTE) avgR;
                image[i][j].rgbtGreen = (BYTE) avgG;
                image[i][j].rgbtBlue = (BYTE) avgB;
            }
            else                    //for the rest of the image
            {
                int GxR = (-2 * (int) temp[i][j - 1].rgbtRed) - (int) temp[i - 1][j - 1].rgbtRed - (int) temp[i + 1][j - 1].rgbtRed +
                          (2 * (int) temp[i][j + 1].rgbtRed) + (int) temp[i - 1][j + 1].rgbtRed + (int) temp[i + 1][j + 1].rgbtRed;
                int GxG = (-2 * (int) temp[i][j - 1].rgbtGreen) - (int) temp[i - 1][j - 1].rgbtGreen - (int) temp[i + 1][j - 1].rgbtGreen +
                          (2 * (int) temp[i][j + 1].rgbtGreen) + (int) temp[i - 1][j + 1].rgbtGreen + (int) temp[i + 1][j + 1].rgbtGreen;
                int GxB = (-2 * (int) temp[i][j - 1].rgbtBlue) - (int) temp[i - 1][j - 1].rgbtBlue - (int) temp[i + 1][j - 1].rgbtBlue +
                          (2 * (int) temp[i][j + 1].rgbtBlue) + (int) temp[i - 1][j + 1].rgbtBlue + (int) temp[i + 1][j + 1].rgbtBlue;
                int GyR = (-2 * (int) temp[i - 1][j].rgbtRed) - (int) temp[i - 1][j - 1].rgbtRed + (2 * (int) temp[i + 1][j].rgbtRed) +
                          (int) temp[i + 1][j - 1].rgbtRed - (int) temp[i - 1][j + 1].rgbtRed + (int) temp[i + 1][j + 1].rgbtRed;
                int GyG = (-2 * (int) temp[i - 1][j].rgbtGreen) - (int) temp[i - 1][j - 1].rgbtGreen + (2 * (int) temp[i + 1][j].rgbtGreen) +
                          (int) temp[i + 1][j - 1].rgbtGreen - (int) temp[i - 1][j + 1].rgbtGreen + (int) temp[i + 1][j + 1].rgbtGreen;
                int GyB = (-2 * (int) temp[i - 1][j].rgbtBlue) - (int) temp[i - 1][j - 1].rgbtBlue + (2 * (int) temp[i + 1][j].rgbtBlue) +
                          (int) temp[i + 1][j - 1].rgbtBlue - (int) temp[i - 1][j + 1].rgbtBlue + (int) temp[i + 1][j + 1].rgbtBlue;
                int avgR = pow(GxR, 2) + pow(GyR, 2);
                avgR = round(sqrt(avgR));
                int avgG = pow(GxG, 2) + pow(GyG, 2);
                avgG = round(sqrt(avgG));
                int avgB = pow(GxB, 2) + pow(GyB, 2);
                avgB = round(sqrt(avgB));
                if (avgR >= 255)
                {
                    avgR = 255;
                }
                if (avgG >= 255)
                {
                    avgG = 255;
                }
                if (avgB >= 255)
                {
                    avgB = 255;
                }
                image[i][j].rgbtRed = (BYTE) avgR;
                image[i][j].rgbtGreen = (BYTE) avgG;
                image[i][j].rgbtBlue = (BYTE) avgB;
            }
        }
    }
    free(temp);
    return;
}
