#include "helpers.h"
#include <math.h>

int min(int lhs, int rhs);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            RGBTRIPLE *cur_RGB = &image[h][w];
            BYTE new_colour =
                round((cur_RGB->rgbtBlue + cur_RGB->rgbtGreen + cur_RGB->rgbtRed) / 3.0);
            cur_RGB->rgbtBlue = new_colour;
            cur_RGB->rgbtGreen = new_colour;
            cur_RGB->rgbtRed = new_colour;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width / 2; w++)
        {
            RGBTRIPLE cur_RGB = image[h][w];
            image[h][w] = image[h][width - 1 - w];
            image[h][width - 1 - w] = cur_RGB;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            copy[h][w] = image[h][w];
        }
    }

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int cur_h = h - 1;
            if (h == 0)
            {
                cur_h = h;
            }
            int b = 0;
            int g = 0;
            int r = 0;
            int count = 0;

            while (cur_h < height && cur_h < h + 2)
            {
                int cur_w = w - 1;
                if (w == 0)
                {
                    cur_w = w;
                }
                while (cur_w < width && cur_w < w + 2)
                {
                    b += copy[cur_h][cur_w].rgbtBlue;
                    g += copy[cur_h][cur_w].rgbtGreen;
                    r += copy[cur_h][cur_w].rgbtRed;
                    count++;
                    cur_w++;
                }
                cur_h++;
            }
            image[h][w].rgbtBlue = round(b * 1.0 / count);
            image[h][w].rgbtGreen = round(g * 1.0 / count);
            image[h][w].rgbtRed = round(r * 1.0 / count);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int Gx[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    int Gy[9] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
    RGBTRIPLE copy[height][width];
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            copy[h][w] = image[h][w];
        }
    }

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int cur_h = h - 1;

            int bx = 0;
            int gx = 0;
            int rx = 0;
            int by = 0;
            int gy = 0;
            int ry = 0;
            int index = 0;

            while (cur_h <= height && cur_h < h + 2)
            {
                int cur_w = w - 1;

                while (cur_w <= width && cur_w < w + 2)
                {
                    if (cur_w >= 0 && cur_h >= 0 && cur_w < width && cur_h < height)
                    {
                        bx += (copy[cur_h][cur_w].rgbtBlue * Gx[index]);
                        gx += (copy[cur_h][cur_w].rgbtGreen * Gx[index]);
                        rx += (copy[cur_h][cur_w].rgbtRed * Gx[index]);
                        by += (copy[cur_h][cur_w].rgbtBlue * Gy[index]);
                        gy += (copy[cur_h][cur_w].rgbtGreen * Gy[index]);
                        ry += (copy[cur_h][cur_w].rgbtRed * Gy[index]);
                    }

                    cur_w++;
                    index++;
                }
                cur_h++;
            }
            int final_b = min(round(sqrt(bx * bx + by * by)), 255);
            int final_g = min(round(sqrt(gx * gx + gy * gy)), 255);
            int final_r = min(round(sqrt(rx * rx + ry * ry)), 255);

            image[h][w].rgbtBlue = final_b;
            image[h][w].rgbtGreen = final_g;
            image[h][w].rgbtRed = final_r;
        }
    }

    return;
}
int min(int lhs, int rhs)
{
    return lhs > rhs ? rhs : lhs;
}
