#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define WIDTH 1600
#define HEIGHT 1080
#define MAX_PIXEL_VALUE 255
#define QUANTIZATION_LEVELS 16

// Function to read the grayscale JPEG image
uint8_t* readJPEG(const char* filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    // Skipping the header of the JPEG file
    fseek(file, 2, SEEK_SET);
    while (fgetc(file) != 0xFF);

    // Reading the image data
    uint8_t *image = (uint8_t*)malloc(WIDTH * HEIGHT * sizeof(uint8_t));
    if (image == NULL) {
        printf("Memory allocation error\n");
        fclose(file);
        exit(1);
    }
    fread(image, WIDTH * HEIGHT, 1, file);
    fclose(file);

    return image;
}

// Function to write the image as PGM format
void writePGM(const char* filename, uint8_t* image) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Error opening file\n");
        free(image);
        exit(1);
    }

    // Writing the PGM header
    fprintf(file, "P5\n%d %d\n%d\n", WIDTH, HEIGHT, MAX_PIXEL_VALUE);

    // Writing the image data
    fwrite(image, WIDTH * HEIGHT, 1, file);
    fclose(file);

    free(image);
}

int main() {
    const char* originalFilename = "OriginalImage.jpg";
    const char* quantizedFilename = "QuantizedImage16.pgm";

    // Read the grayscale JPEG image
    uint8_t* image = readJPEG(originalFilename);

    // Define the quantization levels
    uint8_t quantizationLevels[QUANTIZATION_LEVELS];
    for (int i = 0; i < QUANTIZATION_LEVELS; i++) {
        quantizationLevels[i] = i * (MAX_PIXEL_VALUE / (QUANTIZATION_LEVELS - 1));
    }

    // Apply quantization
    for (int i = 0; i < WIDTH * HEIGHT; i++) {
        uint8_t pixelValue = image[i];
        for (int j = 0; j < QUANTIZATION_LEVELS; j++) {
            if (pixelValue < quantizationLevels[j]) {
                image[i] = quantizationLevels[j];
                break;
            }
        }
    }

    // Write the quantized image as PGM
    writePGM(quantizedFilename, image);

    printf("Quantized image saved as %s\n", quantizedFilename);

    return 0;
}
