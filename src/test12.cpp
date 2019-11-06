#include "test.h"

int main()
{
    Mat img = imread("img/img1.png", IMREAD_COLOR);
    imshow("image", img);

    Mat img1 = Mat(img.size(), img.type());
    cvtColor(img, img1, COLOR_BGR2GRAY);
    adaptiveThreshold(img1, img1, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 15, -2);
    imshow("image1", img1);

    waitKey(0);
    return 0;
}