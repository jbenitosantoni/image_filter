#include "helpers.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            double avarage =
                    ((double) image[i][j].rgbtBlue + (double) image[i][j].rgbtGreen + (double) image[i][j].rgbtRed) /
                    3.0;
            avarage = round(avarage);
            image[i][j].rgbtBlue = avarage;
            image[i][j].rgbtGreen = avarage;
            image[i][j].rgbtRed = avarage;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width]) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int red = round(
                    (image[i][j].rgbtRed * .393) + (image[i][j].rgbtGreen * .769) + (image[i][j].rgbtBlue * .189));
            int green = round(
                    (image[i][j].rgbtRed * .349) + (image[i][j].rgbtGreen * .686) + (image[i][j].rgbtBlue * .168));
            int blue = round(
                    (image[i][j].rgbtRed * .272) + (image[i][j].rgbtGreen * .534) + (image[i][j].rgbtBlue * .131));

            if (red > 255) {
                red = 255;
            }
            if (green > 255) {
                green = 255;
            }
            if (blue > 255) {
                blue = 255;
            }
            image[i][j].rgbtBlue = blue;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtRed = red;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width / 2; j++) {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width]) {
    RGBTRIPLE temp[height][width];
    double red, green, blue;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if ((j == 0 || j == (width - 1)) && (i == 0 || i == (height - 1))) {
                if (j == 0 && i == 0) {
                    red = round((image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed +
                                 image[i][j].rgbtRed) / 4);
                    green = round(
                            (image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen +
                             image[i][j].rgbtGreen) / 4);
                    blue = round((image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue +
                                  image[i][j].rgbtBlue) / 4);
                } else if (j == 0 && i == (width - 1)) {
                    red = round((image[i][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed +
                                 image[i][j].rgbtRed) / 4);
                    green = round(
                            (image[i][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen +
                             image[i][j].rgbtGreen) / 4);
                    blue = round((image[i][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue +
                                  image[i][j].rgbtBlue) / 4);
                } else if (j == (height - 1) && i == 0) {
                    red = round((image[i][j + 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed +
                                 image[i][j].rgbtRed) / 4);
                    green = round(
                            (image[i][j + 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen +
                             image[i][j].rgbtGreen) / 4);
                    blue = round((image[i][j + 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue +
                                  image[i][j].rgbtBlue) / 4);
                } else if (j == (height - 1) && i == (width - 1)) {
                    red = round((image[i][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed +
                                 image[i][j].rgbtRed) / 4);
                    green = round(
                            (image[i][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen +
                             image[i][j].rgbtGreen) / 4);
                    blue = round((image[i][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue +
                                  image[i][j].rgbtBlue) / 4);
                }
            } else if ((i == 0 || i == (height - 1)) && j != 0 && j != (width - 1)) {
                if (i == 0) {
                    red = round((image[i][j - 1].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed +
                                 image[i + 1][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i][j].rgbtRed) / 6);
                    green = round((image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen +
                                   image[i + 1][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen +
                                   image[i][j].rgbtGreen) / 6);
                    blue = round((image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue +
                                  image[i + 1][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i][j].rgbtBlue) /
                                 6);
                } else {
                    red = round((image[i][j - 1].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j].rgbtRed +
                                 image[i - 1][j + 1].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i][j].rgbtRed) / 6);
                    green = round((image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j].rgbtGreen +
                                   image[i - 1][j + 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen +
                                   image[i][j].rgbtGreen) / 6);
                    blue = round((image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j].rgbtBlue +
                                  image[i - 1][j + 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i][j].rgbtBlue) /
                                 6);
                }
            } else if (j == (width - 1) || (j == 0)) {
                if (j == 0) {
                    red = round((image[i][j + 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed +
                                 image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed + image[i][j].rgbtRed) / 6);
                    green = round(
                            (image[i][j + 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen +
                             image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen + image[i][j].rgbtGreen) / 6);
                    blue = round((image[i][j + 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue +
                                  image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue + image[i][j].rgbtBlue) / 6);
                } else {
                    red = round((image[i][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed +
                                 image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i][j].rgbtRed) / 6);
                    green = round(
                            (image[i][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen +
                             image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i][j].rgbtGreen) / 6);
                    blue = round((image[i][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue +
                                  image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i][j].rgbtBlue) / 6);
                }
            } else if (j == (width / 2) && i == (width / 2)) {
                red = round((image[i][j - 1].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j].rgbtRed +
                             image[i - 1][j + 1].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed +
                             image[i + 1][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed) / 8);
                green = round((image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j].rgbtGreen +
                               image[i - 1][j + 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen +
                               image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen +
                               image[i + 1][j - 1].rgbtGreen) / 8);
                blue = round((image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j].rgbtBlue +
                              image[i - 1][j + 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue +
                              image[i + 1][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue) / 8);
            } else {
                red = round((image[i][j - 1].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j].rgbtRed +
                             image[i - 1][j + 1].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed +
                             image[i + 1][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i][j].rgbtRed) / 9);
                green = round((image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j].rgbtGreen +
                               image[i - 1][j + 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen +
                               image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen +
                               image[i + 1][j - 1].rgbtGreen + image[i][j].rgbtGreen) / 9);
                blue = round((image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j].rgbtBlue +
                              image[i - 1][j + 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue +
                              image[i + 1][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i][j].rgbtBlue) / 9);
            }
            temp[i][j].rgbtRed = red;
            temp[i][j].rgbtGreen = green;
            temp[i][j].rgbtBlue = blue;
        }
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            image[i][j] = temp[i][j];
        }
    }
    return;
}
