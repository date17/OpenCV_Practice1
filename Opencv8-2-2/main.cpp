#include <iostream>
#include <cmath>
#include <string>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

string win_src = "src";
string win_dst = "dst";
string win_dst823 = "dst823";
string win_dst825 = "dst825";

int main()
{
	string file_name = "C:\\Users\\date\\Downloads\\mono\\Text.bmp";

	Mat img_src = imread(file_name, 0); //グレースケール

	Mat img_dst; //最終出力画像
	Mat img_dst823; //8-2-3出力画像
	Mat img_dst825; //8-2-5出力画像

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

	//画像をコピー
	img_dst823 = img_tmp2;


	//ラベリング処理
	Mat img_lab;

	//ラベリング(戻り値にはラベル数-1が格納される)
	int nlabel = connectedComponents(img_tmp2, img_lab, 8);


	//面積比較
	vector<vector<vector<Point>>> contours(nlabel-1, vector<vector<Point>>()); //輪郭の座標を格納

	int max_Number = 0; //面積が最大のブロブであるラベルナンバーを格納

	double area, max_area = 0.0; //面積と最大面積
	//

	//重心の比較
	vector<Moments> m(nlabel-1);
	double area_moments;
	//入力画像の中心を入力
	double x_main = ((double)img_tmp2.cols - 1) / 2.0;
	double y_main = ((double)img_tmp2.rows - 1) / 2.0;

	//各ブロブの重心を格納する
	double x_g, y_g;

	//画像の中心との距離を格納する変数,　最小距離を格納する変数
	double D, D_min;

	//距離が一番短いブロブのラベル番号を格納
	int D_min_label;


	

	for (int i = 1; i <= nlabel-1; i++)
	{
		//特定のラベルのブロブを抜き出し(ラベルは1からだから、ループカウンタ + 1する）
		cv::compare(img_lab, i, img_dst, CMP_EQ);


		//輪郭を調査
		findContours(img_dst, contours.at(i - 1), RETR_EXTERNAL, CHAIN_APPROX_NONE);


		//面積を求める
		area = contourArea(Mat(contours.at(i - 1)[0]));

		//面積の比較
		if (area >= max_area)
		{
			max_Number = i;
			max_area = area;
		}

		//面積が150未満のものを削除（ノイズ除去）
		if (area < 150)
		{
			img_dst823 -= img_dst;
		}

		//距離の比較
		if (i == 1)
		{
			//各モーメントを一括で求める
			m[i - 1] = moments(img_dst, true);
			//面積
			area_moments = m[i - 1].m00;
			//重心
			x_g = m[i - 1].m10 / m[i - 1].m00;
			y_g = m[i - 1].m01 / m[i - 1].m00;
			//距離を求める
			D = sqrt(pow(x_g - x_main, 2.0) + pow(y_g - y_main, 2.0));
			D_min = D;

			D_min_label = i;
		}
		else
		{
			//各モーメントを一括で求める
			m[i - 1] = moments(img_dst, true);
			//面積
			area_moments = m[i - 1].m00;
			//重心
			x_g = m[i - 1].m10 / m[i - 1].m00;
			y_g = m[i - 1].m01 / m[i - 1].m00;
			//距離を求める
			D = sqrt(pow(x_g - x_main, 2.0) + pow(y_g - y_main, 2.0));

			if (D <= D_min)
			{
				D_min = D;

				D_min_label = i;
			}
		}
	}

	//面積が最大のラベル番号を抜き出し
	cout << max_Number << endl;

	//面積が最大のブロブを抜き出し
	cv::compare(img_lab, max_Number, img_dst, CMP_EQ);

	//画像中心ブロブの重心の間の距離が最小のブロブを抜き出し
	cv::compare(img_lab, D_min_label, img_dst825, CMP_EQ);

	////面積が最大であるブロブの重心と主軸の角度を求める
	////Moments関数を用いて、各種モーメントを一括で求める
	//Moments m = moments(img_dst, true);

	////面積
	//double area_moments = m.m00;
	////重心
	//double x_g = m.m10 / m.m00;
	//double y_g = m.m01 / m.m00;
	////主軸の角度
	//double ang = 0.5 * atan2(2.0 * m.mu11, m.mu20 - m.m02);

	//cout << "area : " << area_moments << endl;
	//cout << "x_g  : " << x_g << endl;
	//cout << "y_g  : " << y_g << endl;
	//cout << "ang  : " << ang << endl;

	//画面に画像を表示
	cv::namedWindow(win_src, WINDOW_AUTOSIZE);
	cv::namedWindow(win_dst, WINDOW_AUTOSIZE);
	/*namedWindow(win_dst823, WINDOW_AUTOSIZE);*/
	cv::namedWindow(win_dst825, WINDOW_AUTOSIZE);

	cv::imshow(win_src, img_tmp2);
	cv::imshow(win_dst, img_dst);
	/*imshow(win_dst823, img_dst823);*/
	cv::imshow(win_dst825, img_dst825);
	

	cv::waitKey(0);

	return 0;
}
