#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> // For uint8_t
#include <stdbool.h> // For bool

#define ROWS 9
#define COLUMNS 9

// Function to display the image
void displayImage(uint8_t image[ROWS][COLUMNS], int rows, int columns) {
    // Assuming you have a simple terminal to print the image
    // For more advanced graphical display, you'd need additional libraries
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (image[i][j] == 1)
                printf("# "); // Print '#' for white pixels
            else
                printf("  "); // Print ' ' for black pixels
        }
        printf("\n");
    }
}

int main() {
    uint8_t image[ROWS][COLUMNS] = {
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

    displayImage(image, ROWS, COLUMNS);

    return 0;
}
