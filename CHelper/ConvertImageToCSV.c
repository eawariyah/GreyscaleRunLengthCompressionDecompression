#include <stdio.h>

#define ROWS 1080
#define COLS 1600

void readImage(const char *filename, unsigned char image[ROWS][COLS]) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        return;
    }

    fread(image, sizeof(unsigned char), ROWS * COLS, file);
    fclose(file);
}

void writeCSV(const char *filename, unsigned char image[ROWS][COLS]) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        return;
    }

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            fprintf(file, "%d", image[i][j]);
            if (j < COLS - 1) {
                fprintf(file, ",");
            }
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

int main() {
    unsigned char image[ROWS][COLS];
    const char *inputFilename = "OriginalImage.jpg";
    const char *outputFilename = "OriginalImage.csv";

    readImage(inputFilename, image);
    writeCSV(outputFilename, image);

    printf("Image exported as %s\n", outputFilename);

    return 0;
}
