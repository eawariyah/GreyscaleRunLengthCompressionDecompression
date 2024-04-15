#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Open the CSV file
    FILE *fp = fopen("./CSV/image.csv", "r");
    if (fp == NULL) {
        printf("Error opening CSV file\n");
        return 1;
    }

    // Count the number of rows in the CSV file
    int rows = 0;
    char line[1024];
    while (fgets(line, sizeof(line), fp) != NULL) {
        rows++;
    }
    rewind(fp);

    // Read the CSV file into a 2D array
    char **a = (char **)malloc(rows * sizeof(char *));
    for (int i = 0; i < rows; i++) {
        a[i] = (char *)malloc(1024 * sizeof(char));
        if (fgets(a[i], 1024, fp) == NULL) {
            printf("Error reading CSV file\n");
            for (int j = 0; j < i; j++) {
                free(a[j]);
            }
            free(a);
            fclose(fp);
            return 1;
        }
        a[i][strcspn(a[i], "\n")] = '\0'; // Remove newline character
    }
    fclose(fp);

    // Print the shape of the 2D array
    printf("Shape: %d x %d\n", rows, strlen(a[0]) / 4 + 1);

    // Free the memory allocated for the 2D array
    for (int i = 0; i < rows; i++) {
        free(a[i]);
    }
    free(a);

    return 0;
}