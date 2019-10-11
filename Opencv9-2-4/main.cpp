#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <cmath>

using namespace cv;
using namespace std;

string win_src_back = "src_back";
string win_dst = "dst";
string win_src1 = "src1";
string win_src2 = "src2";
string win_src3 = "src3";

int main()
{
	//����t�@�C���̃p�X
	string video_name = "C:\\Users\\date\\�摜�����p\\����\\604-1080.mp4";

	//����t�@�C������荞�ނ��߂̃I�u�W�F�N�g��錾����
	VideoCapture cap;
	cap.open(video_name);

	//����t�@�C�����J���������ׂ�
	if (cap.isOpened() == false) 
	{
		cout << "�t�@�C�����J���܂���" << endl;
		return -1;
	}

	//����̏ڍ�
	int width, height, count;
	double fps, time, time_now;
	

	width = cap.get(CAP_PROP_FRAME_WIDTH);		//�t���[���̕�
	height = cap.get(CAP_PROP_FRAME_HEIGHT);	//�t���[���̍���
	count = cap.get(CAP_PROP_FRAME_COUNT);		//�t���[���̐�
	fps = cap.get(CAP_PROP_FPS);				//�t���[�����[�g

	//�Đ����Ԃ��v�Z
	time = (double)count / fps;

	//����Đ�����3�b�A6�b�A9�b�̉摜��؂���
	vector<Mat> frames(3);
	Mat frame;					//�t���[�����Ƃ̂Ɉ�x�i�[����I�u�W�F�N�g
	int timecounter = 0, i = 0;	//break����Ɏg�p

	cout << "toota" << endl;
	for (;;)
	{
		//1�t���[������荞��
		cap >> frame;			//cap����frame��

		//�摜����̎��A�������[�v�𔲂���
		if (frame.empty() == true)
		{
			break;
		}

		//3�b�A6�b�A9�b�̎�
		if ((int)(cap.get(CAP_PROP_POS_MSEC) / 1000) == timecounter + 3)
		{
			frame.copyTo(frames[i]);
			i++;

			timecounter += 3;

			cout << timecounter << endl;
		}

		if (timecounter >= 9)
		{
			break;

			cout << "break" << endl;
		}

	}
	
	//�摜���O���[�X�P�[���ɕϊ����ĕʁX�Ɋi�[
	Mat img_src1, img_src2, img_src3;

	cvtColor(frames[0], img_src1, COLOR_BGR2GRAY);
	cvtColor(frames[1], img_src2, COLOR_BGR2GRAY);
	cvtColor(frames[2], img_src3, COLOR_BGR2GRAY);

	//���T�C�Y
	resize(img_src1, img_src1, Size(300, 200));
	resize(img_src2, img_src2, Size(300, 200));
	resize(img_src3, img_src3, Size(300, 200));

	//1��2�A2��3�̍����摜���쐬
	Mat img_diff12, img_diff23;
	absdiff(img_src1, img_src2, img_diff12);
	absdiff(img_src2, img_src3, img_diff23);

	//��l������������
	Mat diff12_thresh, diff23_thresh;
	threshold(img_diff12, diff12_thresh, 30, 255, THRESH_BINARY);
	threshold(img_diff23, diff23_thresh, 30, 255, THRESH_BINARY);

	//�c���E���k�����i����͂Ȃ��j

	//�}�X�N�摜�̐���
	Mat img1_msk, img2_msk, img3_msk;

	//img_src2�̃}�X�N
	bitwise_and(diff12_thresh, diff23_thresh, img2_msk);
	//img_src1�̃}�X�N
	bitwise_xor(diff12_thresh, img2_msk, img1_msk);
	//img_src3�̃}�X�N
	bitwise_xor(diff23_thresh, img2_msk, img3_msk);

	//�e�摜�̑O�i�摜���쐬
	Mat img1_front, img2_front, img3_front;
	bitwise_and(img_src1, img1_msk, img1_front);
	bitwise_and(img_src2, img2_msk, img2_front);
	bitwise_and(img_src3, img3_msk, img3_front);

	///////////////////////////////////////////////////////////////////////////////////////////////////

	cout << "start back" << endl;

	//�w�i�摜�̓ǂݍ���
	string file_back_name = "C:\\Users\\date\\�摜�����p\\�[�Ă��w�i.jpg";

	Mat img_back = imread(file_back_name, 1);		//�J���[�摜


	if (!img_back.data)
	{
		cout << "error" << endl;

		return -1;
	}

	//�O���[�X�P�[���ϊ�
	cvtColor(img_back, img_back, COLOR_BGR2GRAY);


	//���T�C�Y
	resize(img_back, img_back, Size(300, 200));


	//�O�i�摜�̃}�X�N�摜�𔽓],�w�i�摜�̃}�X�N�摜�̐���
	Mat img1_mskn, img2_mskn, img3_mskn;

	bitwise_not(img1_msk, img1_mskn);
	bitwise_not(img2_msk, img2_mskn);
	bitwise_not(img3_msk, img3_mskn);


	//�w�i�摜�Ɣw�i�}�X�N�摜���g�p���Ĕw�i�摜����ړ����̕��������o���B
	Mat back_msk1, back_msk2, back_msk3;

	bitwise_and(img_back, img1_mskn, back_msk1);		//3�b���̔��]�}�X�N�摜���g���ړ����̕����̐؂���
	bitwise_and(back_msk1, img2_mskn, back_msk2);		//6�b���̔��]�}�X�N�摜���g���ړ����̕����̐؂���
	bitwise_and(back_msk2, img3_mskn, back_msk3);		//9�b���̔��]�}�X�N�摜���g���ړ����̕����̐؂���


	//�ړ����̂�}��
	Mat img_dst;

	bitwise_or(back_msk3, img1_front, img_dst);
	bitwise_or(img_dst, img2_front, img_dst);
	bitwise_or(img_dst, img3_front, img_dst);
	
	//�摜�̕\��
	namedWindow(win_src1, WINDOW_AUTOSIZE);
	namedWindow(win_src2, WINDOW_AUTOSIZE);
	namedWindow(win_src3, WINDOW_AUTOSIZE);
	namedWindow(win_src_back, WINDOW_AUTOSIZE);
	namedWindow(win_dst, WINDOW_AUTOSIZE);

	imshow(win_src1, img_src1);
	imshow(win_src2, img_src2);
	imshow(win_src3, img_src3);
	imshow(win_src_back, img_back);
	imshow(win_dst, img_dst);

	waitKey(0);


	return 0;

}