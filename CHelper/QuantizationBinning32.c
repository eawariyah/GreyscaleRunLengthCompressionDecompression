#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> // For uint8_t
#include <stdbool.h> // For bool
#include <jpeglib.h>

#define IMAGE_WIDTH 1600
#define IMAGE_HEIGHT 1800

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

// Function to write an image to a JPEG file
void writeJPEG(const char *filename, uint8_t image[IMAGE_HEIGHT][IMAGE_WIDTH]) {
    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;
    JSAMPROW row_pointer[1];
    FILE *outfile = fopen(filename, "wb");

    if (!outfile) {
        printf("Error opening output JPEG file\n");
        exit(1);
    }

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);
    jpeg_stdio_dest(&cinfo, outfile);

    cinfo.image_width = IMAGE_WIDTH;
    cinfo.image_height = IMAGE_HEIGHT;
    cinfo.input_components = 1; // grayscale image
    cinfo.in_color_space = JCS_GRAYSCALE;
    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, 100, TRUE);

    jpeg_start_compress(&cinfo, TRUE);

    while (cinfo.next_scanline < cinfo.image_height) {
        row_pointer[0] = &image[cinfo.next_scanline][0];
        (void)jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }

    jpeg_finish_compress(&cinfo);
    fclose(outfile);
    jpeg_destroy_compress(&cinfo);
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

    // Save the quantized image as a JPEG file
    writeJPEG("QuantizedImage32.jpg", quantized_image);

    printf("Quantized image saved as QuantizedImage32.jpg\n");

    return 0;
}
