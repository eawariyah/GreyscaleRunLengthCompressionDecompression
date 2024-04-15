#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> // For uint8_t
#include <stdbool.h> // For bool

#define IMAGE_WIDTH 640
#define IMAGE_HEIGHT 480

// Function to read an image from a file
void readImage(const char *filename, uint8_t image[IMAGE_HEIGHT][IMAGE_WIDTH]) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    fread(image, sizeof(uint8_t), IMAGE_WIDTH * IMAGE_HEIGHT, file);
    fclose(file);
}

// Function to write an image to a file
void writeImage(const char *filename, uint8_t image[IMAGE_HEIGHT][IMAGE_WIDTH]) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    fwrite(image, sizeof(uint8_t), IMAGE_WIDTH * IMAGE_HEIGHT, file);
    fclose(file);
}

// Function to apply quantization to an image
void quantizeImage(uint8_t image[IMAGE_HEIGHT][IMAGE_WIDTH], uint8_t quantized_image[IMAGE_HEIGHT][IMAGE_WIDTH]) {
    // Define the quantization levels
    int quantization_levels[8];
    for (int i = 0; i < 8; i++) {
        quantization_levels[i] = i * 32;
    }

    // Apply quantization
    for (int i = 0; i < IMAGE_HEIGHT; i++) {
        for (int j = 0; j < IMAGE_WIDTH; j++) {
            int pixel_value = image[i][j];
            int bin = pixel_value / 32;
            quantized_image[i][j] = bin * 32 + 16; // Adjusting to mid-point of each bin
        }
    }
}

int main() {
    uint8_t original_image[IMAGE_HEIGHT][IMAGE_WIDTH];
    uint8_t quantized_image[IMAGE_HEIGHT][IMAGE_WIDTH];

    // Read the original grayscale image
    readImage("OriginalImage.jpg", original_image);

    // Apply quantization
    quantizeImage(original_image, quantized_image);

    // Save the quantized image
    writeImage("QuantizedImage32.jpg", quantized_image);

    printf("Quantized image saved as QuantizedImage.jpg\n");

    return 0;
}
