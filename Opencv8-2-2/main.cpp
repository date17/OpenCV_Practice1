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

	Mat img_src = imread(file_name, 0); //�O���[�X�P�[��

	Mat img_dst; //�ŏI�o�͉摜
	Mat img_dst823; //8-2-3�o�͉摜
	Mat img_dst825; //8-2-5�o�͉摜

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

	//�摜���R�s�[
	img_dst823 = img_tmp2;


	//���x�����O����
	Mat img_lab;

	//���x�����O(�߂�l�ɂ̓��x����-1���i�[�����)
	int nlabel = connectedComponents(img_tmp2, img_lab, 8);


	//�ʐϔ�r
	vector<vector<vector<Point>>> contours(nlabel-1, vector<vector<Point>>()); //�֊s�̍��W���i�[

	int max_Number = 0; //�ʐς��ő�̃u���u�ł��郉�x���i���o�[���i�[

	double area, max_area = 0.0; //�ʐςƍő�ʐ�
	//

	//�d�S�̔�r
	vector<Moments> m(nlabel-1);
	double area_moments;
	//���͉摜�̒��S�����
	double x_main = ((double)img_tmp2.cols - 1) / 2.0;
	double y_main = ((double)img_tmp2.rows - 1) / 2.0;

	//�e�u���u�̏d�S���i�[����
	double x_g, y_g;

	//�摜�̒��S�Ƃ̋������i�[����ϐ�,�@�ŏ��������i�[����ϐ�
	double D, D_min;

	//��������ԒZ���u���u�̃��x���ԍ����i�[
	int D_min_label;


	

	for (int i = 1; i <= nlabel-1; i++)
	{
		//����̃��x���̃u���u�𔲂��o��(���x����1���炾����A���[�v�J�E���^ + 1����j
		cv::compare(img_lab, i, img_dst, CMP_EQ);


		//�֊s�𒲍�
		findContours(img_dst, contours.at(i - 1), RETR_EXTERNAL, CHAIN_APPROX_NONE);


		//�ʐς����߂�
		area = contourArea(Mat(contours.at(i - 1)[0]));

		//�ʐς̔�r
		if (area >= max_area)
		{
			max_Number = i;
			max_area = area;
		}

		//�ʐς�150�����̂��̂��폜�i�m�C�Y�����j
		if (area < 150)
		{
			img_dst823 -= img_dst;
		}

		//�����̔�r
		if (i == 1)
		{
			//�e���[�����g���ꊇ�ŋ��߂�
			m[i - 1] = moments(img_dst, true);
			//�ʐ�
			area_moments = m[i - 1].m00;
			//�d�S
			x_g = m[i - 1].m10 / m[i - 1].m00;
			y_g = m[i - 1].m01 / m[i - 1].m00;
			//���������߂�
			D = sqrt(pow(x_g - x_main, 2.0) + pow(y_g - y_main, 2.0));
			D_min = D;

			D_min_label = i;
		}
		else
		{
			//�e���[�����g���ꊇ�ŋ��߂�
			m[i - 1] = moments(img_dst, true);
			//�ʐ�
			area_moments = m[i - 1].m00;
			//�d�S
			x_g = m[i - 1].m10 / m[i - 1].m00;
			y_g = m[i - 1].m01 / m[i - 1].m00;
			//���������߂�
			D = sqrt(pow(x_g - x_main, 2.0) + pow(y_g - y_main, 2.0));

			if (D <= D_min)
			{
				D_min = D;

				D_min_label = i;
			}
		}
	}

	//�ʐς��ő�̃��x���ԍ��𔲂��o��
	cout << max_Number << endl;

	//�ʐς��ő�̃u���u�𔲂��o��
	cv::compare(img_lab, max_Number, img_dst, CMP_EQ);

	//�摜���S�u���u�̏d�S�̊Ԃ̋������ŏ��̃u���u�𔲂��o��
	cv::compare(img_lab, D_min_label, img_dst825, CMP_EQ);

	////�ʐς��ő�ł���u���u�̏d�S�Ǝ厲�̊p�x�����߂�
	////Moments�֐���p���āA�e�탂�[�����g���ꊇ�ŋ��߂�
	//Moments m = moments(img_dst, true);

	////�ʐ�
	//double area_moments = m.m00;
	////�d�S
	//double x_g = m.m10 / m.m00;
	//double y_g = m.m01 / m.m00;
	////�厲�̊p�x
	//double ang = 0.5 * atan2(2.0 * m.mu11, m.mu20 - m.m02);

	//cout << "area : " << area_moments << endl;
	//cout << "x_g  : " << x_g << endl;
	//cout << "y_g  : " << y_g << endl;
	//cout << "ang  : " << ang << endl;

	//��ʂɉ摜��\��
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
