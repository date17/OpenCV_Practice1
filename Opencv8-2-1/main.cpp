#include <iostream>
#include <cmath>
#include <string>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

string win_src = "src";
string win_dst = "dst";

int main()
{
	string file_name = "C:\\Users\\date\\Downloads\\mono\\Text.bmp";

	Mat img_src = imread(file_name, 0); //グレースケール

	Mat img_dst; //最終出力画像

	if (!img_src.data)
	{
		cout << "error" << endl;

		return -1;
	}

	//2値化処理
	int Thresh = 100;
	threshold(img_src, img_src, Thresh, 255, THRESH_BINARY);

	//膨張縮小処理によりノイズを削除
	Mat img_tmp1, img_tmp2;
	Mat element8 = (Mat_<uchar>(3, 3) << 1, 1, 1, 1, 1, 1, 1, 1, 1); //8近傍

	//クロージング処理により穴をふさぐ
	morphologyEx(img_src, img_tmp1, MORPH_CLOSE, element8, Point(-1, -1), 1);
	//オープニング処理によりノイズを削除
	morphologyEx(img_tmp1, img_tmp2, MORPH_OPEN, element8, Point(-1, -1), 1);


	//ラベリング処理
	Mat img_lab;

	//ラベリング(戻り値にはラベル数-1が格納される)
	int nlabel = connectedComponents(img_tmp2, img_lab); 

	//ラベルの抜き出し(第2引数に指定した値のラベルのデータを出力)
	compare(img_lab, 26, img_dst, CMP_EQ);

	namedWindow(win_src, WINDOW_AUTOSIZE);
	namedWindow(win_dst, WINDOW_AUTOSIZE);

	imshow(win_src, img_tmp2);
	imshow(win_dst, img_dst);


	waitKey(0);

	return 0;

}