/* 膨胀和腐蚀 */
#include <stdio.h>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

void call_back_deal(int num, void *vdata)
{
    struct node
    {
        Mat img, img1;
        int elm_size;
    };

    node *data = (node *)vdata;
    int s = data->elm_size + 1;
    Mat st_elm = getStructuringElement(MORPH_RECT, Size(s, s));
    dilate(data->img, data->img1, st_elm);
    erode(data->img, data->img1, st_elm);
    imshow("image1", data->img1);
}

int main()
{
    struct node
    {
        Mat img, img1;
        int elm_size;
    };
    
    node data;
    data.elm_size = 1;
    data.img = imread("img/img1.png", IMREAD_COLOR);
	data.img1 = Mat(data.img.size(), data.img.type());

    namedWindow("image1", WINDOW_AUTOSIZE);
    createTrackbar("size:", "image1", &data.elm_size, 5, call_back_deal, (void *)&data);
    call_back_deal(0, (void *)&data);

    imshow("image", data.img);
    waitKey(0);
    return 0;
}
