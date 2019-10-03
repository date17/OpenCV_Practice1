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

	int sum = 0; //�ݐϓx���̌v�Z�Ɏg�p
	int c[256] = { 0 }; //�x�����z
	int h[256] = { 0 }; //�ݐϓx��

	for (int i = 0; i < img_src.rows; i++)  //�x�����z�����߂�
	{
		for (int j = 0; j < img_src.cols; j++)
		{
			c[img_src.at<uchar>(i, j)]++;
		}
	}

	for (int i = 0; i < 256; i++) //�ݐϓx�������߂�B
	{
		sum = 0;
		for (int x = 0; x <= i; x++)
		{
			sum += c[x];
		}
		h[i] = sum;
	}

	//cout << "�x�����z" << endl;
	for (int i = 0; i < 256; i++)
	{
	//	cout << i << "�F" << c[i] << endl;
	}
	putchar('\n');

	//cout << "�ݐϓx��" << endl;
	for (int i = 0; i < 256; i++)
	{
	//	cout << i << "�F" << h[i] << endl;
	}

	//6-2-2 �ݐϓx���̃O���t�̕`��

	//�q�X�g�O�����̕\���p�A256*100�s�N�Z���A0�i���j�ŏ�����
	Mat img_hst;
	img_hst = Mat::zeros(100, 256, CV_8UC1);

	//�q�X�g�O�����𔒐��ŕ`��
	for (int i = 0; i < 256; i++)
	{
		line(img_hst, Point(i, img_hst.rows), Point(i, img_hst.rows - img_hst.rows * ((double)h[i] / (double)h[255])), Scalar(255, 255, 255));
	}



	
	imshow(win_src, img_hst);

	waitKey(0);

	return 0;
}