/* 图像重合 */
#include <stdio.h>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat img1, img2, dest;
	float alp;

	img1 = imread("img/parole1.png", IMREAD_COLOR);
	img2 = imread("img/parole2.png", IMREAD_COLOR);
	dest = Mat(img1.size(), img1.type());
	waitKey(100);

	while(scanf("%f", &alp) != EOF)
	{
		for(int i = 0; i < img1.rows; i++)
		{
			for(int j = 0; j < img1.cols; j++)
			{
				dest.at<Vec3b>(i, j)[0] = img1.at<Vec3b>(i, j)[0] * alp + img2.at<Vec3b>(i, j)[0] * (1 - alp);
				dest.at<Vec3b>(i, j)[1] = img1.at<Vec3b>(i, j)[1] * alp + img2.at<Vec3b>(i, j)[1] * (1 - alp);
				dest.at<Vec3b>(i, j)[2] = img1.at<Vec3b>(i, j)[2] * alp + img2.at<Vec3b>(i, j)[2] * (1 - alp);
			}
		}
		imshow("img1", img1);
		imshow("img2", img2);
		imshow("dest", dest);
		waitKey(100);
	}
	return 0;
}
