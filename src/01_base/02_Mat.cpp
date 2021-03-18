/* Mat的基本操作 */
#include <stdio.h>
#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat mat1 = Mat(2, 2, CV_8UC3, Scalar(0, 0, 255));
	cout << "mat1 =" << endl << mat1 << endl;

	int size[3] = {2, 2};
	Mat mat2 = Mat(2, size, CV_8UC1, Scalar::all(255));
	cout << "mat2 =" << endl << mat2 << endl;

	Mat mat3 = Mat(4, 4, CV_8UC3);
	cout << "mat3 =" << endl << mat3 << endl;
	cout << endl;

	Mat mat_e = Mat::eye(4, 4, CV_8UC1);
	Mat mat_o = Mat::ones(4, 4, CV_8UC1);
	Mat mat_z = Mat::zeros(4, 4, CV_8UC1);
	cout << "E =" << endl << mat_e << endl;
	cout << "O =" << endl << mat_o << endl;
	cout << "Z =" << endl << mat_z << endl;
	cout << endl;

	Mat row_clone = mat_e.row(2).clone();
	// Mat row_clone;
	// mat_e.row(2).copyTo(row_clone);
	cout << "row_clone =" << endl << row_clone << endl;
	cout << endl;
	
	Mat mat_rand = Mat::zeros(4, 4, CV_8UC1);
	randu(mat_rand, Scalar::all(0), Scalar::all(255));
	cout << "mat_rand =" << endl << mat_rand << endl;
	cout << endl;

	Point2f p2f = Point2f(5, 1);
	cout << "point(2D) = " << p2f << endl;

	Point3f p3f = Point3f(5, 1, 7);
	cout << "point(3D) = " << p3f << endl;
	cout << endl;

	vector<double> vet_dou;
	vet_dou.push_back((double)CV_PI);
	vet_dou.push_back(2);
	vet_dou.push_back(3.01);
	cout << "vet_dou = " << endl << Mat(vet_dou) << endl;
	cout << endl;

	vector<Point2f> vet_p2d(10);
	for(int i = 0; i < (int)vet_p2d.size(); i++)
	{
		vet_p2d[i] = Point2d(i * 7, i % 3);
	}
	cout << "vet_p2d = " << endl << Mat(vet_p2d) << endl;
	cout << endl;

	Mat m1 = (Mat_<float>(2, 3) << 1.2, 0.4, 2.9, 2.0, 1.3, 2.2);
	printf("m1.rows: %d\n", m1.rows);
	printf("m1.cols: %d\n", m1.cols);
	printf("m1.channels(): %d\n", m1.channels());
	printf("m1.depth(): %d\n", m1.depth());
	printf("m1.elemSize(): %d\n", m1.elemSize());
	printf("m1.elemSize1(): %d\n", m1.elemSize1());

	printf("m1.size: [");
	for(int i = 0; i < m1.dims; i++)
	{
		printf("%d ", m1.size[i]);
	}
	printf("]\n");
	printf("m1.step: [");
	for(int i = 0; i < m1.dims; i++)
	{
		printf("%d ", m1.step[i]);
	}
	printf("]\n");
	cout << "m1 =" << endl << m1 << endl;
	cout << endl;

	Mat m2 = (Mat_<float>(3, 4) << 1.2, 0.4, 2.9, 2.0, 1.3, 2.2, 1.2, 0.4, 2.9, 2.0, 1.3, 2.2);
	cout << "m2 =" << endl << m2 << endl;
	cout << endl;

	Mat m3 = m1 * m2;
	cout << "m3 =" << endl << m3 << endl;
	cout << endl;
	
	return 0;
}
