#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>
#include <cmath>

using namespace std;
using namespace cv;

//表示する画像ボックスの名前

string win_src = "src"; 
string win_dst = "dst";


int changeR(int a) //r成分用　折れ線型トーンカーブ
{
	if (a < 128) 
	{
		return 0;
	}
	else if (128 <= a && 193 < a)
	{
		return (51 / 13) * a - (51 * 127 / 13);
	}
	else
	{
		return 255;
	}
}

int changeG(int a) //g成分用　台形型トーンカーブ
{
	if (a < 64)
	{
		return (255 / 63) * a;
	}
	else if (64 <= a && a < 192)
	{
		return 255;
	}
	else
	{
		return -(255 / 63) * a + (255 * 255 / 63);
	}
}

int changeB(int a) //b成分用　逆折れ線型トーンカーブ
{
	if (a < 64)
	{
		return 255;
	}
	else if (64 <= a && a < 128)
	{
		return -(255 * 63) * a + (255 * 127 / 63);
	}
	else
	{
		return 0;
	}
}

int main()
{
	string src_name = "C:\\Users\\date\\Desktop\\newImage.jpg";

	string dst_name = "changeRGB.png";

	Mat img_src = imread(src_name, 0);

	if (!img_src.data)
	{
		cout << "error" << endl;

		return -1;
	}

	Mat changeRGB = Mat(img_src.rows,img_src.cols,CV_8UC3);  //rgbに疑似カラー変換したデータを格納していく

	


	for (int i = 0; i < img_src.rows; i++)
	{
		for (int j = 0; j < img_src.cols; j++) 
		{
			int img_src_value = img_src.at<uchar>(i, j);

			changeRGB.at<Vec3b>(i, j) = Vec3b(changeB(img_src_value), changeG(img_src_value), changeR(img_src_value));
		}
	}

	namedWindow(win_src, WINDOW_AUTOSIZE);
	namedWindow(win_dst, WINDOW_AUTOSIZE);

	imshow(win_src, img_src);
	imshow(win_dst, changeRGB);

	waitKey(0);

	return 0;
}
