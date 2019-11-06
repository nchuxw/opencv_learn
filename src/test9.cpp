#include "test.h"

int main()
{
	Mat img = imread("img/img1.png", IMREAD_COLOR);
	Mat img1 = Mat(img.size(), img.type());
	Mat img2 = Mat(img.size(), img.type());
	Mat img3 = Mat(img.size(), img.type());
	Mat img4 = Mat(img.size(), img.type());
	Mat img5 = Mat(img.size(), img.type());

    blur(img, img1, Size(3, 3));
    GaussianBlur(img, img2, Size(3, 3), 3, 3);
	medianBlur(img, img3, 3);
	bilateralFilter(img, img4, 15, 150, 3);

	Mat kernel = (Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	filter2D(img4, img5, img4.depth(), kernel);

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
