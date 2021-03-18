/* 提取水平和竖直直线 */
#include <stdio.h>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main()
{
    Mat img = imread("img/img1.png", IMREAD_COLOR);
    imshow("image", img);

    //画几条水平和竖直直线
    line(img, Point(100, 100), Point(400, 100), Scalar(255, 255, 255), 4);
    line(img, Point(200, 150), Point(550, 150), Scalar(255, 255, 255), 4);
    line(img, Point(150, 400), Point(500, 400), Scalar(255, 255, 255), 4);
    line(img, Point(250, 50), Point(250, 300), Scalar(255, 255, 255), 4);
    line(img, Point(300, 70), Point(300, 400), Scalar(255, 255, 255), 4);
    line(img, Point(550, 150), Point(550, 550), Scalar(255, 255, 255), 4);
    imshow("image", img);

    Mat img1 = Mat(img.size(), img.type());
    cvtColor(img, img1, COLOR_BGR2GRAY); //灰度处理
    imshow("image1", img1);

    Mat img2 = Mat(img.size(), img.type()); //二值化
    adaptiveThreshold(img1, img2, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 9, 0);
    imshow("image2", img2);

    Mat sp_kernel = getStructuringElement(MORPH_RECT, Size(200, 1));//Size的宽度大,高度为1
    Mat img3 = Mat(img.size(), img.type()); //执行开操作(先腐蚀后膨胀),得到水平直线
    morphologyEx(img2, img3, MORPH_OPEN, sp_kernel);
    imshow("image3", img3);

    Mat sz_kernel = getStructuringElement(MORPH_RECT, Size(1, 200));//Size的宽度为1,高度小
    Mat img4 = Mat(img.size(), img.type()); //执行开操作(先腐蚀后膨胀),得到竖直直线
    morphologyEx(img2, img4, MORPH_OPEN, sz_kernel);
    imshow("image4", img4);

    waitKey(0);
    return 0;
}