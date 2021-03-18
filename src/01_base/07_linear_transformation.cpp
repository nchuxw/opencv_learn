/* 线性变换 */
#include <stdio.h>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat img = imread("img/img1.png", IMREAD_COLOR);
	Mat img1 = Mat(img.size(), img.type());
	double a, b;
	
	while(scanf("%lf %lf", &a, &b) != EOF)
	{
		for(int i = 0; i < img.rows; i++)
		{
			for(int j = 0; j < img.cols; j++)
			{
				img1.at<Vec3b>(i, j)[0] = saturate_cast<uchar>(a * img.at<Vec3b>(i, j)[0] + b);
				img1.at<Vec3b>(i, j)[1] = saturate_cast<uchar>(a * img.at<Vec3b>(i, j)[1] + b);
				img1.at<Vec3b>(i, j)[2] = saturate_cast<uchar>(a * img.at<Vec3b>(i, j)[2] + b);
			}
		}
		imshow("image", img);
		imshow("image1", img1);
		waitKey(100);
	}
	return 0;
}
