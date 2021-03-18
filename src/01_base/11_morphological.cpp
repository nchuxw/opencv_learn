/* 形态学操作 */
#include <stdio.h>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main()
{
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    Mat img = imread("img/img1.png", IMREAD_COLOR);
    imshow("image", img);

    Mat img1 = Mat(img.size(), img.type());
    morphologyEx(img, img1, MORPH_OPEN, kernel);
    imshow("image_open", img1);

    Mat img2 = Mat(img.size(), img.type());
    morphologyEx(img, img2, MORPH_CLOSE, kernel);
    imshow("image_close", img2);

    Mat img3 = Mat(img.size(), img.type());
    morphologyEx(img, img3, MORPH_GRADIENT, kernel);
    imshow("image_gradient", img3);

    Mat img4 = Mat(img.size(), img.type());
    morphologyEx(img, img4, MORPH_TOPHAT, kernel);
    imshow("image_tophat", img4);

    Mat img5 = Mat(img.size(), img.type());
    morphologyEx(img, img5, MORPH_BLACKHAT, kernel);
    imshow("image_blackhat", img5);

    waitKey(0);
    return 0;
}