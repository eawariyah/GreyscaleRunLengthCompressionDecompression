#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define WIDTH 1600
#define HEIGHT 1080

#pragma pack(push, 1)
typedef struct {
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
    uint32_t biSize;
    int32_t biWidth;
    int32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    int32_t biXPelsPerMeter;
    int32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
} BMPHeader;
#pragma pack(pop)

void readCSV(const char *filename, uint8_t image[HEIGHT][WIDTH]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        return;
    }

    for (int i = HEIGHT - 1; i >= 0; i--) { // Start from HEIGHT - 1 and move downwards
        for (int j = 0; j < WIDTH; j++) {
            if (fscanf(file, "%hhu,", &image[i][j]) != 1) {
                printf("Error reading CSV file\n");
                fclose(file);
                return;
            }
        }
    }

    fclose(file);
}

void writeBMP(const char *filename, const uint8_t image[HEIGHT][WIDTH]) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        return;
    }

    BMPHeader header;
    header.bfType = 0x4D42;
    header.bfSize = sizeof(BMPHeader) + sizeof(uint8_t) * WIDTH * HEIGHT + 256 * sizeof(uint32_t);
    header.bfReserved1 = 0;
    header.bfReserved2 = 0;
    header.bfOffBits = sizeof(BMPHeader) + 256 * sizeof(uint32_t);
    header.biSize = sizeof(BMPHeader) - 14;
    header.biWidth = WIDTH;
    header.biHeight = HEIGHT;
    header.biPlanes = 1;
    header.biBitCount = 8;
    header.biCompression = 0;
    header.biSizeImage = 0;
    header.biXPelsPerMeter = 0;
    header.biYPelsPerMeter = 0;
    header.biClrUsed = 256;
    header.biClrImportant = 0;

    fwrite(&header, sizeof(BMPHeader), 1, file);

    // Write color palette
    uint32_t palette[256];
    for (int i = 0; i < 256; i++) {
        palette[i] = (i << 16) | (i << 8) | i; // Grayscale values (R = G = B)
    }
    fwrite(palette, sizeof(uint32_t), 256, file);

    // Write image data
    for (int i = 0; i < HEIGHT; i++) { // Start from the top row and move downwards
        for (int j = 0; j < WIDTH; j++) {
            fputc(image[i][j], file);
        }
    }

    fclose(file);
}

int main() {
    uint8_t image[HEIGHT][WIDTH];
    readCSV("../Output/CSV/rle_decoded.csv", image);
    writeBMP("../Output/rleDecoded.bmp", image);
    printf("Image exported as RestoredImage.bmp\n");
    return 0;
}
