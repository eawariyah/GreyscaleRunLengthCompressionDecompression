#include <stdio.h>
#include <stdlib.h>
#include <opencv2/opencv.hpp>

int main() {
    // Load the image
    cv::Mat image = cv::imread("./Resources/OriginalImage.jpg", cv::IMREAD_GRAYSCALE);
    // cv::Mat image = cv::imread("./Resources/QuantizedImage16.jpg", cv::IMREAD_GRAYSCALE);
    // cv::Mat image = cv::imread("./Resources/QuantizedImage32.jpg", cv::IMREAD_GRAYSCALE);

    // Print the image data
    printf("%s\n", image.dump().c_str());

    // Save the image data to a CSV file
    FILE *fp = fopen("./CSV/OriginalImage.csv", "w");
    if (fp == NULL) {
        printf("Error opening CSV file\n");
        return 1;
    }

    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            fprintf(fp, "%d", image.at<uchar>(i, j));
            if (j < image.cols - 1) {
                fprintf(fp, ",");
            }
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
    printf("Image exported as OriginalImage.csv\n");

    return 0;
}