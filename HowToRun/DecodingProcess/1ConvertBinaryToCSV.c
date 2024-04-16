#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROWS 756641
#define MAX_COLS 2

void binaryToCSV(const char *binaryFilename, const char *csvFilename) {
    FILE *binaryFile = fopen(binaryFilename, "rb");
    if (binaryFile == NULL) {
        printf("Error opening binary file %s\n", binaryFilename);
        return;
    }

    FILE *csvFile = fopen(csvFilename, "w");
    if (csvFile == NULL) {
        printf("Error opening CSV file %s\n", csvFilename);
        fclose(binaryFile);
        return;
    }

    int numRows, numCols;
    fread(&numRows, sizeof(int), 1, binaryFile);
    fread(&numCols, sizeof(int), 1, binaryFile);

    uint8_t data[MAX_ROWS][MAX_COLS];
    fread(data, sizeof(uint8_t), numRows * numCols, binaryFile);

    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            fprintf(csvFile, "%u", data[i][j]);
            if (j < numCols - 1) {
                fprintf(csvFile, ",");
            }
        }
        fprintf(csvFile, "\n");
    }

    fclose(binaryFile);
    fclose(csvFile);

    printf("Binary file %s converted to CSV file %s\n", binaryFilename, csvFilename);
}

int main() {
    const char *binaryFilename = "../Output/Binary/rle_encoded_in_binary.bin";
    const char *csvFilename = "../Output/CSV/OriginalImageRecovered.csv";
    binaryToCSV(binaryFilename, csvFilename);
    return 0;
}
