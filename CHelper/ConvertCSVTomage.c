#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <opencv2/opencv.hpp>

int main() {
    // Read the image data from the CSV file
    FILE *fp = fopen("./CSV/rle_decoded.csv", "r");
    if (fp == NULL) {
        printf("Error opening CSV file\n");
        return 1;
    }

    int height, width;
    if (fscanf(fp, "%d,%d", &height, &width) != 2) {
        printf("Error reading CSV file header\n");
        fclose(fp);
        return 1;
    }

    uint8_t *image_data = (uint8_t *)malloc(height * width * sizeof(uint8_t));
    for (int i = 0; i < height * width; i++) {
        if (fscanf(fp, "%hhu", &image_data[i]) != 1) {
            printf("Error reading CSV file data\n");
            fclose(fp);
            free(image_data);
            return 1;
        }
    }
    fclose(fp);

    // Reshape the image data into the original shape (assuming grayscale image)
    cv::Mat image(height, width, CV_8UC1, image_data);

    // Save the image
    cv::imwrite("./Resources/OriginalImage_reconstructed.jpg", image);

    printf("Image reconstructed as OriginalImage_reconstructed.jpg\n");

    free(image_data);
    return 0;
}