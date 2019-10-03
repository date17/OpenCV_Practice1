#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;

string win_src = "src";
string win_dst = "dst";
string win_tmp = "tmp";

int main()
{
	string file_name = "C:\\Users\\date\\画像処理用\\Lighthousemono.jpg";

	Mat img_src = imread(file_name, 0); //グレースケール

	if (!img_src.data)
	{
		cout << "error" << endl;

		return -1;
	}

	Mat img_tmp;
	Mat img_dst;

	GaussianBlur(img_src, img_tmp, Size(5, 5), 1, 1); //ガウシアンフィルタ適用（標準偏差はそのまま）
	GaussianBlur(img_src, img_dst, Size(5, 5), 3, 3);

	namedWindow(win_src, WINDOW_AUTOSIZE);
	namedWindow(win_tmp, WINDOW_AUTOSIZE);
	namedWindow(win_dst, WINDOW_AUTOSIZE);

	imshow(win_src, img_src);
	imshow(win_tmp, img_tmp);
	imshow(win_dst, img_dst);

	waitKey(0);

	return 0;
}