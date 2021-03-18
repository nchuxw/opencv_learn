/* 图像的仿射变换 */
#include <stdio.h>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

/* 原图路径 */
char img_path[100] = "img/affine.png";
/* 变换后图像的大小 */
Size img_out_size = {300, 300};
/* 仿射矩阵 */
double T[3][3] = 
{
	{1, 0, 0},
	{0, 1, 0},
	{0, 0, 1},
};

/* 利用双线性内插计算原图中的浮点像素值 */
double bilinear_interpolation(Mat src, double x, double y)
{
	if(x < 0 || x > src.cols || y < 0 || y > src.rows)
	{
		return 0;
	}

	/* 表示在原图中与浮点像素最近的四个整数坐标值(lx:左x、rx:右x、uy:上y、dy:下y) */
	double lx = (int)x;
	double rx = lx + 1;
	double uy = (int)y;
	double dy = uy + 1;

	/* 先计算y方向的两个像素点值f1、f2，再计算xy两个方向上的像素点值 */
	double f1 = (rx - x) * src.at<uchar>(uy, lx) + (x - lx) * src.at<uchar>(uy, rx);
	double f2 = (rx - x) * src.at<uchar>(dy, lx) + (x - lx) * src.at<uchar>(dy, rx);
	double xy = (dy - y) * f1 + (y - uy) * f2;
	return xy;
}

int main()
{
	int i, j;
	Mat src = imread(img_path, cv::IMREAD_GRAYSCALE);
	src.rows -= 2;
	Mat dst = Mat(img_out_size, src.type());

	Mat t_s = Mat(3, 3, CV_64FC1, T);
	Mat t_inv = Mat(3, 3, CV_64FC1);
	invert(t_s, t_inv); // t_inv为仿射矩阵的逆矩阵

	Mat src_vec, dst_vec;
	for(i = 0; i < dst.rows; i++)
	{
		for(j = 0; j < dst.cols; j++)
		{
			/* 目标图像的坐标向量 */
			dst_vec = (Mat_<double>(1, 3) << j, i, 1);
			/* 计算dst_vec对应于原图中的坐标向量src_vec */
			src_vec = dst_vec * t_inv;
			/* 计算目标图像的浮点像素值 */
			dst.at<uchar>(i, j) = (uchar)bilinear_interpolation(src, src_vec.at<double_t>(0, 0), src_vec.at<double_t>(0, 1));
		}
	}
	imshow("dst", dst);
	imwrite("img/t_1.png", dst);

	waitKey(0);
	return 0;
}
