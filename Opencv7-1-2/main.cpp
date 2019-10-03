#include <opencv2/opencv.hpp>
#include <string>
#include <cmath>
#include <iostream>

using namespace cv;
using namespace std;

string win_src = "src";
string win_dst = "dst";

int main()
{
	string src_name = "C:\\Users\\date\\source\\repos\\Opencv7-1-1\\src.png";
	string dst_name = "dst.png";

	Mat img_tmp, img_dst;

	Mat img_src = imread(src_name, 0); //�O���[�X�P�[���摜��ǂݍ���

	if (!img_src.data)
	{
		cout << "error" << endl;

		return -1;
	}

	//�N�s���I�y���[�^���쐬
	float k = 1.0;
	Mat op = Mat::ones(3, 3, CV_32F) * -1;
	op.at<float>(1, 1) = 1 + 8 * -k;

	//�ݒ肵���I�y���[�^�Ńt�B���^����������
	filter2D(img_src, img_tmp, CV_32F, op);
	convertScaleAbs(img_tmp, img_dst, 1, 0);


	//�摜�̕\��
	namedWindow(win_src, WINDOW_AUTOSIZE);
	namedWindow(win_dst, WINDOW_AUTOSIZE);

	imshow(win_src, img_src);
	imshow(win_dst, img_dst);

	imwrite(dst_name, img_dst);
	waitKey(0);


	

	return 0;
}