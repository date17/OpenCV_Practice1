#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>
#include <cmath>

using namespace std;
using namespace cv;

string win_src = "src";
string win_dst = "dst";

int main()
{
	string src_name = "C:\\Users\\date\\�摜�����p\\LENNAmono.jpg";

	Mat img_src = imread(src_name, 0); //�O���[�X�P�[��

	if (!img_src.data)
	{
		cout << "error" << endl;

		return -1;
	}

	Mat img_dst = Mat(img_src.rows, img_src.cols, CV_8UC1);

	int select;

	cout << "�ǂ̋^���Z�W���������܂����H\n1 : �����_���f�B�U�����O\n2 : �덷�g�U�f�B�U�����O\n3 : �g�D�I�f�B�U�����O" << endl;

	scanf_s("%d", &select);

	if (select == 1)
	{
		//�����_���f�B�U�����O
		for (int i = 0; i < img_src.rows; i++)
		{
			for (int j = 0; j < img_src.cols; j++)
			{
				if (img_src.at<uchar>(i, j) < rand() % 256)
				{
					img_dst.at<uchar>(i, j) = 0;
				}
				else
				{
					img_dst.at<uchar>(i, j) = 255;
				}
			}
		}
	}
	else if (select == 2)
	{
		//�덷�g�U�f�B�U�����O
		int treash = 128;
		int v = 0;
		int error = 0;;

		for (int i = 0; i < img_src.rows; i++)
		{
			for (int j = 0; j < img_src.cols; j++)
			{
				v = img_src.at<uchar>(i, j) + error;

				if (v < treash)
				{
					img_dst.at<uchar>(i, j) = 0;

					error = v;
				}
				else
				{
					img_dst.at<uchar>(i, j) = 255;

					error = v - 255;
				}
			}
		}
	}
	else if (select == 3)
	{
		//�g�D�I�f�B�U�����O
		const int N = 4;
		int bayer[N][N] = { { 0, 8, 2, 10 },
							{ 12, 4, 14, 6},
							{ 3, 11, 1, 9 },
							{ 15, 7, 13, 5} };

		//bayer�z���0~255�ɕϊ�
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				bayer[i][j] *= N * N;
			}
		}

		for (int i = 0; i < img_src.rows; i++)
		{
			for (int j = 0; j < img_src.cols; j++)
			{
				if (img_src.at<uchar>(i, j) < bayer[i % N][j % N])
				{
					img_dst.at<uchar>(i, j) = 0;
				}
				else
				{
					img_dst.at<uchar>(i, j) = 255;
				}
			}
		}
	}
	else
	{
		cout << "error select number" << endl;

		return -1;
	}

	//�摜�\��
	namedWindow(win_src, WINDOW_AUTOSIZE);
	namedWindow(win_dst, WINDOW_AUTOSIZE);

	imshow(win_src, img_src);
	imshow(win_dst, img_dst);

	waitKey(0);

	return 0;
}