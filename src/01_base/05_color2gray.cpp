/* 图像灰度处理 */
#include <stdio.h>
#include <math.h>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat img = imread("img/img1.png", IMREAD_COLOR);
	imshow("image", img);

	Mat gray;
	cvtColor(img, gray, COLOR_BGR2GRAY);
	imshow("gray", gray);

	Mat max_gray, min_gray, ave_gray;
	cvtColor(img, max_gray, COLOR_BGR2GRAY);
	cvtColor(img, min_gray, COLOR_BGR2GRAY);
	cvtColor(img, ave_gray, COLOR_BGR2GRAY);
	for(int i = 0; i < img.rows; i++)
	{
		for(int j = 0; j < img.cols; j++)
		{
			int b = img.at<Vec3b>(i, j)[0];
			int g = img.at<Vec3b>(i, j)[1];
			int r = img.at<Vec3b>(i, j)[2];
			max_gray.at<uchar>(i, j) = (uchar)max(b, max(g, r));
			min_gray.at<uchar>(i, j) = (uchar)min(b, min(g, r));
			ave_gray.at<uchar>(i, j) = (uchar)((b + g + r) / 3);
		}
	}
	imshow("max_gray", max_gray);
	imshow("min_gray", min_gray);
	imshow("ave_gray", ave_gray);

	Mat oppt_gray;
	cvtColor(img, oppt_gray, COLOR_BGR2GRAY);
	for(int i = 0; i < gray.rows; i++)
	{
		for(int j = 0; j < gray.cols; j++)
		{
			oppt_gray.at<uchar>(i, j) = 255 - gray.at<uchar>(i, j);
		}
	}
	imshow("oppt_gray", oppt_gray);

	Mat oppt = Mat(img.size(), img.type());
	for(int i = 0; i < oppt.rows; i++)
	{
		for(int j = 0; j < oppt.cols; j++)
		{
			oppt.at<Vec3b>(i, j)[0] = ~img.at<Vec3b>(i, j)[0];
			oppt.at<Vec3b>(i, j)[1] = ~img.at<Vec3b>(i, j)[1];
			oppt.at<Vec3b>(i, j)[2] = ~img.at<Vec3b>(i, j)[2];
		}
	}
	imshow("oppt", oppt);

	waitKey(0);
	return 0;
}
