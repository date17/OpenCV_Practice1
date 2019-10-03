# define _CRT_SECURE_NO_WARNINGS
# define _USE_MATH_DEFINES
# include <iostream>
# include <cmath>
# include <opencv2/opencv.hpp>
# include <string>

using namespace cv;
using namespace std;

string win_src = "src";

int main()
{
	Mat img_src = imread("C:\\Users\\date\\Desktop\\newImage.jpg", 0);

	namedWindow(win_src, WINDOW_AUTOSIZE);

	if (!img_src.data)
	{
		cout << "error!" << endl;

		return -1;
	}

	int sum = 0; //累積度数の計算に使用
	int c[256] = { 0 }; //度数分布
	int h[256] = { 0 }; //累積度数

	for (int i = 0; i < img_src.rows; i++)  //度数分布を求める
	{
		for (int j = 0; j < img_src.cols; j++)
		{
			c[img_src.at<uchar>(i, j)]++;
		}
	}

	for (int i = 0; i < 256; i++) //累積度数を求める。
	{
		sum = 0;
		for (int x = 0; x <= i; x++)
		{
			sum += c[x];
		}
		h[i] = sum;
	}

	//cout << "度数分布" << endl;
	for (int i = 0; i < 256; i++)
	{
	//	cout << i << "：" << c[i] << endl;
	}
	putchar('\n');

	//cout << "累積度数" << endl;
	for (int i = 0; i < 256; i++)
	{
	//	cout << i << "：" << h[i] << endl;
	}

	//6-2-2 累積度数のグラフの描画

	//ヒストグラムの表示用、256*100ピクセル、0（黒）で初期化
	Mat img_hst;
	img_hst = Mat::zeros(100, 256, CV_8UC1);

	//ヒストグラムを白線で描画
	for (int i = 0; i < 256; i++)
	{
		line(img_hst, Point(i, img_hst.rows), Point(i, img_hst.rows - img_hst.rows * ((double)h[i] / (double)h[255])), Scalar(255, 255, 255));
	}



	
	imshow(win_src, img_hst);

	waitKey(0);

	return 0;
}