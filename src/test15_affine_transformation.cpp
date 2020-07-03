/* 图像的仿射变换 */
#include "test.h"

/* 原图路径 */
char img_path[100] = "img/tl.png";
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
	if(x < 0 || x > src.rows || y < 0 || y > src.cols)
	{
		return 0;
	}

	/* 表示在原图中与浮点像素最近的四个整数坐标值(ux:上x、dx:下x、ly:左y、ry:右y) */
	double ux = (int)x;
	double dx = ux + 1;
	double ly = (int)y;
	double ry = ly + 1;

	/* y方向的两个像素点值，xy两个方向上的像素点值 */
	double f1 = (dx - x) * src.at<uchar>(ux, ly) + (x - ux) * src.at<uchar>(dx, ly);
	double f2 = (dx - x) * src.at<uchar>(ux, ry) + (x - ux) * src.at<uchar>(dx, ry);
	double xy = (ry - y) * f1 + (y - ly) * f2;
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
			dst_vec = (Mat_<double>(1, 3) << i, j, 1);
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
