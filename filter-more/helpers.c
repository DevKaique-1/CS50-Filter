#include "helpers.h"
#include "math.h"
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int x = 0; x < height; x++)
    {
        for(int y = 0; y < width; y++)
        {
            int r = image[x][y].rgbtRed;
            int b = image[x][y].rgbtBlue;
            int g = image[x][y].rgbtGreen;

            int avarege = round((r+g+b) / 3.0);

            image[x][y].rgbtRed = avarege;
            image[x][y].rgbtBlue = avarege;
            image[x][y].rgbtGreen = avarege;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
      for (int x = 0; x < height; x++)
    {
        for(int y = 0, lit = width / 2; y < lit; y++)
        {
            RGBTRIPLE temp;
            temp = image[x][y];
            image[x][y] = image[x][width -1 -y];
            image[x][width -1 -y] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    int avarege_red;
    int avarege_blue;
    int avarege_green;

    for(int a = 0; a < height; a++)
    {
        for(int b = 0; b < width; b++)
        {
            copy[a][b] = image[a][b];
        }
    }
    for(int x = 0; x < height; x++)
    {
        for(int y = 0; y < width; y++)
        {
            int sumred = 0;
            int sumblue = 0;
            int sumgreen = 0;
            int count = 0;

            for(int j = -1; j <= 1; j++)
            {
                for(int k = -1; k <= 1; k++)
                {
                    int line =  x+j;
                    int colun = y+k;

                    if(line >= 0 && line < height && colun >= 0 && colun < width)
                    {

                        sumred += copy[line][colun].rgbtRed;
                        sumblue += copy[line][colun].rgbtBlue;
                        sumgreen += copy[line][colun].rgbtGreen;

                        count++;
                    }

                }
            }

            avarege_red = round((float)sumred / count);
            avarege_blue = round((float)sumblue / count);
            avarege_green = round((float)sumgreen / count);

            image[x][y].rgbtRed = avarege_red;
            image[x][y].rgbtBlue = avarege_blue;
            image[x][y].rgbtGreen = avarege_green;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int Gx[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    int Gy[3][3] =
    {
        {-1, -2, -1},
        { 0, 0, 0 },
        { 1, 2, 1 }
    };
    RGBTRIPLE copy[height][width];

    for(int a = 0; a < height; a++)
    {
        for(int b = 0; b < width; b++)
        {
            copy[a][b] = image[a][b];
        }
    }

    for(int x = 0; x < height; x++)
    {
        for(int y = 0; y < width; y++)
        {
            int redgx = 0;
            int bluegx = 0;
            int greengx = 0;
            int redgy = 0;
            int bluegy = 0;
            int greengy = 0;

            for(int j = -1; j <= 1; j++)
            {
                for(int k = -1; k <= 1; k++)
                {
                    int line =  x+j;
                    int colun = y+k;
                    if (line >= 0 && line < height && colun >= 0 && colun < width)
                    {
                        redgx += copy[line][colun].rgbtRed * Gx[j+1][k+1];
                        redgy += copy[line][colun].rgbtRed * Gy[j+1][k+1];
                        bluegx += copy[line][colun].rgbtBlue * Gx[j+1][k+1];
                        bluegy += copy[line][colun].rgbtBlue * Gy[j+1][k+1];
                        greengx += copy[line][colun].rgbtGreen * Gx[j+1][k+1];
                        greengy += copy[line][colun].rgbtGreen * Gy[j+1][k+1];
                    }

                }

            }

            int red = round(sqrt(redgx * redgx + redgy * redgy));
            int blue = round(sqrt(bluegx * bluegx + bluegy * bluegy));
            int green = round(sqrt(greengx * greengx + greengy * greengy));

            if (red > 255)
            {
                red = 255;
            }
            if (blue > 255)
            {
                blue = 255;
            }
            if (green > 255)
            {
                green = 255;
            }

            image[x][y].rgbtRed = red;
            image[x][y].rgbtBlue = blue;
            image[x][y].rgbtGreen = green;
        }
    }

    return;

}

