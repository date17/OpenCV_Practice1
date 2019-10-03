#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;
using namespace cv;

string win_src = "src";
string win_dst = "dst";

int main()
{
	string src_name = "C:\\Users\\date\\画像処理用\\Lenna.jpg";

	string dst_name = "opencv6-2-4";

	Mat img_src = imread(src_name, 1); //カラー画像の読み込み

	if(!img_src.data)
	{
		cout << "error" << endl;

		return -1;
	}

	Mat img_dst = Mat(img_src.rows, img_src.cols, CV_8UC3); //出力画像

	vector<Mat> dst_split(3);

	split(img_src, dst_split); //一度RGBを各色に分ける

	//γ変換
	double ganma;

	cout << "γの値を入力してください。" << endl;
	scanf_s("%lf", &ganma);

	for (int i = 0; i < img_src.rows; i++)
	{
		for (int j = 0; j < img_src.cols; j++)
		{
			double b;
			double g;
			double r;

			//B成分
			b = 255 * pow((double)dst_split[0].at<uchar>(i, j) / (double)255, 1.0 / ganma);
			

			if (b < 0)
			{
				b = 0;
			}
			if (b > 255)
			{
				b = 255;
			}


			//G成分
			g = 255 * pow((double)dst_split[1].at<uchar>(i, j) / (double)255, 1.0 / ganma);

			if (g < 0)
			{
				g = 0;
			}
			if (g > 255)
			{
				g = 255;
			}


			//R成分
			r = 255 * pow((double)dst_split[2].at<uchar>(i, j) / (double)255, 1.0 / ganma);

			if (r < 0)
			{
				r = 0;
			}
			if (r > 255)
			{
				r = 255;
			}


			dst_split[0].at<uchar>(i, j) = (int)b;
			dst_split[1].at<uchar>(i, j) = (int)g;
			dst_split[2].at<uchar>(i, j) = (int)r;

		}
	}


	//各成分を合体
	merge(vector<Mat>{dst_split[0], dst_split[1], dst_split[2]}, img_dst);


	//画面に表示
	namedWindow(win_src, WINDOW_AUTOSIZE);
	namedWindow(win_dst, WINDOW_AUTOSIZE);

	imshow(win_src, img_src);
	imshow(win_dst, img_dst);

	waitKey(0);

	return 0;
}