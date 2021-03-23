/**
 ************************************
 * @file     : 01_lbp_feature.cpp
 * @author   : stxw
 * @date     : 2021-03-18
 ************************************
 * @brief :
 * 		LBP特征提取
 */

#include <stdio.h>
#include <string.h>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

void origin_LBP_feature(cv::InputArray src, cv::OutputArray dst);
double bilinear_interpolation(cv::InputArray src, double x, double y);
void circular_LBP_feature(cv::InputArray src, cv::OutputArray dst, int num_neighbor = 8, double radius = 1.0);
void rotation_invariant(cv::InputArray src, cv::OutputArray dst, int num_neighbor = 8);
void uniform_pattern(cv::InputArray src, cv::OutputArray dst, int num_neighbor = 8);
void histogram_LBP_feature(cv::InputArray src, cv::OutputArray dst, int num_patterns, int grid_w = 8, int grid_h = 8);

int main(int argc, char *argv[])
{
	cv::Mat src_img, dst;

	src_img = cv::imread("img/img1.png", cv::IMREAD_GRAYSCALE);
	cv::imshow("原图", src_img);

	origin_LBP_feature(src_img, dst);
	cv::imshow("原始LBP特征", dst);

	circular_LBP_feature(src_img, dst, 8, 1.0);
	cv::imshow("圆形LBP特征", dst);

	circular_LBP_feature(src_img, dst, 8, 1.0);
	rotation_invariant(dst, dst, 8);
	cv::imshow("圆形LBP特征进行旋转不变处理", dst);

	circular_LBP_feature(src_img, dst, 8, 1.0);
	rotation_invariant(dst, dst, 8);
	uniform_pattern(dst, dst, 8);
	// dst = dst * 4; /* 进行对比度增强 */
	cv::imshow("圆形LBP特征进行旋转不变处理，再进行统一模式编码", dst);

	circular_LBP_feature(src_img, dst, 8, 1.0);
	rotation_invariant(dst, dst, 8);
	uniform_pattern(dst, dst, 8);
	histogram_LBP_feature(dst, dst, 59, 8, 8);
	printf("histogram LBP特征的大小：(%d, %d, %d)\n", dst.size[0], dst.size[1], dst.channels());

	cv::waitKey();
	return 0;
}


/**
 * @brief : 提取图像的原始LBP特征
 * @param src : 输入的图像
 * @param dst : 图像src的原始LBP特征
 * @return : None
 */
void origin_LBP_feature(cv::InputArray src, cv::OutputArray dst)
{
	cv::Mat _src, _dst, border_src;
	int i, j;

	/* 填充图像的边界 */
	_src = src.getMat();
	cv::copyMakeBorder(_src, border_src, 1, 1, 1, 1, cv::BORDER_CONSTANT, cv::Scalar(0));
	dst.create(_src.rows, _src.cols, _src.type());
	_dst = dst.getMat();

	/* 循环处理每个像素 */
	for(i = 0; i < dst.rows(); i++)
	{
		for(j = 0; j < src.cols(); j++)
		{
			uchar center = border_src.at<uchar>(i + 1, j + 1);
			uchar lbp_code = 0;
			lbp_code |= ((border_src.at<uchar>(i + 0, j + 0) > center) << 7);
			lbp_code |= ((border_src.at<uchar>(i + 0, j + 1) > center) << 6);
			lbp_code |= ((border_src.at<uchar>(i + 0, j + 2) > center) << 5);
			lbp_code |= ((border_src.at<uchar>(i + 1, j + 2) > center) << 4);
			lbp_code |= ((border_src.at<uchar>(i + 2, j + 2) > center) << 3);
			lbp_code |= ((border_src.at<uchar>(i + 2, j + 1) > center) << 2);
			lbp_code |= ((border_src.at<uchar>(i + 2, j + 0) > center) << 1);
			lbp_code |= ((border_src.at<uchar>(i + 1, j + 0) > center) << 0);
			_dst.at<uchar>(i, j) = lbp_code;
		}
	}
}


/**
 * @brief : 提取图像的圆形LBP特征
 * @param src : 输入的图像
 * @param dst : 图像src的圆形LBP特征
 * @return : None
 */
void circular_LBP_feature(cv::InputArray src, cv::OutputArray dst, int num_neighbor, double radius)
{
	cv::Mat _src, _dst, border_src;
	int i, j, k, padding;
	double x, y, neighbor;

	_src = src.getMat();
	dst.create(_src.rows, _src.cols, _src.type());
	_dst = dst.getMat();
	/* 填充图像的边界 */
	padding = (int)radius + 1;
	cv::copyMakeBorder(_src, border_src, 
		padding, padding, padding, padding, cv::BORDER_CONSTANT, cv::Scalar(0));

	/* 循环处理每个像素 */
	for(i = 0; i < dst.rows(); i++)
	{
		for(j = 0; j < src.cols(); j++)
		{
			uchar center = border_src.at<uchar>(i + padding, j + padding);
			uchar lbp_code = 0;
			for(k = 0; k < num_neighbor; k++)
			{
				/* 根据公式计算第k个采样点的坐标，这个地方可以优化，不必每次都进行计算radius*cos，radius*sin */
				x = (double)j + radius * cos(2.0 * CV_PI * k / num_neighbor);
				y = (double)i + radius * sin(2.0 * CV_PI * k / num_neighbor);
				neighbor = bilinear_interpolation(src, x, y);
				lbp_code |= ((neighbor > center) << (num_neighbor - k - 1));
			}
			_dst.at<uchar>(i, j) = lbp_code;
		}
	}
}


