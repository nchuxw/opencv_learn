/* 卷积和池化 */
#include <stdio.h>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

#define MAX(a, b) ((a) < (b) ? (b) : (a))

void pool_max(Mat src, Mat &des)
{
	int i, j;

	for(i = 0; i < des.rows; i++)
	{
		for(j = 0; j < des.cols; j++)
		{
			uchar max = 0;
			max = MAX(max, src.at<uchar>(i * 2, j * 2));
			max = MAX(max, src.at<uchar>(i * 2 + 1, j * 2));
			max = MAX(max, src.at<uchar>(i * 2, j * 2 + 1));
			max = MAX(max, src.at<uchar>(i * 2 + 1, j * 2 + 1));
			des.at<uchar>(i, j) = max;
		}
	}
}

void pool_ave(Mat src, Mat &des)
{
	int i, j;

	for(i = 0; i < des.rows; i++)
	{
		for(j = 0; j < des.cols; j++)
		{
			int ave = 0;
			ave += src.at<uchar>(i * 2, j * 2);
			ave += src.at<uchar>(i * 2 + 1, j * 2);
			ave += src.at<uchar>(i * 2, j * 2 + 1);
			ave += src.at<uchar>(i * 2 + 1, j * 2 + 1);
			des.at<uchar>(i, j) = (uchar)(ave / 4);
		}
	}
}

int main()
{
	Mat img = imread("img/img1.png", cv::IMREAD_GRAYSCALE);
	imshow("src", img);

	Mat kernel1 = (Mat_<char>(3, 3) << 2, -1, 2, -1, -4, -1, 2, -1, 2);
	Mat des1 = Mat(img.rows, img.cols, img.type());
	filter2D(img, des1, img.depth(), kernel1);
	imshow("des1_con", des1);
	// imwrite("./img/des_con.png", des);

	Mat des2 = Mat(des1.rows / 2, des1.cols / 2, des1.type());
	pool_ave(des1, des2);
	imshow("des2_pool", des2);
	// imwrite("./img/des_pool.png", des2);

	Mat kernel2 = (Mat_<char>(3, 3) << 0, -1, 0, -1, 4, -1, 0, -1, 0);
	Mat des3 = Mat(des2.rows, des2.cols, des2.type());
	filter2D(des2, des3, des2.depth(), kernel2);
	imshow("des3_con", des3);

	Mat des4 = Mat(des3.rows / 2, des3.cols / 2, des3.type());
	pool_ave(des3, des4);
	imshow("des4_pool", des4);

	waitKey(0);
	return 0;
}