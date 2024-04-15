#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Include string.h for strtok

#define ROWS 1080
#define COLUMNS 1600

int main() {
    int a[ROWS][COLUMNS];

    FILE *file = fopen("OriginalImage.csv", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    char line[4096]; // Assuming maximum line length is 4096 characters
    int row = 0;
    while (fgets(line, sizeof(line), file) && row < ROWS) {
        char *token;
        token = strtok(line, ",");
        int col = 0;
        while (token != NULL && col < COLUMNS) {
            a[row][col++] = atoi(token);
            token = strtok(NULL, ",");
        }
        row++;
    }

    fclose(file);

    // Printing the array
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }

    return 0;
}
