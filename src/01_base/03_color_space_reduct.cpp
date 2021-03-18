/* 简单颜色空间缩小 */
#include <stdio.h>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat img = imread("img/img1.png", IMREAD_COLOR);
	int divideWith = 0;
	imshow("image", img);
	waitKey(100);
	while(scanf("%d", &divideWith) != EOF)
	{
		unsigned char table[256];
		for(int i = 0; i < 256; i++)
		{
			table[i] = (unsigned char)(i - i % divideWith);
		}

		int nrow = img.rows;
		int ncol = img.cols * img.channels();
		unsigned char* p;

		double t = (double)getTickCount();
		for(int i = 0; i < nrow; i++)
		{
			p = img.ptr<unsigned char>(i);
			for(int j = 0; j < ncol; j++)
			{
				p[j] = table[p[j]];
			}
		}
		t = ((double)getTickCount() - t) / getTickFrequency();
		printf("Time passed in:%lfs\n", t);
		imshow("image2", img);
		waitKey(100);
	}
	return 0;
}
