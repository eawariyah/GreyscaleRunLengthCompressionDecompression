#include <stdio.h>
#include <stdlib.h>
#include <opencv2/opencv.hpp>

int main() {
    // Read the original grayscale image
    cv::Mat image = cv::imread("./Resources/OriginalImage.jpg", cv::IMREAD_GRAYSCALE);

    // Define the quantization levels
    int quantization_levels = 32;
    int bin_size = 256 / quantization_levels;

    // Apply quantization
    cv::Mat quantized_image(image.rows, image.cols, CV_8UC1);
    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            int pixel_value = image.at<uchar>(i, j);
            int bin = pixel_value / bin_size;
            quantized_image.at<uchar>(i, j) = (bin * bin_size) + (bin_size / 2);
        }
    }

    // Save the quantized image
    cv::imwrite("./Resources/QuantizedImage16.jpg", quantized_image);
    printf("Quantized image saved as QuantizedImage16.jpg\n");

    return 0;
}