/**
 * @brief : 利用双线性内插计算图像的浮点像素值
 * @param src : 需要插值的图像
 * @param x : x坐标
 * @param y : y坐标
 * @return : 图像src在浮点坐标(x, y)处的浮点像素值
 */
double bilinear_interpolation(cv::InputArray src, double x, double y)
{
	cv::Mat _src = src.getMat();
	if(x < 0 || x > _src.cols || y < 0 || y > _src.rows)
	{
		return 0;
	}

	/* 图像中与浮点像素最近的四个整数坐标值(lx:左x、rx:右x、uy:上y、dy:下y) */
	double lx = (int)x;
	double rx = lx + 1;
	double uy = (int)y;
	double dy = uy + 1;

	/* 先计算y方向的两个像素点值f1、f2，再计算xy两个方向上的像素点值 */
	double f1 = (rx - x) * _src.at<uchar>(uy, lx) + (x - lx) * _src.at<uchar>(uy, rx);
	double f2 = (rx - x) * _src.at<uchar>(dy, lx) + (x - lx) * _src.at<uchar>(dy, rx);
	double xy = (dy - y) * f1 + (y - uy) * f2;
	return xy;
}


/**
 * @brief : 对LBP特征图像进行旋转不变处理
 * @param src : 输入的LBP特征图像
 * @param dst : 进行旋转不变处理后的特征图像
 * @return : None
 */
void rotation_invariant(cv::InputArray src, cv::OutputArray dst, int num_neighbor)
{
	cv::Mat _src, _dst;
	int i, j, k;
	uchar current_value, min_value, temp;

	_src = src.getMat();
	dst.create(_src.rows, _src.cols, _src.type());
	_dst = dst.getMat();

	/* 循环处理每个像素 */
	for(i = 0; i < _src.rows; i++)
	{
		for(j = 0; j < _dst.cols; j++)
		{
			current_value = _src.at<uchar>(i, j);
			min_value = current_value;
			for(k = 1; k < num_neighbor; k++)
			{
				/* 循环右移k位 */
				temp = (current_value >> k) | (current_value << (num_neighbor - k));
				temp &= (0xff >> (8 - num_neighbor));
				if(temp < min_value)
				{
					min_value = temp;
				}
			}
			_dst.at<uchar>(i, j) = min_value;
		}
	}
}


/**
 * @brief : 对LBP特征进行统一模式编码
 * @param src : 输入的LBP特征
 * @param dst : 用统一模式编码的LBP特征
 * @return : None
 */
void uniform_pattern(cv::InputArray src, cv::OutputArray dst, int num_neighbor)
{
	cv::Mat _src, _dst;
	int i, j, k, hop_time;
	uchar kind, curr_bit, next_bit;
	uchar table[256] = {0};

	/* 计算编码映射关系 */
	kind = 1; /* 用0来表示混合模式类，所以从1开始计算统一模式类 */
	for(i = 0; i < 256; i++)
	{
		/* 计算跳变次数 */
		hop_time = 0;
		for(j = 0; j < num_neighbor; j++)
		{
			/* 计算i的二进制第j位，以及j的下一位--第(j + 1) % num_neighbor位 */
			curr_bit = (i >> j) & 0x01;
			next_bit = (i >> ((j + 1) % num_neighbor)) & 0x01;
			if(curr_bit != next_bit)
			{
				hop_time++;
			}
		}
		/* 跳变次数小于等于2，说明是统一模式类 */
		if(hop_time <= 2)
		{
			table[i] = kind;
			kind++;
		}
	}

	_src = src.getMat();
	dst.create(_src.rows, _src.cols, _src.type());
	_dst = dst.getMat();
	/* 对输入的LBP特征进行统一模式编码 */
	for(i = 0; i < _src.rows; i++)
	{
		for(j = 0; j < _src.cols; j++)
		{
			_dst.at<uchar>(i, j) = table[_dst.at<uchar>(i, j)];
		}
	}
}


/**
 * @brief : 提取图像的LBP特征统计直方图
 * @param src : 输入的图像LBP特征
 * @param dst : 图像的LBP特征统计直方图，大小为(grid_w, grid_h, num_patterns)
 * @param num_patterns : LBP模式的种类
 * @param grid_w : 分块后的宽度，图像最终分成 grid_w×grid_h 个块
 * @param grid_h : 分块后的高度
 * @return : None
 */
void histogram_LBP_feature(cv::InputArray src, cv::OutputArray dst, int num_patterns, int grid_w, int grid_h)
{
	cv::Mat _src, _dst, block;
	int i, j;
	int weight, height;
	int dst_row_index;
	int32_t block_histogram[256];
	uchar *data, *dst_row_ptr;

	_src = src.getMat();
	dst.create(cv::Size(grid_w, grid_h), CV_32SC(num_patterns));
	_dst = dst.getMat();
	weight = (int)(_src.cols / grid_w);
	height = (int)(_src.rows / grid_h);

	dst_row_ptr = _dst.data;
	for(i = 0; i < grid_h; i++)
	{
		for(j = 0; j < grid_w; j++)
		{
			/* 对图像切块 */
			block = cv::Mat(_src, cv::Rect(j * weight, i * height, weight, height));
			/* 计算块的直方图 */
			memset(block_histogram, 0x00, sizeof(block_histogram));
			for(data = block.data; data != block.dataend; data++)
			{
				block_histogram[*data]++;
			}
			/* 将块的直方图存到dst的一行里 */
			memcpy(dst_row_ptr, block_histogram, 4 * num_patterns);
			/* dst_row_ptr指向dst的下一行 */
			dst_row_ptr = dst_row_ptr +  4 * num_patterns;
		}
	}
}
