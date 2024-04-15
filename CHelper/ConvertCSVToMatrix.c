#include <stdio.h>
#include <stdlib.h>

#define MAX_ROWS 1080
#define MAX_COLS 1600

int main() {
    int a[MAX_ROWS][MAX_COLS]; // Assuming a 2D array of integers

    // Open the CSV file for reading
    FILE *csvfile = fopen("./CSV/image.csv", "r");
    if (csvfile == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    // Read each row from the CSV file and store it in the array
    int row = 0, col;
    char line[MAX_COLS * 4]; // Assuming each value can have up to 4 digits
    while (fgets(line, sizeof(line), csvfile)) {
        col = 0;
        char *token = strtok(line, ",");
        while (token != NULL && col < MAX_COLS) {
            a[row][col++] = atoi(token);
            token = strtok(NULL, ",");
        }
        row++;
    }

    fclose(csvfile);

    // Print the shape of the array
    printf("Shape of the array: (%d, %d)\n", row, col);

    return 0;
}
