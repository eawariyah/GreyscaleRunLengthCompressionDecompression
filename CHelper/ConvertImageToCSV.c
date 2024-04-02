#include <stdio.h>
#include <stdlib.h>

#define IMAGE_WIDTH  1600
#define IMAGE_HEIGHT 1080

void load_grayscale_image(const char* filename, unsigned char image[IMAGE_HEIGHT][IMAGE_WIDTH]) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        exit(1);
    }

    fread(image, sizeof(unsigned char), IMAGE_WIDTH * IMAGE_HEIGHT, file);
    fclose(file);
}

void save_image_to_csv(const char* filename, unsigned char image[IMAGE_HEIGHT][IMAGE_WIDTH]) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        exit(1);
    }

    for (int i = 0; i < IMAGE_HEIGHT; ++i) {
        for (int j = 0; j < IMAGE_WIDTH; ++j) {
            fprintf(file, "%d", image[i][j]);
            if (j < IMAGE_WIDTH - 1) {
                fprintf(file, ",");
            }
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

int main() {
    unsigned char image[IMAGE_HEIGHT][IMAGE_WIDTH];

    // Load the grayscale image
    load_grayscale_image("OriginalImage.jpg", image);
    // load_grayscale_image("./Resources/QuantizedImage16.raw", image);
    // load_grayscale_image("./Resources/QuantizedImage32.raw", image);

    // Save the image to CSV
    save_image_to_csv("OriginalImage.csv", image);
    // save_image_to_csv("./CSV/QuantizedImage16.csv", image);
    // save_image_to_csv("./CSV/QuantizedImage32.csv", image);

    printf("Image exported as OriginalImage.csv\n");

    return 0;
}
