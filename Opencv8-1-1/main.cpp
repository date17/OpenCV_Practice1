#include <iostream>
#include <string>
#include <cmath>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
	//問題の入力画像の作成
	Mat img_src = Mat::zeros(Size(8, 8), CV_8UC1);

	img_src.at<uchar>(1, 2) = 255;
	img_src.at<uchar>(2, 1) = 255;
	img_src.at<uchar>(2, 2) = 255;
	img_src.at<uchar>(2, 3) = 255;
	img_src.at<uchar>(3, 1) = 255;
	img_src.at<uchar>(3, 2) = 255;
	img_src.at<uchar>(3, 3) = 255;
	img_src.at<uchar>(4, 1) = 255;
	img_src.at<uchar>(4, 2) = 255;
	img_src.at<uchar>(4, 3) = 255;
	img_src.at<uchar>(4, 4) = 255;
	img_src.at<uchar>(5, 2) = 255;
	img_src.at<uchar>(5, 3) = 255;
	img_src.at<uchar>(5, 4) = 255;
	img_src.at<uchar>(5, 5) = 255;
	img_src.at<uchar>(6, 3) = 255;
	img_src.at<uchar>(6, 4) = 255;

	//ここまで

	vector<vector<Point>> contours; //検出された輪郭を保持する配列
	
	//ブロフの輪郭を求める関数 (最も外側の輪郭のみ抽出、すべての輪郭点を完全に格納)
	findContours(img_src, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);

	for (int i = 0; i < sizeof(contours) / sizeof(contours[0]); i++)
	{
		cout << contours[i] << endl;
	}

	string win = "win";

	namedWindow(win, WINDOW_AUTOSIZE);

	imshow(win, img_src);
	waitKey(0);

	return 0;
}