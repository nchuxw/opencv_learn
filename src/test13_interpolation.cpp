/* 图像内插 */
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

/* 最近邻内插 */
void nearest_interpolation(Mat src, Mat &dst, Size dst_size)
{
	int i, j, x, y;
	/* 计算原图像与目标图像的宽度和高度比例 */
	double wsd = (double)src.cols / dst_size.width;
	double hsd = (double)src.rows / dst_size.height;

	dst = Mat(dst_size, src.type());
	for(i = 0; i < dst.rows; i++)
	{
		y = hsd * i + 0.5;
		for(j = 0; j < dst.cols; j++)
		{
			x = wsd * j + 0.5;
			dst.at<uchar>(i, j) = src.at<uchar>(y, x);
		}
	}
}

/* 双线性内插 */
void bilinear_interpolation(Mat src, Mat &dst, Size dst_size)
{
	int i, j;
	/* 计算原图像与目标图像的宽度和高度比例 */
	double wsd = (double)src.cols / dst_size.width;
	double hsd = (double)src.rows / dst_size.height;
	/* 表示原图中的浮点像素 */
	Point2f sfp;
	/* 表示在原图中与浮点像素最近的四个整数坐标值(左x、右x、上y、下y) */
	double lx, rx, uy, dy;
	/* x方向的两个像素点值，xy两个方向上的像素点值 */
	double xf1, xf2, xyf;

	dst = Mat(dst_size, src.type());
	for(i = 0; i < dst.rows; i++)
	{
		sfp.y = hsd * i;
		for(j = 0; j < dst.cols; j++)
		{
			sfp.x = wsd * j;
			lx = (int)sfp.x;
			rx = lx + 1;
			uy = (int)sfp.y;
			dy = uy + 1;

			xf1 = (rx - sfp.x) * src.at<uchar>(uy, lx) + (sfp.x - lx) * src.at<uchar>(uy, rx);
			xf2 = (rx - sfp.x) * src.at<uchar>(dy, lx) + (sfp.x - lx) * src.at<uchar>(dy, rx);
			xyf = (dy - sfp.y) * xf1 + (sfp.y - uy) * xf2;
			dst.at<uchar>(i, j) = (uchar)xyf;
		}
	}
}

int main()
{
	Mat src, dst;
	Size dst_size = cv::Size(2000, 1000);

	src = cv::imread("img/img1.png", cv::IMREAD_COLOR);
	cvtColor(src, src, COLOR_BGR2GRAY);
	imshow("src", src);

	nearest_interpolation(src, dst, dst_size);
	imshow("nearest interpolation", dst);

	bilinear_interpolation(src, dst, dst_size);
	imshow("bilinear interpolation", dst);

	/* opencv的双线性内插接口 */
	cv::resize(src, dst, dst_size, 0, 0, INTER_LINEAR);
	imshow("opencv resize", dst);

	waitKey(0);
	return 0;
}