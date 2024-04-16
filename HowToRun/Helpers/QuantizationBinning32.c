#include <stdio.h>
#include <stdint.h>

#define WIDTH 1600
#define HEIGHT 1080
#define QUANTIZATION_LEVELS 32

void readBMP(const char *filename, uint8_t image[HEIGHT][WIDTH]) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        return;
    }

    fseek(file, 54, SEEK_SET); // Skip the BMP header
    fread(image, sizeof(uint8_t), WIDTH * HEIGHT, file);

    fclose(file);
}

void writeBMP(const char *filename, const uint8_t image[HEIGHT][WIDTH]) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        return;
    }

    uint8_t header[54] = {
        0x42, 0x4D, 0x36, 0x0C, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x04, 0x00, 0x00, 0x28, 0x00,
        0x00, 0x00, 0x40, 0x06, 0x00, 0x00, 0xD0, 0x02, 0x00, 0x00, 0x01, 0x00, 0x08, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x0C, 0x0C, 0x00, 0x13, 0x0B, 0x00, 0x14, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    fwrite(header, sizeof(uint8_t), 54, file);

    // Apply quantization
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            uint8_t quantized_value = ((image[i][j] / 32) * 32) + 16; // Adjusting to mid-point of each bin
            fputc(quantized_value, file);
        }
    }

    fclose(file);
}

int main() {
    uint8_t image[HEIGHT][WIDTH];
    readBMP("../Input/OriginalImage.bmp", image);
    writeBMP("../Input/QuantizedImage32.bmp", image);
    printf("Quantized image saved as QuantizedImage32.bmp\n");
    return 0;
}
