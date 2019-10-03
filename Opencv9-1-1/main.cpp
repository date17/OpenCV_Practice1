#include <iostream>
#include <string>
#include <cmath>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

string win_src1 = "src1";
string win_src2 = "src2";
string win_dst = "dst";

int main()
{
	string file_name1 = "C:\\Users\\date\\Downloads\\mono\\Airplane.bmp";
	string file_name2 = "C:\\Users\\date\\Downloads\\mono\\Text.bmp";

	Mat img_src1 = imread(file_name1, 0);
	Mat img_src2 = imread(file_name2, 0);

	if (!img_src1.data || !img_src2.data)
	{
		cout << "error" << endl;

		return -1;
	}

	//“ü—Í‰æ‘œ‚Ìã‰º‚ð•‚É‚·‚é
	for (int i = 0; i < img_src1.rows / 2; i++)
	{
		for (int j = 0; j < img_src1.cols; j++)
		{
			img_src1.at<uchar>(i, j) = 0;
		}
	}

	for (int i = img_src2.rows / 2; i < img_src2.rows; i++)
	{
		for (int j = 0; j < img_src2.cols; j++)
		{
			img_src2.at<uchar>(i, j) = 0;
		}
	}


	Mat img_dst;

	bitwise_and(img_src1, img_src2, img_dst);

	namedWindow(win_src1, WINDOW_AUTOSIZE);
	namedWindow(win_src2, WINDOW_AUTOSIZE);
	namedWindow(win_dst, WINDOW_AUTOSIZE);

	imshow(win_src1, img_src1);
	imshow(win_src2, img_src2);
	imshow(win_dst, img_dst);

	waitKey(0);

	return 0;
}