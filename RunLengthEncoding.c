#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define WIDTH 1600
#define HEIGHT 1080

void readCSV(const char *filename, uint8_t image[HEIGHT][WIDTH]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        return;
    }

    for (int i = 0; i < HEIGHT; i++) {
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

typedef struct {
    uint8_t value;
    int count;
} RLEPair;

void runLengthEncoding(uint8_t image[HEIGHT][WIDTH], RLEPair **rle, int *size) {
    int capacity = WIDTH * HEIGHT;
    *rle = malloc(capacity * sizeof(RLEPair));
    if (*rle == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    int index = 0;
    uint8_t current_value;
    int count;
    for (int i = 0; i < HEIGHT; i++) {
        current_value = image[i][0];
        count = 1;
        for (int j = 1; j < WIDTH; j++) {
            if (image[i][j] == current_value) {
                count++;
            } else {
                (*rle)[index].value = current_value;
                (*rle)[index].count = count;
                index++;
                if (index >= capacity) {
                    // Resize the array if needed
                    capacity *= 2;
                    *rle = realloc(*rle, capacity * sizeof(RLEPair));
                    if (*rle == NULL) {
                        printf("Memory reallocation failed\n");
                        return;
                    }
                }
                current_value = image[i][j];
                count = 1;
            }
        }
        (*rle)[index].value = current_value;
        (*rle)[index].count = count;
        index++;
        if (index >= capacity) {
            // Resize the array if needed
            capacity *= 2;
            *rle = realloc(*rle, capacity * sizeof(RLEPair));
            if (*rle == NULL) {
                printf("Memory reallocation failed\n");
                return;
            }
        }
    }
    *size = index;
}

void writeCSV(const char *filename, RLEPair *rle, int size) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        return;
    }

    for (int i = 0; i < size; i++) {
        fprintf(file, "%hhu,%d\n", rle[i].value, rle[i].count);
    }

    fclose(file);
}

int main() {
    uint8_t image[HEIGHT][WIDTH];
    readCSV("OriginalImage.csv", image);

    RLEPair *rle;
    int size;
    runLengthEncoding(image, &rle, &size);

    writeCSV("rle_encoded.csv", rle, size);

    free(rle);

    printf("RLE encoded data saved as rle_encoded.csv\n");

    return 0;
}
