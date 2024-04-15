#include <stdio.h>
#include <stdlib.h>

int main() {
    // Define the matrix
    int image[9][9] = {
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 1, 1, 1, 1, 1, 0, 0},
            {0, 0, 1, 0, 0, 0, 0, 0, 0},
            {0, 0, 1, 1, 1, 1, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0, 0, 1, 0, 0},
            {0, 0, 1, 0, 0, 0, 1, 0, 0},
            {0, 0, 0, 1, 1, 1, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    // Open the CSV file for writing
    FILE *fp = fopen("./CSV/image.csv", "w");
    if (fp == NULL) {
        printf("Error opening CSV file\n");
        return 1;
    }

    // Write the matrix to the CSV file
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            fprintf(fp, "%d", image[i][j]);
            if (j < 8) {
                fprintf(fp, ",");
            }
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
    printf("./CSV/Image exported as image.csv\n");

    return 0;
}