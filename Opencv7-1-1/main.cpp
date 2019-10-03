#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <cmath>

using namespace cv;
using namespace std;

string win_src = "src";
string win_dst = "dst";

int main()
{
	Mat img_src = Mat(8, 8, CV_8UC1); //8*8

	Mat img_dst = Mat(8,8,CV_8UC1);

	//p114 図7.7を作成
	for (int i = 0; i < 8; i++) 
	{
		for (int j = 0; j < 8; j++)
		{
			if ((2 <= i && i <= 5) && (2 <= j && j <= 5))
			{
				img_src.at<uchar>(i, j) = 255;
			}
			else
			{
				img_src.at<uchar>(i, j) = 0;
			}
		}
	}

	



	//sobelフィルタを適用
	Mat img_tmp;

	Sobel(img_src, img_tmp, CV_32F, 0, 1, 3);

	for (int i = 0; i < img_tmp.rows; i++)
	{
		for (int j = 0; j < img_tmp.cols; j++)
		{
			img_dst.at<uchar>(i, j) = (int)img_tmp.at<uchar>(i, j);
		}
	}

	//convertScaleAbs(img_tmp, img_dst, 1, 0);

	namedWindow(win_src, WINDOW_AUTOSIZE);
	namedWindow(win_dst, WINDOW_AUTOSIZE);

	imshow(win_src, img_src);
	imshow(win_dst, img_dst);

	imwrite("src.png", img_src);
	imwrite("dst2.png", img_dst);

	waitKey(0);

	return 0;

}