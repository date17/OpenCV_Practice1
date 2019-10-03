#define _CRT_SECURE_NO_WARNINGS
#define _USE__MATH_DEFINES
#include <iostream>
#include <string>
#include <cmath>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
string win_src = "src";

int main() 
{
	// 640*480 ピクセルの黒い画像
	Mat img_src = Mat::zeros(Size(640, 480), CV_8UC3);

	// ウィンドウ生成
	namedWindow(win_src, WINDOW_AUTOSIZE);

	// 点（0,0）と点（640,480）を結ぶ太さ5の黄色の線分
	line(img_src, Point(0, 0), Point(640, 480), Scalar(0, 255, 255), 5);

	// 中心座標（320, 240）、半径100、太さ3の青色の円
	circle(img_src, Point(320, 240), 100, Scalar(255, 0, 0), 3);

	// 中心座標（500, 100）、半径50、塗りつぶしの緑色の円
	circle(img_src, Point(500, 100), 50, Scalar(0, 255, 0), -1);

	// 左上座標（100, 150）、幅50、高さ150、太さ2の赤い短形
	rectangle(img_src, Rect(100, 150, 50, 150), Scalar(0, 0, 255), 2);

	// 左上座標（50, 350）、幅200、高さ50、塗りつぶしの紫色の短形
	rectangle(img_src, Rect(50, 350, 200, 50), Scalar(255, 0, 255), -1);

	// 左上座標（300, 450）、倍率3、太さ5の水色の文字列123
	putText(img_src, "123", Point(300, 450), 0, 3, Scalar(255, 255, 0), 5);


	// 表示
	imshow(win_src, img_src);

	// キー入力待ち
	waitKey(0);

	return 0;
}