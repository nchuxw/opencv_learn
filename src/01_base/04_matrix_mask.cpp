/* 矩阵掩码 */
#include <stdio.h>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat img = imread("img/img1.png", IMREAD_COLOR);

	Mat result1(img.rows, img.cols, img.type());
	int i, j, val;
	unsigned char *pre, *cur, *next, *outptr;
	double t = (double)getTickCount();
	for(i = 1; i < img.rows - 1; i++)
	{
		pre = img.ptr<unsigned char>(i - 1);
		cur = img.ptr<unsigned char>(i);
		next = img.ptr<unsigned char>(i + 1);
		outptr = result1.ptr<unsigned char>(i);
		for(j = img.channels(); j < img.channels() * (img.cols - 1); j++)
		{
			val = 5 * cur[j];
			val -= cur[j - img.channels()];
			val -= cur[j + img.channels()];
			val -= pre[j];
			val -= next[j];
			outptr[j] = saturate_cast<unsigned char>(val);
		}
	}
	result1.row(0).setTo(Scalar(0));
	result1.row(result1.rows - 1).setTo(Scalar(0));
	result1.col(0).setTo(Scalar(0));
	result1.col(result1.cols -1).setTo(Scalar(0));
	t = ((double)getTickCount() - t) / getTickFrequency();
	printf("way1 time passed in:%lfs\n", t);

	t = (double)getTickCount();
	Mat result2(img.rows, img.cols, img.type());
	Mat kernel = (Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	filter2D(img, result2, img.depth(), kernel);
	t = ((double)getTickCount() - t) / getTickFrequency();
	printf("way2 time passed in:%lfs\n", t);

	imshow("image", img);
	imshow("result1", result1);
	imshow("result2", result2);
	waitKey(0);
	return 0;
}
