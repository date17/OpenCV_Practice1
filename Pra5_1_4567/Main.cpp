#include <opencv2\opencv.hpp>
#include <iostream>
#include <string>
#include <cmath>
using namespace std;
using namespace cv;


int main() 
{
	String src_name = "C:\\Users\\date\\Downloads\\Pepper.jpg"; //���͉摜�̃p�X

	Mat img_src = imread(src_name, 1); //�摜�̓ǂݍ��݁i�J���[�j

	String dst_name = "kadai_5_1_7.png"; //�o�͉摜�̖��O�i�ۑ�5-1�j
	Mat img_dst; //�o�͉摜

	if (!img_src.data) {
		cout << "error" << endl;
		return -1;
	}

	

	Mat img_HSV;

	cvtColor(img_src, img_HSV, COLOR_BGR2HSV);

	vector<Mat> img_spl;

	split(img_HSV, img_spl);

	Mat img_HSVv, img_HSVh, img_HSVs; //HSV��Ԃ̊e�`�����l�����Ƃɕ������f�[�^���i�[����Mat�N���X

	img_HSVv = img_spl[2];	//���x�i���邳�j
	img_HSVh = img_spl[0];	//�F���i�F�����j
	img_HSVs = img_spl[1];	//�ʓx�i�N�₩���j

	int getValue = 0;


	cout << "�ǂ��ύX���܂����H" << endl;
	cout << "�F���F0  �ʓx:1  ���x�F2  ����͂��Ă�������" << endl;

	printf("���́@�F�@"); scanf_s("%d", &getValue);

	while (getValue != 0 && getValue != 1 && getValue != 2)
	{ 
		cout << "���͂Ɍ�肪����܂�!!!!!!!!" << endl;
		cout << "�ǂ��ύX���܂����H" << endl;
		cout << "�F���F0  �ʓx:1  ���x�F2  ����͂��Ă�������" << endl;

		printf("���́@�F�@"); scanf_s("%d", &getValue);
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

	//�E�B���h�E�̐���
	namedWindow("win_src", WINDOW_AUTOSIZE);
	namedWindow("win_dst", WINDOW_AUTOSIZE);

	imshow("win_src", img_src);
	imshow("win_dst", img_dst);

	imwrite(dst_name, img_dst);

	waitKey(0);

	return 0;

}