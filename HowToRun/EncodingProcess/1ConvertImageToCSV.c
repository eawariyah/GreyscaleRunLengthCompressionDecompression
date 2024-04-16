#include <stdio.h>
#include <stdint.h>

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

void readBMP(const char *filename, uint8_t image[HEIGHT][WIDTH]) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        return;
    }

    BMPHeader header;
    fread(&header, sizeof(BMPHeader), 1, file);

    if (header.bfType != 0x4D42 || header.biWidth != WIDTH || header.biHeight != HEIGHT || header.biBitCount != 8) {
        printf("Invalid BMP format\n");
        fclose(file);
        return;
    }

    fseek(file, header.bfOffBits, SEEK_SET);
    fread(image, sizeof(uint8_t), WIDTH * HEIGHT, file);

    fclose(file);
}

void writeCSV(const char *filename, const uint8_t image[HEIGHT][WIDTH]) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        return;
    }

    for (int i = HEIGHT - 1; i >= 0; i--) { // Start from HEIGHT - 1 and move upwards
        for (int j = 0; j < WIDTH; j++) {
            fprintf(file, "%d", image[i][j]);
            if (j < WIDTH - 1) {
                fprintf(file, ",");
            }
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

int main() {
    uint8_t image[HEIGHT][WIDTH];
    readBMP("../Input/OriginalImage.bmp", image);
    // readBMP("../Input/QuantizedImage16.bmp", image);
    // readBMP("../Input/QuantizedImage32.bmp", image);    
    writeCSV("../Output/CSV/OriginalImage.csv", image);
    printf("Image exported as OriginalImage.csv\n");
    return 0;
}
