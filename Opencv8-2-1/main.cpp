#include <iostream>
#include <cmath>
#include <string>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

string win_src = "src";
string win_dst = "dst";

int main()
{
	string file_name = "C:\\Users\\date\\Downloads\\mono\\Text.bmp";

	Mat img_src = imread(file_name, 0); //�O���[�X�P�[��

	Mat img_dst; //�ŏI�o�͉摜

	if (!img_src.data)
	{
		cout << "error" << endl;

		return -1;
	}

	//2�l������
	int Thresh = 100;
	threshold(img_src, img_src, Thresh, 255, THRESH_BINARY);

	//�c���k�������ɂ��m�C�Y���폜
	Mat img_tmp1, img_tmp2;
	Mat element8 = (Mat_<uchar>(3, 3) << 1, 1, 1, 1, 1, 1, 1, 1, 1); //8�ߖT

	//�N���[�W���O�����ɂ�茊���ӂ���
	morphologyEx(img_src, img_tmp1, MORPH_CLOSE, element8, Point(-1, -1), 1);
	//�I�[�v�j���O�����ɂ��m�C�Y���폜
	morphologyEx(img_tmp1, img_tmp2, MORPH_OPEN, element8, Point(-1, -1), 1);


	//���x�����O����
	Mat img_lab;

	//���x�����O(�߂�l�ɂ̓��x����-1���i�[�����)
	int nlabel = connectedComponents(img_tmp2, img_lab); 

	//���x���̔����o��(��2�����Ɏw�肵���l�̃��x���̃f�[�^���o��)
	compare(img_lab, 26, img_dst, CMP_EQ);

	namedWindow(win_src, WINDOW_AUTOSIZE);
	namedWindow(win_dst, WINDOW_AUTOSIZE);

	imshow(win_src, img_tmp2);
	imshow(win_dst, img_dst);


	waitKey(0);

	return 0;

}