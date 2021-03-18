/*图像的读取,显示*/
#include <stdio.h>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat img = imread("img/img1.png", IMREAD_COLOR);
	printf("%d %d %d\n", img.cols, img.rows, img.channels());
	namedWindow("image", WINDOW_AUTOSIZE);
	imshow("image", img);

	Mat img1;
	cvtColor(img, img1, COLOR_BGR2GRAY);
	printf("%d %d %d\n", img1.cols, img1.rows, img1.channels());
	//imwrite("./img1_1.png", img1);
	namedWindow("image_1", WINDOW_AUTOSIZE);
	imshow("image_1", img1);

	Mat img2(img, Rect(100, 200, 200, 100));
	printf("%d %d %d\n", img2.cols, img2.rows, img2.channels());
	namedWindow("image_2", WINDOW_AUTOSIZE);
	imshow("image_2", img2);

	Mat img3 = img(Range::all(), Range(100, 200));
	printf("%d %d %d\n", img3.cols, img3.rows, img3.channels());
	namedWindow("image_3", WINDOW_AUTOSIZE);
	imshow("image_3", img3);

	waitKey(0);
	return 0;
}
