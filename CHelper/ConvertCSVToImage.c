#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IMAGE_WIDTH 1600
#define IMAGE_HEIGHT 1080

void load_image_from_csv(const char *filename, unsigned char image[IMAGE_HEIGHT][IMAGE_WIDTH])
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file %s\n", filename);
        exit(1);
    }

    char line[IMAGE_WIDTH * 4]; // Assuming each pixel value can have up to 4 digits
    int row = 0;
    while (fgets(line, sizeof(line), file))
    {
        char *token = strtok(line, ",");
        int col = 0;
        while (token != NULL)
        {
            image[row][col++] = atoi(token);
            token = strtok(NULL, ",");
        }
        row++;
    }

    fclose(file);
}

void save_image(const char *filename, unsigned char image[IMAGE_HEIGHT][IMAGE_WIDTH])
{
    FILE *file = fopen(filename, "wb");
    if (file == NULL)
    {
        printf("Error opening file %s\n", filename);
        exit(1);
    }

    fwrite(image, sizeof(unsigned char), IMAGE_WIDTH * IMAGE_HEIGHT, file);
    fclose(file);
}

int main()
{
    unsigned char image[IMAGE_HEIGHT][IMAGE_WIDTH];

    // Load the pixel values from the CSV file
    load_image_from_csv("../CSV/OriginalImage.csv", image);
    // load_image_from_csv("./CSV/QuantizedImage16.csv", image);
    // load_image_from_csv("./CSV/QuantizedImage32.csv", image);

    // Save the image
    save_image("OriginalImage_reconstructed.jpg", image);
    // save_image("./Resources/QuantizedImage16_reconstructed.raw", image);
    // save_image("./Resources/QuantizedImage32_reconstructed.raw", image);

    printf("Image reconstructed and saved\n");

    return 0;
}
