#include <opencv2\opencv.hpp>
#include <iostream>
#include <string>
#include <cmath>
using namespace std;
using namespace cv;


int main() 
{
	String src_name = "C:\\Users\\date\\Downloads\\Pepper.jpg"; //入力画像のパス

	Mat img_src = imread(src_name, 1); //画像の読み込み（カラー）

	String dst_name = "kadai_5_1_7.png"; //出力画像の名前（課題5-1）
	Mat img_dst; //出力画像

	if (!img_src.data) {
		cout << "error" << endl;
		return -1;
	}

	

	Mat img_HSV;

	cvtColor(img_src, img_HSV, COLOR_BGR2HSV);

	vector<Mat> img_spl;

	split(img_HSV, img_spl);

	Mat img_HSVv, img_HSVh, img_HSVs; //HSV空間の各チャンネルごとに分けたデータを格納するMatクラス

	img_HSVv = img_spl[2];	//明度（明るさ）
	img_HSVh = img_spl[0];	//色相（色合い）
	img_HSVs = img_spl[1];	//彩度（鮮やかさ）

	int getValue = 0;


	cout << "どれを変更しますか？" << endl;
	cout << "色相：0  彩度:1  明度：2  を入力してください" << endl;

	printf("入力　：　"); scanf_s("%d", &getValue);

	while (getValue != 0 && getValue != 1 && getValue != 2)
	{ 
		cout << "入力に誤りがあります!!!!!!!!" << endl;
		cout << "どれを変更しますか？" << endl;
		cout << "色相：0  彩度:1  明度：2  を入力してください" << endl;

		printf("入力　：　"); scanf_s("%d", &getValue);
	}

	if (getValue == 2)
	{
		for (int i = 0; i < img_HSVv.rows; i++)
		{
			for (int j = 0; j < img_HSVv.cols; j++)
			{
				img_HSVv.at<uchar>(i, j) += 30;

				if (img_HSVv.at<uchar>(i, j) < 255)
				{
					img_HSVv.at<uchar>(i, j) = 255;
				}
			}
		}
	}
	else if (getValue == 1)
	{
		for (int i = 0; i < img_HSVs.rows; i++)
		{
			for (int j = 0; j < img_HSVs.cols; j++)
			{
				img_HSVs.at<uchar>(i, j) += 30;

				if (img_HSVs.at<uchar>(i, j) < 255)
				{
					img_HSVs.at<uchar>(i, j) = 255;
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < img_HSVh.rows; i++)
		{
			for (int j = 0; j < img_HSVh.cols; j++)
			{
				img_HSVh.at<uchar>(i, j) += 30;

				if (img_HSVh.at<uchar>(i, j) < 179)
				{
					img_HSVh.at<uchar>(i, j) = 179;
				}
			}
		}
	}

	merge(vector<Mat>{img_HSVh, img_HSVs, img_HSVv}, img_dst);

	//ウィンドウの生成
	namedWindow("win_src", WINDOW_AUTOSIZE);
	namedWindow("win_dst", WINDOW_AUTOSIZE);

	imshow("win_src", img_src);
	imshow("win_dst", img_dst);

	imwrite(dst_name, img_dst);

	waitKey(0);

	return 0;

}