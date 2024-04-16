#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROWS 756641
#define MAX_COLS 2

void csvToBinary(const char *csvFilename, const char *binaryFilename) {
    FILE *csvFile = fopen(csvFilename, "r");
    if (csvFile == NULL) {
        printf("Error opening CSV file %s\n", csvFilename);
        return;
    }

    FILE *binaryFile = fopen(binaryFilename, "wb");
    if (binaryFile == NULL) {
        printf("Error opening binary file %s\n", binaryFilename);
        fclose(csvFile);
        return;
    }

    uint8_t data[MAX_ROWS][MAX_COLS];
    int numRows = 0;
    int numCols = 0;

    char line[1024];
    while (fgets(line, sizeof(line), csvFile) && numRows < MAX_ROWS) {
        char *token = strtok(line, ",");
        numCols = 0;
        while (token != NULL && numCols < MAX_COLS) {
            data[numRows][numCols++] = atoi(token);
            token = strtok(NULL, ",");
        }
        numRows++;
    }

    fwrite(&numRows, sizeof(int), 1, binaryFile);
    fwrite(&numCols, sizeof(int), 1, binaryFile);
    fwrite(data, sizeof(uint8_t), numRows * numCols, binaryFile);

    fclose(csvFile);
    fclose(binaryFile);

    printf("CSV file %s converted to binary file %s\n", csvFilename, binaryFilename);
}

int main() {
    const char *csvFilename = "../Output/CSV/rle_encoded.csv";
    const char *binaryFilename = "../Output/Binary/rle_encoded_in_binary.bin";
    csvToBinary(csvFilename, binaryFilename);
    return 0;
}
