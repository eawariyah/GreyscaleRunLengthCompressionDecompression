#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define WIDTH 1600
#define HEIGHT 1080

typedef struct {
    uint8_t value;
    int count;
} RLEPair;

void readRLE(const char *filename, RLEPair **rle, int *size) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        return;
    }

    int capacity = 100; // Initial capacity
    *rle = malloc(capacity * sizeof(RLEPair));
    if (*rle == NULL) {
        printf("Memory allocation failed\n");
        fclose(file);
        return;
    }

    int index = 0;
    int value, count;
    while (fscanf(file, "%d,%d\n", &value, &count) == 2) {
        (*rle)[index].value = (uint8_t)value;
        (*rle)[index].count = count;
        index++;
        if (index >= capacity) {
            // Resize the array if needed
            capacity *= 2;
            *rle = realloc(*rle, capacity * sizeof(RLEPair));
            if (*rle == NULL) {
                printf("Memory reallocation failed\n");
                fclose(file);
                return;
            }
        }
    }

    fclose(file);
    *size = index;
}

void decodeRLE(RLEPair *rle, int size, uint8_t decoded_image[HEIGHT][WIDTH]) {
    int row_index = 0;
    int col_index = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < rle[i].count; j++) {
            decoded_image[row_index][col_index + j] = rle[i].value;
        }
        col_index += rle[i].count;
        if (col_index >= WIDTH) {
            row_index++;
            col_index = 0;
        }
    }
}

void writeCSV(const char *filename, uint8_t image[HEIGHT][WIDTH]) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        return;
    }

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            fprintf(file, "%hhu", image[i][j]);
            if (j < WIDTH - 1) {
                fprintf(file, ",");
            }
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

int main() {
    RLEPair *rle;
    int size;
    readRLE("../Output/CSV/OriginalImageRecovered.csv", &rle, &size);

    uint8_t decoded_image[HEIGHT][WIDTH];
    decodeRLE(rle, size, decoded_image);

    writeCSV("../Output/CSV/rle_decoded.csv", decoded_image);

    free(rle);

    printf("Decoded image saved as rle_decoded.csv\n");

    return 0;
}
