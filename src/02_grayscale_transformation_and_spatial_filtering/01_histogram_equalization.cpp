/* 直方图均衡 */
#include <stdio.h>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

Mat histogram_equalization(Mat src)
{
	int i, j, pix;
	int table[256], mp[256];
	Mat dst = Mat(src.size(), src.type());

	memset(table, 0, sizeof(table));
	for(i = 0; i < src.rows; i++)
	{
		for(j = 0; j < src.cols; j++)
		{
			pix = src.at<uint8_t>(i, j);
			table[pix]++;
		}
	}
	for(i = 0; i < 256; i++)
	{
		if(i > 0)
		{
			table[i] = table[i - 1] + table[i];
		}
		mp[i] = (uint8_t)(255.0 * table[i] / src.rows / src.cols + 0.5);
	}
	for(i = 0; i < src.rows; i++)
	{
		for(j = 0; j < src.cols; j++)
		{
			pix = src.at<uint8_t>(i, j);
			dst.at<uint8_t>(i, j) = mp[pix];
		}
	}
	return dst;
}

int main()
{
	Mat src = cv::imread("img/img4.png", cv::IMREAD_GRAYSCALE);
	cv::imshow("src", src);

	Mat dst = histogram_equalization(src);
	cv::imshow("dst", dst);
	cv::imwrite("img/img4_he.png", dst);

	cv::waitKey(0);
	return 0;
}
