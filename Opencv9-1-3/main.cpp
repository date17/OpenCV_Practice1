#include <iostream>
#include <string>
#include <cmath>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

string win_src1 = "src1";
string win_src2 = "src2";
string win_dst = "dst";

int main()
{
	string file_name1 = "C:\\Users\\date\\Downloads\\mono\\Lighthouse.bmp";
	string file_name2 = "C:\\Users\\date\\Downloads\\mono\\LAX.bmp";

	//���͉摜�̐���
	Mat img_src1 = imread(file_name1, 0);
	Mat img_src2 = imread(file_name2, 0);

	if (!img_src1.data || !img_src2.data)
	{
		cout << "error" << endl;

		return -1;
	}

	//�}�X�N�����̂��߂ɓ��͉摜���l��
	Mat img_mskg;
	threshold(img_src1, img_mskg, 200, 255, THRESH_BINARY_INV);

	//���͉摜1����}�X�N�摜�̕����������o��(�؂�o���摜1�̐���)
	Mat img_slm;
	bitwise_and(img_src1, img_mskg, img_slm);

	//�}�X�N�摜�̔��]
	bitwise_not(img_mskg, img_mskg);

	//���͉摜2���甽�]�}�X�N�摜�̕����������o���i�؂�o���摜2�̐����j
	Mat img_slm2;
	bitwise_and(img_src2, img_mskg, img_slm2);

	//�؂�o���摜�̍���
	Mat img_dst;
	bitwise_or(img_slm, img_slm2, img_dst);

	namedWindow(win_src1, WINDOW_AUTOSIZE);
	namedWindow(win_src2, WINDOW_AUTOSIZE);
	namedWindow(win_dst, WINDOW_AUTOSIZE);

	imshow(win_src1, img_src1);
	imshow(win_src2, img_src2);
	imshow(win_dst, img_dst);

	waitKey(0);

	return 0;
}