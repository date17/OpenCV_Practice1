#include <iostream>
#include <string>
#include <cmath>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

string win_src1 = "src1";
string win_src2 = "src2";
string win_dst = "dst";

int main()
{
	string file_name1 = "C:\\Users\\date\\Downloads\\mono\\Lighthouse.bmp";
	string file_name2 = "C:\\Users\\date\\Downloads\\mono\\LAX.bmp";

	//入力画像の生成
	Mat img_src1 = imread(file_name1, 0);
	Mat img_src2 = imread(file_name2, 0);

	if (!img_src1.data || !img_src2.data)
	{
		cout << "error" << endl;

		return -1;
	}

	//マスク生成のために入力画像を二値化
	Mat img_mskg;
	threshold(img_src1, img_mskg, 200, 255, THRESH_BINARY_INV);

	//入力画像1からマスク画像の部分だけ取り出す(切り出し画像1の生成)
	Mat img_slm;
	bitwise_and(img_src1, img_mskg, img_slm);

	//マスク画像の反転
	bitwise_not(img_mskg, img_mskg);

	//入力画像2から反転マスク画像の部分だけ取り出す（切り出し画像2の生成）
	Mat img_slm2;
	bitwise_and(img_src2, img_mskg, img_slm2);

	//切り出し画像の合成
	Mat img_dst;
	bitwise_or(img_slm, img_slm2, img_dst);

	namedWindow(win_src1, WINDOW_AUTOSIZE);
	namedWindow(win_src2, WINDOW_AUTOSIZE);
	namedWindow(win_dst, WINDOW_AUTOSIZE);

	imshow(win_src1, img_src1);
	imshow(win_src2, img_src2);
	imshow(win_dst, img_dst);

	waitKey(0);

	return 0;
}