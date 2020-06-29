/* 卷积和池化 */
#include "test.h"
#define MAX(a, b) ((a) < (b) ? (b) : (a))

int main()
{
	int i, j;
	Mat img = imread("img/img1.png", cv::IMREAD_COLOR);
	imshow("src", img);

	Mat des = Mat(img.rows, img.cols, img.type());
	Mat kernel = (Mat_<char>(3, 3) << 2, -1, 2, -1, -4, -1, 2, -1, 2);
	filter2D(img, des, img.depth(), kernel);
	cvtColor(des, des, cv::COLOR_BGR2GRAY);
	imshow("des_con", des);
	// imwrite("./img/des_con.png", des);

	Mat des2 = Mat(des.rows / 2, des.cols / 2, des.type());
	for(i = 0; i < des2.rows; i++)
	{
		for(j = 0; j < des2.cols; j++)
		{
			uchar max = 0;
			max = MAX(max, des.at<uchar>(i * 2, j * 2));
			max = MAX(max, des.at<uchar>(i * 2 + 1, j * 2));
			max = MAX(max, des.at<uchar>(i * 2, j * 2 + 1));
			max = MAX(max, des.at<uchar>(i * 2 + 1, j * 2 + 1));
			des2.at<uchar>(i, j) = max;
		}
	}
	imshow("des_pool", des2);
	// imwrite("./img/des_pool.png", des2);

	waitKey(0);
	return 0;
}