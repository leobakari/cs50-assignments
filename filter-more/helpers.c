#include "helpers.h"
#include <math.h>
#include <stdio.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    uint8_t rgb_avg = 0;
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            rgb_avg = round((float) (image[row][col].rgbtRed + image[row][col].rgbtBlue + image[row][col].rgbtGreen) / 3);
            image[row][col].rgbtRed = rgb_avg;
            image[row][col].rgbtBlue = rgb_avg;
            image[row][col].rgbtGreen = rgb_avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE row_reversed_copy[width];
    for (int row = 0; row < height; row++)
    {
        for (int col_copy = 0; col_copy < width; col_copy++)
        {
            row_reversed_copy[col_copy] = image[row][width - col_copy - 1];
        }
        for (int col_paste = 0; col_paste < width; col_paste++)
        {
            image[row][col_paste] = row_reversed_copy[col_paste];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    // horrific implementation - did not come up with a better solution so far..
    RGBTRIPLE image_blured[height][width];
    int temp_color = 0;
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            if (row == 0)
            {
                if (col == 0)
                {
                    // no left outer - no above
                    temp_color = round(((float) image[row][col].rgbtRed + image[row][col + 1].rgbtRed +
                                        image[row + 1][col].rgbtRed + image[row + 1][col + 1].rgbtRed) /
                                       (float) 4);
                    image_blured[row][col].rgbtRed = temp_color;

                    temp_color = round(((float) image[row][col].rgbtGreen + image[row][col + 1].rgbtGreen +
                                        image[row + 1][col].rgbtGreen + image[row + 1][col + 1].rgbtGreen) /
                                       (float) 4);
                    image_blured[row][col].rgbtGreen = temp_color;

                    temp_color = round(((float) image[row][col].rgbtBlue + image[row][col + 1].rgbtBlue +
                                        image[row + 1][col].rgbtBlue + image[row + 1][col + 1].rgbtBlue) /
                                       (float) 4);
                    image_blured[row][col].rgbtBlue = temp_color;
                }
                else if (col == width - 1)
                {
                    // no right outer - no above
                    temp_color = round(((float) image[row][col - 1].rgbtRed + image[row][col].rgbtRed +
                                        image[row + 1][col - 1].rgbtRed + image[row + 1][col].rgbtRed) /
                                       (float) 4);
                    image_blured[row][col].rgbtRed = temp_color;

                    temp_color = round(((float) image[row][col - 1].rgbtGreen + image[row][col].rgbtGreen +
                                        image[row + 1][col - 1].rgbtGreen + image[row + 1][col].rgbtGreen) /
                                       (float) 4);
                    image_blured[row][col].rgbtGreen = temp_color;

                    temp_color = round(((float) image[row][col - 1].rgbtBlue + image[row][col].rgbtBlue +
                                        image[row + 1][col - 1].rgbtBlue + image[row + 1][col].rgbtBlue) /
                                       (float) 4);
                    image_blured[row][col].rgbtBlue = temp_color;
                }
                else
                {
                    // Normal - no above
                    temp_color =
                        round(((float) image[row][col - 1].rgbtRed + image[row][col].rgbtRed + image[row][col + 1].rgbtRed +
                               image[row + 1][col - 1].rgbtRed + image[row + 1][col].rgbtRed + image[row + 1][col + 1].rgbtRed) /
                              (float) 6);
                    image_blured[row][col].rgbtRed = temp_color;

                    temp_color = round(((float) image[row][col - 1].rgbtGreen + image[row][col].rgbtGreen +
                                        image[row][col + 1].rgbtGreen + image[row + 1][col - 1].rgbtGreen +
                                        image[row + 1][col].rgbtGreen + image[row + 1][col + 1].rgbtGreen) /
                                       6);
                    image_blured[row][col].rgbtGreen = temp_color;

                    temp_color =
                        round(((float) image[row][col - 1].rgbtBlue + image[row][col].rgbtBlue + image[row][col + 1].rgbtBlue +
                               image[row + 1][col - 1].rgbtBlue + image[row + 1][col].rgbtBlue + image[row + 1][col + 1].rgbtBlue) /
                              6);
                    image_blured[row][col].rgbtBlue = temp_color;
                }
            }

            else if (row == height - 1)
            {
                if (col == 0)
                {
                    // no left outer - no below
                    temp_color = round(((float) image[row - 1][col].rgbtRed + image[row - 1][col + 1].rgbtRed +
                                        image[row][col].rgbtRed + image[row][col + 1].rgbtRed) /
                                       (float) 4);
                    image_blured[row][col].rgbtRed = temp_color;

                    temp_color = round(((float) image[row - 1][col].rgbtGreen + image[row - 1][col + 1].rgbtGreen +
                                        image[row][col].rgbtGreen + image[row][col + 1].rgbtGreen) /
                                       (float) 4);
                    image_blured[row][col].rgbtGreen = temp_color;

                    temp_color = round(((float) image[row - 1][col].rgbtBlue + image[row - 1][col + 1].rgbtBlue +
                                        image[row][col].rgbtBlue + image[row][col + 1].rgbtBlue) /
                                       (float) 4);
                    image_blured[row][col].rgbtBlue = temp_color;
                }
                else if (col == width - 1)
                {
                    // no right outer - no below
                    temp_color = round(((float) image[row - 1][col - 1].rgbtRed + image[row - 1][col].rgbtRed +
                                        image[row][col - 1].rgbtRed + image[row][col].rgbtRed) /
                                       (float) 4);
                    image_blured[row][col].rgbtRed = temp_color;

                    temp_color = round(((float) image[row - 1][col - 1].rgbtGreen + image[row - 1][col].rgbtGreen +
                                        image[row][col - 1].rgbtGreen + image[row][col].rgbtGreen) /
                                       (float) 4);
                    image_blured[row][col].rgbtGreen = temp_color;

                    temp_color = round(((float) image[row - 1][col - 1].rgbtBlue + image[row - 1][col].rgbtBlue +
                                        image[row][col - 1].rgbtBlue + image[row][col].rgbtBlue) /
                                       (float) 4);
                    image_blured[row][col].rgbtBlue = temp_color;
                }
                else
                {
                    // Normal - no below
                    temp_color = round(((float) image[row - 1][col - 1].rgbtRed + image[row - 1][col].rgbtRed +
                                        image[row - 1][col + 1].rgbtRed + image[row][col - 1].rgbtRed + image[row][col].rgbtRed +
                                        image[row][col + 1].rgbtRed) /
                                       (float) 6);
                    image_blured[row][col].rgbtRed = temp_color;

                    temp_color = round(((float) image[row - 1][col - 1].rgbtGreen + image[row - 1][col].rgbtGreen +
                                        image[row - 1][col + 1].rgbtGreen + image[row][col - 1].rgbtGreen +
                                        image[row][col].rgbtGreen + image[row][col + 1].rgbtGreen) /
                                       (float) 6);
                    image_blured[row][col].rgbtGreen = temp_color;

                    temp_color = round(((float) image[row - 1][col - 1].rgbtBlue + image[row - 1][col].rgbtBlue +
                                        image[row - 1][col + 1].rgbtBlue + image[row][col - 1].rgbtBlue + image[row][col].rgbtBlue +
                                        image[row][col + 1].rgbtBlue) /
                                       (float) 6);
                    image_blured[row][col].rgbtBlue = temp_color;
                }
            }
            else
            {
                if (col == 0)
                {
                    // no left outer
                    temp_color =
                        round(((float) image[row - 1][col].rgbtRed + image[row - 1][col + 1].rgbtRed + image[row][col].rgbtRed +
                               image[row][col + 1].rgbtRed + image[row + 1][col].rgbtRed + image[row + 1][col + 1].rgbtRed) /
                              (float) 6);
                    image_blured[row][col].rgbtRed = temp_color;

                    temp_color = round(((float) image[row - 1][col].rgbtGreen + image[row - 1][col + 1].rgbtGreen +
                                        image[row][col].rgbtGreen + image[row][col + 1].rgbtGreen + image[row + 1][col].rgbtGreen +
                                        image[row + 1][col + 1].rgbtGreen) /
                                       (float) 6);
                    image_blured[row][col].rgbtGreen = temp_color;

                    temp_color =
                        round(((float) image[row - 1][col].rgbtBlue + image[row - 1][col + 1].rgbtBlue + image[row][col].rgbtBlue +
                               image[row][col + 1].rgbtBlue + image[row + 1][col].rgbtBlue + image[row + 1][col + 1].rgbtBlue) /
                              (float) 6);
                    image_blured[row][col].rgbtBlue = temp_color;
                }
                else if (col == width - 1)
                {
                    // no right outer
                    temp_color =
                        round(((float) image[row - 1][col - 1].rgbtRed + image[row - 1][col].rgbtRed + image[row][col - 1].rgbtRed +
                               image[row][col].rgbtRed + image[row + 1][col - 1].rgbtRed + image[row + 1][col].rgbtRed) /
                              (float) 6);
                    image_blured[row][col].rgbtRed = temp_color;

                    temp_color = round(((float) image[row - 1][col - 1].rgbtGreen + image[row - 1][col].rgbtGreen +
                                        image[row][col - 1].rgbtGreen + image[row][col].rgbtGreen +
                                        image[row + 1][col - 1].rgbtGreen + image[row + 1][col].rgbtGreen) /
                                       (float) 6);
                    image_blured[row][col].rgbtGreen = temp_color;

                    temp_color = round(((float) image[row - 1][col - 1].rgbtBlue + image[row - 1][col].rgbtBlue +
                                        image[row][col - 1].rgbtBlue + image[row][col].rgbtBlue + image[row + 1][col - 1].rgbtBlue +
                                        image[row + 1][col].rgbtBlue) /
                                       (float) 6);
                    image_blured[row][col].rgbtBlue = temp_color;
                }
                else
                {
                    // Normal
                    temp_color = round(((float) image[row - 1][col - 1].rgbtRed + image[row - 1][col].rgbtRed +
                                        image[row - 1][col + 1].rgbtRed + image[row][col - 1].rgbtRed + image[row][col].rgbtRed +
                                        image[row][col + 1].rgbtRed + image[row + 1][col - 1].rgbtRed +
                                        image[row + 1][col].rgbtRed + image[row + 1][col + 1].rgbtRed) /
                                       (float) 9);
                    image_blured[row][col].rgbtRed = temp_color;

                    temp_color =
                        round(((float) image[row - 1][col - 1].rgbtGreen + image[row - 1][col].rgbtGreen +
                               image[row - 1][col + 1].rgbtGreen + image[row][col - 1].rgbtGreen + image[row][col].rgbtGreen +
                               image[row][col + 1].rgbtGreen + image[row + 1][col - 1].rgbtGreen + image[row + 1][col].rgbtGreen +
                               image[row + 1][col + 1].rgbtGreen) /
                              (float) 9);
                    image_blured[row][col].rgbtGreen = temp_color;

                    temp_color = round(((float) image[row - 1][col - 1].rgbtBlue + image[row - 1][col].rgbtBlue +
                                        image[row - 1][col + 1].rgbtBlue + image[row][col - 1].rgbtBlue + image[row][col].rgbtBlue +
                                        image[row][col + 1].rgbtBlue + image[row + 1][col - 1].rgbtBlue +
                                        image[row + 1][col].rgbtBlue + image[row + 1][col + 1].rgbtBlue) /
                                       (float) 9);
                    image_blured[row][col].rgbtBlue = temp_color;
                }
            }
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = image_blured[i][j];
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // horrific implementation - did not come up with a better solution so far..
    RGBTRIPLE image_edged[height][width];
    float temp_color_gx = 0;
    float temp_color_gy = 0;
    int temp_color = 0;

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            if (row == 0)
            {
                if (col == 0)
                {
                    // no left outer - no above
                    temp_color_gx = (image[row][col].rgbtRed * 0) + (image[row][col + 1].rgbtRed * 2) +
                                    (image[row + 1][col].rgbtRed * 0) + (image[row + 1][col + 1].rgbtRed * 1);
                    temp_color_gy = (image[row][col].rgbtRed * 0) + (image[row][col + 1].rgbtRed * 0) +
                                    (image[row + 1][col].rgbtRed * 2) + (image[row + 1][col + 1].rgbtRed * 1);
                    temp_color = round(sqrt((float) ((float) temp_color_gx * (float) temp_color_gx) +
                                            (float) ((float) temp_color_gy * (float) temp_color_gy)));
                    if (temp_color > 255)
                    {
                        temp_color = 255;
                    }
                    image_edged[row][col].rgbtRed = temp_color;

                    temp_color_gx = (image[row][col].rgbtGreen * 0) + (image[row][col + 1].rgbtGreen * 2) +
                                    (image[row + 1][col].rgbtGreen * 0) + (image[row + 1][col + 1].rgbtGreen * 1);
                    temp_color_gy = (image[row][col].rgbtGreen * 0) + (image[row][col + 1].rgbtGreen * 0) +
                                    (image[row + 1][col].rgbtGreen * 2) + (image[row + 1][col + 1].rgbtGreen * 1);
                    temp_color = round(sqrt((float) ((float) temp_color_gx * (float) temp_color_gx) +
                                            (float) ((float) temp_color_gy * (float) temp_color_gy)));
                    if (temp_color > 255)
                    {
                        temp_color = 255;
                    }
                    image_edged[row][col].rgbtGreen = temp_color;

                    temp_color_gx = (image[row][col].rgbtBlue * 0) + (image[row][col + 1].rgbtBlue * 2) +
                                    (image[row + 1][col].rgbtBlue * 0) + (image[row + 1][col + 1].rgbtBlue * 1);
                    temp_color_gy = (image[row][col].rgbtBlue * 0) + (image[row][col + 1].rgbtBlue * 0) +
                                    (image[row + 1][col].rgbtBlue * 2) + (image[row + 1][col + 1].rgbtBlue * 1);
                    temp_color = round(sqrt((float) ((float) temp_color_gx * (float) temp_color_gx) +
                                            (float) ((float) temp_color_gy * (float) temp_color_gy)));
                    if (temp_color > 255)
                    {
                        temp_color = 255;
                    }
                    image_edged[row][col].rgbtBlue = temp_color;
                }
                else if (col == width - 1)
                {
                    // no right outer - no above
                    temp_color_gx = (image[row][col - 1].rgbtRed * -2) + (image[row][col].rgbtRed * 0) +
                                    (image[row + 1][col - 1].rgbtRed * -1) + (image[row + 1][col].rgbtRed * 0);
                    temp_color_gy = (image[row][col - 1].rgbtRed * 0) + (image[row][col].rgbtRed * 0) +
                                    (image[row + 1][col - 1].rgbtRed * 1) + (image[row + 1][col].rgbtRed * 2);
                    temp_color = round(sqrt((float) ((float) temp_color_gx * (float) temp_color_gx) +
                                            (float) ((float) temp_color_gy * (float) temp_color_gy)));
                    if (temp_color > 255)
                    {
                        temp_color = 255;
                    }
                    image_edged[row][col].rgbtRed = temp_color;

                    temp_color_gx = (image[row][col - 1].rgbtGreen * -2) + (image[row][col].rgbtGreen * 0) +
                                    (image[row + 1][col - 1].rgbtGreen * -1) + (image[row + 1][col].rgbtGreen * 0);
                    temp_color_gy = (image[row][col - 1].rgbtGreen * 0) + (image[row][col].rgbtGreen * 0) +
                                    (image[row + 1][col - 1].rgbtGreen * 1) + (image[row + 1][col].rgbtGreen * 2);
                    temp_color = round(sqrt((float) ((float) temp_color_gx * (float) temp_color_gx) +
                                            (float) ((float) temp_color_gy * (float) temp_color_gy)));
                    if (temp_color > 255)
                    {
                        temp_color = 255;
                    }
                    image_edged[row][col].rgbtGreen = temp_color;

                    temp_color_gx = (image[row][col - 1].rgbtBlue * -2) + (image[row][col].rgbtBlue * 0) +
                                    (image[row + 1][col - 1].rgbtBlue * -1) + (image[row + 1][col].rgbtBlue * 0);
                    temp_color_gy = (image[row][col - 1].rgbtBlue * 0) + (image[row][col].rgbtBlue * 0) +
                                    (image[row + 1][col - 1].rgbtBlue * 1) + (image[row + 1][col].rgbtBlue * 2);
                    temp_color = round(sqrt((float) ((float) temp_color_gx * (float) temp_color_gx) +
                                            (float) ((float) temp_color_gy * (float) temp_color_gy)));
                    if (temp_color > 255)
                    {
                        temp_color = 255;
                    }
                    image_edged[row][col].rgbtBlue = temp_color;
                }
                else
                {
                    // Normal - no above
                    temp_color_gx = (image[row][col - 1].rgbtRed * -2) + (image[row][col].rgbtRed * 0) +
                                    (image[row][col + 1].rgbtRed * 2) + (image[row + 1][col - 1].rgbtRed * -1) +
                                    (image[row + 1][col].rgbtRed * 0) + (image[row + 1][col + 1].rgbtRed * 1);
                    temp_color_gy = (image[row][col - 1].rgbtRed * 0) + (image[row][col].rgbtRed * 0) +
                                    (image[row][col + 1].rgbtRed * 0) + (image[row + 1][col - 1].rgbtRed * 1) +
                                    (image[row + 1][col].rgbtRed * 2) + (image[row + 1][col + 1].rgbtRed * 1);
                    temp_color = round(sqrt((float) ((float) temp_color_gx * (float) temp_color_gx) +
                                            (float) ((float) temp_color_gy * (float) temp_color_gy)));
                    if (temp_color > 255)
                    {
                        temp_color = 255;
                    }
                    image_edged[row][col].rgbtRed = temp_color;

                    temp_color_gx = (image[row][col - 1].rgbtGreen * -2) + (image[row][col].rgbtGreen * 0) +
                                    (image[row][col + 1].rgbtGreen * 2) + (image[row + 1][col - 1].rgbtGreen * -1) +
                                    (image[row + 1][col].rgbtGreen * 0) + (image[row + 1][col + 1].rgbtGreen * 1);
                    temp_color_gy = (image[row][col - 1].rgbtGreen * 0) + (image[row][col].rgbtGreen * 0) +
                                    (image[row][col + 1].rgbtGreen * 0) + (image[row + 1][col - 1].rgbtGreen * 1) +
                                    (image[row + 1][col].rgbtGreen * 2) + (image[row + 1][col + 1].rgbtGreen * 1);
                    temp_color = round(sqrt((float) ((float) temp_color_gx * (float) temp_color_gx) +
                                            (float) ((float) temp_color_gy * (float) temp_color_gy)));
                    if (temp_color > 255)
                    {
                        temp_color = 255;
                    }
                    image_edged[row][col].rgbtGreen = temp_color;

                    temp_color_gx = (image[row][col - 1].rgbtBlue * -2) + (image[row][col].rgbtBlue * 0) +
                                    (image[row][col + 1].rgbtBlue * 2) + (image[row + 1][col - 1].rgbtBlue * -1) +
                                    (image[row + 1][col].rgbtBlue * 0) + (image[row + 1][col + 1].rgbtBlue * 1);
                    temp_color_gy = (image[row][col - 1].rgbtBlue * 0) + (image[row][col].rgbtBlue * 0) +
                                    (image[row][col + 1].rgbtBlue * 0) + (image[row + 1][col - 1].rgbtBlue * 1) +
                                    (image[row + 1][col].rgbtBlue * 2) + (image[row + 1][col + 1].rgbtBlue * 1);
                    temp_color = round(sqrt((float) ((float) temp_color_gx * (float) temp_color_gx) +
                                            (float) ((float) temp_color_gy * (float) temp_color_gy)));
                    if (temp_color > 255)
                    {
                        temp_color = 255;
                    }
                    image_edged[row][col].rgbtBlue = temp_color;
                }
            }

            else if (row == height - 1)
            {
                if (col == 0)
                {
                    // no left outer - no below
                    temp_color_gx = (image[row - 1][col].rgbtRed * 0) + (image[row - 1][col + 1].rgbtRed * 1) +
                                    (image[row][col].rgbtRed * 0) + (image[row][col + 1].rgbtRed * 2);
                    temp_color_gy = (image[row - 1][col].rgbtRed * -2) + (image[row - 1][col + 1].rgbtRed * -1) +
                                    (image[row][col].rgbtRed * 0) + (image[row][col + 1].rgbtRed * 0);
                    temp_color = round(sqrt((float) ((float) temp_color_gx * (float) temp_color_gx) +
                                            (float) ((float) temp_color_gy * (float) temp_color_gy)));
                    if (temp_color > 255)
                    {
                        temp_color = 255;
                    }
                    image_edged[row][col].rgbtRed = temp_color;

                    temp_color_gx = (image[row - 1][col].rgbtGreen * 0) + (image[row - 1][col + 1].rgbtGreen * 1) +
                                    (image[row][col].rgbtGreen * 0) + (image[row][col + 1].rgbtGreen * 2);
                    temp_color_gy = (image[row - 1][col].rgbtGreen * -2) + (image[row - 1][col + 1].rgbtGreen * -1) +
                                    (image[row][col].rgbtGreen * 0) + (image[row][col + 1].rgbtGreen * 0);
                    temp_color = round(sqrt((float) ((float) temp_color_gx * (float) temp_color_gx) +
                                            (float) ((float) temp_color_gy * (float) temp_color_gy)));
                    if (temp_color > 255)
                    {
                        temp_color = 255;
                    }
                    image_edged[row][col].rgbtGreen = temp_color;

                    temp_color_gx = (image[row - 1][col].rgbtBlue * 0) + (image[row - 1][col + 1].rgbtBlue * 1) +
                                    (image[row][col].rgbtBlue * 0) + (image[row][col + 1].rgbtBlue * 2);
                    temp_color_gy = (image[row - 1][col].rgbtBlue * -2) + (image[row - 1][col + 1].rgbtBlue * -1) +
                                    (image[row][col].rgbtBlue * 0) + (image[row][col + 1].rgbtBlue * 0);
                    temp_color = round(sqrt((float) ((float) temp_color_gx * (float) temp_color_gx) +
                                            (float) ((float) temp_color_gy * (float) temp_color_gy)));
                    if (temp_color > 255)
                    {
                        temp_color = 255;
                    }
                    image_edged[row][col].rgbtBlue = temp_color;
                }
                else if (col == width - 1)
                {
                    // no right outer - no below
                    temp_color_gx = (image[row - 1][col - 1].rgbtRed * -1) + (image[row - 1][col].rgbtRed * 0) +
                                    (image[row][col - 1].rgbtRed * -2) + (image[row][col].rgbtRed * 0);
                    temp_color_gy = (image[row - 1][col - 1].rgbtRed * -1) + (image[row - 1][col].rgbtRed * -2) +
                                    (image[row][col - 1].rgbtRed * 0) + (image[row][col].rgbtRed * 0);
                    temp_color = round(sqrt((float) ((float) temp_color_gx * (float) temp_color_gx) +
                                            (float) ((float) temp_color_gy * (float) temp_color_gy)));
                    if (temp_color > 255)
                    {
                        temp_color = 255;
                    }
                    image_edged[row][col].rgbtRed = temp_color;

                    temp_color_gx = (image[row - 1][col - 1].rgbtGreen * -1) + (image[row - 1][col].rgbtGreen * 0) +
                                    (image[row][col - 1].rgbtGreen * -2) + (image[row][col].rgbtGreen * 0);
                    temp_color_gy = (image[row - 1][col - 1].rgbtGreen * -1) + (image[row - 1][col].rgbtGreen * -2) +
                                    (image[row][col - 1].rgbtGreen * 0) + (image[row][col].rgbtGreen * 0);
                    temp_color = round(sqrt((float) ((float) temp_color_gx * (float) temp_color_gx) +
                                            (float) ((float) temp_color_gy * (float) temp_color_gy)));
                    if (temp_color > 255)
                    {
                        temp_color = 255;
                    }
                    image_edged[row][col].rgbtGreen = temp_color;

                    temp_color_gx = (image[row - 1][col - 1].rgbtBlue * -1) + (image[row - 1][col].rgbtBlue * 0) +
                                    (image[row][col - 1].rgbtBlue * -2) + (image[row][col].rgbtBlue * 0);
                    temp_color_gy = (image[row - 1][col - 1].rgbtBlue * -1) + (image[row - 1][col].rgbtBlue * -2) +
                                    (image[row][col - 1].rgbtBlue * 0) + (image[row][col].rgbtBlue * 0);
                    temp_color = round(sqrt((float) ((float) temp_color_gx * (float) temp_color_gx) +
                                            (float) ((float) temp_color_gy * (float) temp_color_gy)));
                    if (temp_color > 255)
                    {
                        temp_color = 255;
                    }
                    image_edged[row][col].rgbtBlue = temp_color;
                }
                else
                {
                    // Normal - no below
                    temp_color_gx = (image[row - 1][col - 1].rgbtRed * -1) + (image[row - 1][col].rgbtRed * 0) +
                                    (image[row - 1][col + 1].rgbtRed * 1) + (image[row][col - 1].rgbtRed * -2) +
                                    (image[row][col].rgbtRed * 0) + (image[row][col + 1].rgbtRed * 2);
                    temp_color_gy = (image[row - 1][col - 1].rgbtRed * -1) + (image[row - 1][col].rgbtRed * -2) +
                                    (image[row - 1][col + 1].rgbtRed * -1) + (image[row][col - 1].rgbtRed * 0) +
                                    (image[row][col].rgbtRed * 0) + (image[row][col + 1].rgbtRed * 0);
                    temp_color = round(sqrt((float) ((float) temp_color_gx * (float) temp_color_gx) +
                                            (float) ((float) temp_color_gy * (float) temp_color_gy)));
                    if (temp_color > 255)
                    {
                        temp_color = 255;
                    }
                    image_edged[row][col].rgbtRed = temp_color;

                    temp_color_gx = (image[row - 1][col - 1].rgbtGreen * -1) + (image[row - 1][col].rgbtGreen * 0) +
                                    (image[row - 1][col + 1].rgbtGreen * 1) + (image[row][col - 1].rgbtGreen * -2) +
                                    (image[row][col].rgbtGreen * 0) + (image[row][col + 1].rgbtGreen * 2);
                    temp_color_gy = (image[row - 1][col - 1].rgbtGreen * -1) + (image[row - 1][col].rgbtGreen * -2) +
                                    (image[row - 1][col + 1].rgbtGreen * -1) + (image[row][col - 1].rgbtGreen * 0) +
                                    (image[row][col].rgbtGreen * 0) + (image[row][col + 1].rgbtGreen * 0);
                    temp_color = round(sqrt((float) ((float) temp_color_gx * (float) temp_color_gx) +
                                            (float) ((float) temp_color_gy * (float) temp_color_gy)));
                    if (temp_color > 255)
                    {
                        temp_color = 255;
                    }
                    image_edged[row][col].rgbtGreen = temp_color;

                    temp_color_gx = (image[row - 1][col - 1].rgbtBlue * -1) + (image[row - 1][col].rgbtBlue * 0) +
                                    (image[row - 1][col + 1].rgbtBlue * 1) + (image[row][col - 1].rgbtBlue * -2) +
                                    (image[row][col].rgbtBlue * 0) + (image[row][col + 1].rgbtBlue * 2);
                    temp_color_gy = (image[row - 1][col - 1].rgbtBlue * -1) + (image[row - 1][col].rgbtBlue * -2) +
                                    (image[row - 1][col + 1].rgbtBlue * -1) + (image[row][col - 1].rgbtBlue * 0) +
                                    (image[row][col].rgbtBlue * 0) + (image[row][col + 1].rgbtBlue * 0);
                    temp_color = round(sqrt((float) ((float) temp_color_gx * (float) temp_color_gx) +
                                            (float) ((float) temp_color_gy * (float) temp_color_gy)));
                    if (temp_color > 255)
                    {
                        temp_color = 255;
                    }
                    image_edged[row][col].rgbtBlue = temp_color;
                }
            }
            else
            {
                if (col == 0)
                {
                    // no left outer
                    temp_color_gx = (image[row - 1][col].rgbtRed * 0) + (image[row - 1][col + 1].rgbtRed * 1) +
                                    (image[row][col].rgbtRed * 0) + (image[row][col + 1].rgbtRed * 2) +
                                    (image[row + 1][col].rgbtRed * 0) + (image[row + 1][col + 1].rgbtRed * 1);
                    temp_color_gy = (image[row - 1][col].rgbtRed * -2) + (image[row - 1][col + 1].rgbtRed * -1) +
                                    (image[row][col].rgbtRed * 0) + (image[row][col + 1].rgbtRed * 0) +
                                    (image[row + 1][col].rgbtRed * 2) + (image[row + 1][col + 1].rgbtRed * 1);
                    temp_color = round(sqrt((float) ((float) temp_color_gx * (float) temp_color_gx) +
                                            (float) ((float) temp_color_gy * (float) temp_color_gy)));
                    if (temp_color > 255)
                    {
                        temp_color = 255;
                    }
                    image_edged[row][col].rgbtRed = temp_color;

                    temp_color_gx = (image[row - 1][col].rgbtGreen * 0) + (image[row - 1][col + 1].rgbtGreen * 1) +
                                    (image[row][col].rgbtGreen * 0) + (image[row][col + 1].rgbtGreen * 2) +
                                    (image[row + 1][col].rgbtGreen * 0) + (image[row + 1][col + 1].rgbtGreen * 1);
                    temp_color_gy = (image[row - 1][col].rgbtGreen * -2) + (image[row - 1][col + 1].rgbtGreen * -1) +
                                    (image[row][col].rgbtGreen * 0) + (image[row][col + 1].rgbtGreen * 0) +
                                    (image[row + 1][col].rgbtGreen * 2) + (image[row + 1][col + 1].rgbtGreen * 1);
                    temp_color = round(sqrt((float) ((float) temp_color_gx * (float) temp_color_gx) +
                                            (float) ((float) temp_color_gy * (float) temp_color_gy)));
                    if (temp_color > 255)
                    {
                        temp_color = 255;
                    }
                    image_edged[row][col].rgbtGreen = temp_color;

                    temp_color_gx = (image[row - 1][col].rgbtBlue * 0) + (image[row - 1][col + 1].rgbtBlue * 1) +
                                    (image[row][col].rgbtBlue * 0) + (image[row][col + 1].rgbtBlue * 2) +
                                    (image[row + 1][col].rgbtBlue * 0) + (image[row + 1][col + 1].rgbtBlue * 1);
                    temp_color_gy = (image[row - 1][col].rgbtBlue * -2) + (image[row - 1][col + 1].rgbtBlue * -1) +
                                    (image[row][col].rgbtBlue * 0) + (image[row][col + 1].rgbtBlue * 0) +
                                    (image[row + 1][col].rgbtBlue * 2) + (image[row + 1][col + 1].rgbtBlue * 1);
                    temp_color = round(sqrt((float) ((float) temp_color_gx * (float) temp_color_gx) +
                                            (float) ((float) temp_color_gy * (float) temp_color_gy)));
                    if (temp_color > 255)
                    {
                        temp_color = 255;
                    }
                    image_edged[row][col].rgbtBlue = temp_color;
                }
                else if (col == width - 1)
                {
                    // no right outer
                    temp_color_gx = (image[row - 1][col - 1].rgbtRed * -1) + (image[row - 1][col].rgbtRed * 0) +
                                    (image[row][col - 1].rgbtRed * -2) + (image[row][col].rgbtRed * 0) +
                                    (image[row + 1][col - 1].rgbtRed * -1) + (image[row + 1][col].rgbtRed * 0);
                    temp_color_gy = (image[row - 1][col - 1].rgbtRed * -1) + (image[row - 1][col].rgbtRed * -2) +
                                    (image[row][col - 1].rgbtRed * 0) + (image[row][col].rgbtRed * 0) +
                                    (image[row + 1][col - 1].rgbtRed * 1) + (image[row + 1][col].rgbtRed * 2);
                    temp_color = round(sqrt((float) ((float) temp_color_gx * (float) temp_color_gx) +
                                            (float) ((float) temp_color_gy * (float) temp_color_gy)));
                    if (temp_color > 255)
                    {
                        temp_color = 255;
                    }
                    image_edged[row][col].rgbtRed = temp_color;

                    temp_color_gx = (image[row - 1][col - 1].rgbtGreen * -1) + (image[row - 1][col].rgbtGreen * 0) +
                                    (image[row][col - 1].rgbtGreen * -2) + (image[row][col].rgbtGreen * 0) +
                                    (image[row + 1][col - 1].rgbtGreen * -1) + (image[row + 1][col].rgbtGreen * 0);
                    temp_color_gy = (image[row - 1][col - 1].rgbtGreen * -1) + (image[row - 1][col].rgbtGreen * -2) +
                                    (image[row][col - 1].rgbtGreen * 0) + (image[row][col].rgbtGreen * 0) +
                                    (image[row + 1][col - 1].rgbtGreen * 1) + (image[row + 1][col].rgbtGreen * 2);
                    temp_color = round(sqrt((float) ((float) temp_color_gx * (float) temp_color_gx) +
                                            (float) ((float) temp_color_gy * (float) temp_color_gy)));
                    if (temp_color > 255)
                    {
                        temp_color = 255;
                    }
                    image_edged[row][col].rgbtGreen = temp_color;

                    temp_color_gx = (image[row - 1][col - 1].rgbtBlue * -1) + (image[row - 1][col].rgbtBlue * 0) +
                                    (image[row][col - 1].rgbtBlue * -2) + (image[row][col].rgbtBlue * 0) +
                                    (image[row + 1][col - 1].rgbtBlue * -1) + (image[row + 1][col].rgbtBlue * 0);
                    temp_color_gy = (image[row - 1][col - 1].rgbtBlue * -1) + (image[row - 1][col].rgbtBlue * -2) +
                                    (image[row][col - 1].rgbtBlue * 0) + (image[row][col].rgbtBlue * 0) +
                                    (image[row + 1][col - 1].rgbtBlue * 1) + (image[row + 1][col].rgbtBlue * 2);
                    temp_color = round(sqrt((float) ((float) temp_color_gx * (float) temp_color_gx) +
                                            (float) ((float) temp_color_gy * (float) temp_color_gy)));
                    if (temp_color > 255)
                    {
                        temp_color = 255;
                    }
                    image_edged[row][col].rgbtBlue = temp_color;
                }
                else
                {
                    // normal
                    temp_color_gx = (image[row - 1][col - 1].rgbtRed * -1) + (image[row - 1][col].rgbtRed * 0) +
                                    (image[row - 1][col + 1].rgbtRed * 1) + (image[row][col - 1].rgbtRed * -2) +
                                    (image[row][col].rgbtRed * 0) + (image[row][col + 1].rgbtRed * 2) +
                                    (image[row + 1][col - 1].rgbtRed * -1) + (image[row + 1][col].rgbtRed * 0) +
                                    (image[row + 1][col + 1].rgbtRed * 1);
                    temp_color_gy = (image[row - 1][col - 1].rgbtRed * -1) + (image[row - 1][col].rgbtRed * -2) +
                                    (image[row - 1][col + 1].rgbtRed * -1) + (image[row][col - 1].rgbtRed * 0) +
                                    (image[row][col].rgbtRed * 0) + (image[row][col + 1].rgbtRed * 0) +
                                    (image[row + 1][col - 1].rgbtRed * 1) + (image[row + 1][col].rgbtRed * 2) +
                                    (image[row + 1][col + 1].rgbtRed * 1);
                    temp_color = round(sqrt((float) ((float) temp_color_gx * (float) temp_color_gx) +
                                            (float) ((float) temp_color_gy * (float) temp_color_gy)));
                    if (temp_color > 255)
                    {
                        temp_color = 255;
                    }
                    image_edged[row][col].rgbtRed = temp_color;

                    temp_color_gx = (image[row - 1][col - 1].rgbtGreen * -1) + (image[row - 1][col].rgbtGreen * 0) +
                                    (image[row - 1][col + 1].rgbtGreen * 1) + (image[row][col - 1].rgbtGreen * -2) +
                                    (image[row][col].rgbtGreen * 0) + (image[row][col + 1].rgbtGreen * 2) +
                                    (image[row + 1][col - 1].rgbtGreen * -1) + (image[row + 1][col].rgbtGreen * 0) +
                                    (image[row + 1][col + 1].rgbtGreen * 1);
                    temp_color_gy = (image[row - 1][col - 1].rgbtGreen * -1) + (image[row - 1][col].rgbtGreen * -2) +
                                    (image[row - 1][col + 1].rgbtGreen * -1) + (image[row][col - 1].rgbtGreen * 0) +
                                    (image[row][col].rgbtGreen * 0) + (image[row][col + 1].rgbtGreen * 0) +
                                    (image[row + 1][col - 1].rgbtGreen * 1) + (image[row + 1][col].rgbtGreen * 2) +
                                    (image[row + 1][col + 1].rgbtGreen * 1);
                    temp_color = round(sqrt((float) ((float) temp_color_gx * (float) temp_color_gx) +
                                            (float) ((float) temp_color_gy * (float) temp_color_gy)));
                    if (temp_color > 255)
                    {
                        temp_color = 255;
                    }
                    image_edged[row][col].rgbtGreen = temp_color;

                    temp_color_gx = (image[row - 1][col - 1].rgbtBlue * -1) + (image[row - 1][col].rgbtBlue * 0) +
                                    (image[row - 1][col + 1].rgbtBlue * 1) + (image[row][col - 1].rgbtBlue * -2) +
                                    (image[row][col].rgbtBlue * 0) + (image[row][col + 1].rgbtBlue * 2) +
                                    (image[row + 1][col - 1].rgbtBlue * -1) + (image[row + 1][col].rgbtBlue * 0) +
                                    (image[row + 1][col + 1].rgbtBlue * 1);
                    temp_color_gy = (image[row - 1][col - 1].rgbtBlue * -1) + (image[row - 1][col].rgbtBlue * -2) +
                                    (image[row - 1][col + 1].rgbtBlue * -1) + (image[row][col - 1].rgbtBlue * 0) +
                                    (image[row][col].rgbtBlue * 0) + (image[row][col + 1].rgbtBlue * 0) +
                                    (image[row + 1][col - 1].rgbtBlue * 1) + (image[row + 1][col].rgbtBlue * 2) +
                                    (image[row + 1][col + 1].rgbtBlue * 1);
                    temp_color = round(sqrt((float) ((float) temp_color_gx * (float) temp_color_gx) +
                                            (float) ((float) temp_color_gy * (float) temp_color_gy)));
                    if (temp_color > 255)
                    {
                        temp_color = 255;
                    }
                    image_edged[row][col].rgbtBlue = temp_color;
                }
            }
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = image_edged[i][j];
        }
    }
}
