#define _CRT_SECURE_NO_WARNINGS
#define _USE__MATH_DEFINES
#include <iostream>
#include <string>
#include <cmath>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
string win_src = "src";

int main() 
{
	// 640*480 �s�N�Z���̍����摜
	Mat img_src = Mat::zeros(Size(640, 480), CV_8UC3);

	// �E�B���h�E����
	namedWindow(win_src, WINDOW_AUTOSIZE);

	// �_�i0,0�j�Ɠ_�i640,480�j�����ԑ���5�̉��F�̐���
	line(img_src, Point(0, 0), Point(640, 480), Scalar(0, 255, 255), 5);

	// ���S���W�i320, 240�j�A���a100�A����3�̐F�̉~
	circle(img_src, Point(320, 240), 100, Scalar(255, 0, 0), 3);

	// ���S���W�i500, 100�j�A���a50�A�h��Ԃ��̗ΐF�̉~
	circle(img_src, Point(500, 100), 50, Scalar(0, 255, 0), -1);

	// ������W�i100, 150�j�A��50�A����150�A����2�̐Ԃ��Z�`
	rectangle(img_src, Rect(100, 150, 50, 150), Scalar(0, 0, 255), 2);

	// ������W�i50, 350�j�A��200�A����50�A�h��Ԃ��̎��F�̒Z�`
	rectangle(img_src, Rect(50, 350, 200, 50), Scalar(255, 0, 255), -1);

	// ������W�i300, 450�j�A�{��3�A����5�̐��F�̕�����123
	putText(img_src, "123", Point(300, 450), 0, 3, Scalar(255, 255, 0), 5);


	// �\��
	imshow(win_src, img_src);

	// �L�[���͑҂�
	waitKey(0);

	return 0;
}