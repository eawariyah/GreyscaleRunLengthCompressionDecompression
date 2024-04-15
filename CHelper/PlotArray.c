#include <stdio.h>
#include <stdlib.h>
#include <opencv2/opencv.hpp>

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

    // Create a grayscale image from the matrix
    cv::Mat img(9, 9, CV_8UC1);
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            img.at<uchar>(i, j) = (uchar)image[i][j] * 255;
        }
    }

    // Display the image
    cv::imshow("Image", img);
    cv::waitKey(0);
    cv::destroyAllWindows();

    // Print the shape of the image
    printf("Shape: %d x %d\n", img.rows, img.cols);

    return 0;
}