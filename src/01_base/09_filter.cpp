/* 滤波 */
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
	Mat img2 = Mat(img.size(), img.type());
	Mat img3 = Mat(img.size(), img.type());
	Mat img4 = Mat(img.size(), img.type());
	Mat img5 = Mat(img.size(), img.type());

	/* 均值滤波 */
    blur(img, img1, Size(3, 3));
	/* 高斯滤波 */
    GaussianBlur(img, img2, Size(3, 3), 3, 3);
	/* 中值滤波 */
	medianBlur(img, img3, 3);
	/* 双边滤波 */
	bilateralFilter(img, img4, 15, 150, 3);

	Mat kernel = (Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	filter2D(img, img5, img.depth(), kernel);

	imshow("image", img);
	imshow("image1", img1);
	imshow("image2", img2);
	imshow("image3", img3);
	imshow("image4", img4);
	imshow("image5", img5);

	Mat img_my = Mat(img.size(), img.type());
	for(int i = 1; i < img.rows - 1; i++)
	{
		for(int j = 1; j < img.cols - 1; j++)
		{
			int val;
			val = 0;
			val += img.at<Vec3b>(i - 1, j)[0];
			val += img.at<Vec3b>(i - 1, j + 1)[0];
			val += img.at<Vec3b>(i - 1, j - 1)[0];
			val += img.at<Vec3b>(i, j)[0];
			val += img.at<Vec3b>(i, j + 1)[0];
			val += img.at<Vec3b>(i, j - 1)[0];
			val += img.at<Vec3b>(i + 1, j)[0];
			val += img.at<Vec3b>(i + 1, j + 1)[0];
			val += img.at<Vec3b>(i + 1, j - 1)[0];
			val /= 9;
			img_my.at<Vec3b>(i, j)[0] = val;

			val = 0;
			val += img.at<Vec3b>(i - 1, j)[1];
			val += img.at<Vec3b>(i - 1, j + 1)[1];
			val += img.at<Vec3b>(i - 1, j - 1)[1];
			val += img.at<Vec3b>(i, j)[1];
			val += img.at<Vec3b>(i, j + 1)[1];
			val += img.at<Vec3b>(i, j - 1)[1];
			val += img.at<Vec3b>(i + 1, j)[1];
			val += img.at<Vec3b>(i + 1, j + 1)[1];
			val += img.at<Vec3b>(i + 1, j - 1)[1];
			val /= 9;
			img_my.at<Vec3b>(i, j)[1] = val;

			val = 0;
			val += img.at<Vec3b>(i - 1, j)[2];
			val += img.at<Vec3b>(i - 1, j + 1)[2];
			val += img.at<Vec3b>(i - 1, j - 1)[2];
			val += img.at<Vec3b>(i, j)[2];
			val += img.at<Vec3b>(i, j + 1)[2];
			val += img.at<Vec3b>(i, j - 1)[2];
			val += img.at<Vec3b>(i + 1, j)[2];
			val += img.at<Vec3b>(i + 1, j + 1)[2];
			val += img.at<Vec3b>(i + 1, j - 1)[2];
			val /= 9;
			img_my.at<Vec3b>(i, j)[2] = val;
		}
	}
	imshow("image_my", img_my);

	waitKey(0);
	return 0;
}
