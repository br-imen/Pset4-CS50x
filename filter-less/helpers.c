#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        float m = 0;

        for (int j = 0; j < width; j++)
        {
            m = image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed;
            m = m / 3;
            m = round(m);
            image[i][j].rgbtBlue = m;
            image[i][j].rgbtGreen = m;
            image[i][j].rgbtRed = m;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        int m = 0;

        for (int j = 0; j < width; j++)
        {
            int RGBTBLUE = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            int RGBTGREEN = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int RGBTRED = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            if (RGBTRED > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = RGBTRED;
            }

            if (RGBTBLUE > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = RGBTBLUE;
            }

            if (RGBTGREEN > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = RGBTGREEN;
            }
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < round(width / 2); j++)
        {
            RGBTRIPLE x = image[i][j];
            image [i][j] = image [i][width - 1 - j];
            image [i][width - 1 - j] = x;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy [height] [width];
// copying the image in copy[m][n]
    for (int m = 0; m < height; m++)
    {
        for (int n = 0; n < width; n++)
        {
            copy [m][n] = image [m][n];
        }
    }


// creating a loup goes around the copy[i][j] position
    int div;
    float total_red, total_blue, total_green;

    for (int i = 1; i <= height; i++)
    {
        for (int j = 1; j <= width; j++)
        {
            div = 0;
            total_red = 0;
            total_blue = 0;
            total_green = 0;

            for (int k = i - 1; k <= i + 1; k++)
            {

                // if (k == height || k < 0)
                // {
                //     break;
                // }


                for (int l = j - 1; l <= j + 1; l++)
                {

                    if (k < height && k > 0 && l < width && l > 0)
                    {
                        div++;

                        total_red = total_red + copy[k][l].rgbtRed;

                        total_blue = total_blue + copy[k][l].rgbtBlue;

                        total_green = total_green + copy[k][l].rgbtGreen;

                    }

                }

                image[i][j].rgbtRed =  round(total_red / div);

                image[i][j].rgbtBlue = round(total_blue / div);

                image[i][j].rgbtGreen = round(total_green / div);

            }

        }

    }


// // creating a loup goes around the copy[i][j] position

//      int div;

//      float total_red, total_blue, total_green;

//      for ( int i = 1; i <= height; i++)

//      {

//          for (int j = 1; j <= width; j++)

//          {
//             div = 0;

//             total_red = 0;

//             total_blue = 0;

//             total_green = 0;

//             for (int k = i-1; k <= i+1; k++)

//             {
//                 if (k == height)

//                 {


//                     break;

//                 }

//                 for (int l = j-1; l <= j+1; l++)

//                 {

//                     if (l == width)

//                     {

//                         break;

//                     }

//                     div++;

//                     total_red = total_red + copy[k][l].rgbtRed;
//                     total_blue = total_blue + copy[k][l].rgbtBlue;
//                     total_green = total_green + copy[k][l].rgbtGreen;

//                 }
//              }

//              image[i][j].rgbtRed =  round(total_red / div);
//              image[i][j].rgbtBlue = round(total_blue / div);
//              image[i][j].rgbtGreen = round(total_green / div);
//          }
//      }
}
