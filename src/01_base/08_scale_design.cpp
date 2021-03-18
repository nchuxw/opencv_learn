/* 绘制图案 */
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <vector>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main()
{
	//Mat img = imread(argv[1], IMREAD_COLOR);
	Mat img = Mat(600, 1000, CV_8UC3, Scalar(100, 100, 100));

	//line(img, Point(0, 0), Point(img.cols, img.rows), Scalar(0, 0, 255), 5);
	line(img, Point(0, 0), Point(img.cols, img.rows), Scalar(0, 0, 255), 5, LINE_AA);

	Rect rect(50, 200, 200, 300);
	rectangle(img, rect, Scalar(255, 0, 0), 3);

	circle(img, Point(500, 300), 150, Scalar(255, 255, 0), 5);

	ellipse(img, Point(500, 300), Size(200, 100), 0, 0, 360, Scalar(0, 255, 0), 3);

	vector<vector<Point> > pts = {{Point(100, 100), Point(200, 100), Point(300, 200), Point(100, 200), Point(100, 100)}};
	fillPoly(img, pts, Scalar(255, 255, 100));

	putText(img, "Hello", Point(500, 100), FONT_HERSHEY_SCRIPT_COMPLEX, 2.0, Scalar(255, 255, 0));

	imshow("image", img);


	Mat pane = Mat(600, 1000, CV_8UC3, Scalar::all(0));
	srand(time(NULL));
	for(int i = 0; i < 1000; i++)
	{
		Point p1, p2;
		Scalar color(rand() % 256, rand() % 256, rand() % 256);
		p1.x = rand() % 1000;
		p2.x = rand() % 1000;
		p1.y = rand() % 600;
		p2.y = rand() % 600;
		line(pane, p1, p2, color, 2);
		imshow("pane", pane);
		if((char)waitKey(50) > 0)
		{
			break;
		}
	}
	waitKey(0);
	return 0;
}
