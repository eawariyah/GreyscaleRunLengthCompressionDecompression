#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#pragma pack(1)
typedef struct
{
    uint8_t r, g, b, a;
} pixel;

#pragma pack(1)
typedef struct
{
    uint8_t width[4];
    uint8_t height[4];
    uint8_t data[8];
} header;

void convert_to_8_channels(const char *input_filename, const char *output_filename)
{
    FILE *input_file = fopen(input_filename, "rb");
    if (input_file == NULL)
    {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }

    FILE *output_file = fopen(output_filename, "wb");
    if (output_file == NULL)
    {
        perror("Error opening output fileSecond");
        fclose(input_file);
        exit(EXIT_FAILURE);
    }

    // Read the header of the input file
    header input_header;
    fread(&input_header, sizeof(header), 1, input_file);

    // Write the header to the output file
    fwrite(&input_header, sizeof(header), 1, output_file);

    // Process each pixel in the input file and write the converted pixel to the output file
    pixel current_pixel;
    while (fread(&current_pixel, sizeof(pixel), 1, input_file) == 1)
    {
        // Convert pixel value from 0-255 to 0-7
        current_pixel.r >>= 5;
        current_pixel.g >>= 5;
        current_pixel.b >>= 5;
        current_pixel.a >>= 5;

        // Write the converted pixel to the output file
        fwrite(&current_pixel, sizeof(pixel), 1, output_file);
    }

    fclose(input_file);
    fclose(output_file);
}

int main()
{
    const char *input_filename = "OriginalImage.jpg";
    const char *output_filename = "EightChannelImageC.jpg";

    convert_to_8_channels(input_filename, output_filename);

    printf("Image converted to 8 channels and saved as 'EightChannelImage.raw'.\n");

    return 0;
}
