#include <iostream>
#include <string>
#include <cmath>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat img_src = Mat::zeros(Size(8, 8), CV_8UC1);

	img_src.at<uchar>(1, 2) = 255;
	img_src.at<uchar>(2, 1) = 255;
	img_src.at<uchar>(2, 2) = 255;
	img_src.at<uchar>(2, 3) = 255;
	img_src.at<uchar>(3, 1) = 255;
	img_src.at<uchar>(3, 2) = 255;
	img_src.at<uchar>(3, 3) = 255;
	img_src.at<uchar>(4, 1) = 255;
	img_src.at<uchar>(4, 2) = 255;
	img_src.at<uchar>(4, 3) = 255;
	img_src.at<uchar>(4, 4) = 255;
	img_src.at<uchar>(5, 2) = 255;
	img_src.at<uchar>(5, 3) = 255;
	img_src.at<uchar>(5, 4) = 255;
	img_src.at<uchar>(5, 5) = 255;
	img_src.at<uchar>(6, 3) = 255;
	img_src.at<uchar>(6, 4) = 255;

	//�֊s�_�̒��o
	vector<vector<Point>> contours4;	//4�ߖT�̗֊s�_���i�[
	vector<vector<Point>> contours8;	//8�ߖT�̗֊s�_���i�[

	findContours(img_src, contours4, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE); //4�ߖT�̗֊s���o
	findContours(img_src, contours8, RETR_CCOMP, CHAIN_APPROX_NONE);	  //8�ߖT�̗֊s���o

	



	//���Ӓ������߂�
	double perimeter4 = arcLength(Mat(contours4[0]), true); //4�ߖT�̎��Ӓ�
	double perimeter8 = arcLength(Mat(contours8[0]), true); //8�ߖT�̎��Ӓ�

	cout << "4�ߖT�̎��Ӓ�" << perimeter4 << endl;
	cout << "8�ߖT�̎��Ӓ�" << perimeter8 << endl;

	resize(img_src, img_src,Size(), 2.0, 2.0); //�摜���c����{

	//�֊s�_�̒��o
	vector<vector<Point>> contours4_2;	//4�ߖT�̗֊s�_���i�[
	vector<vector<Point>> contours8_2;	//8�ߖT�̗֊s�_���i�[

	findContours(img_src, contours4_2, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE); //4�ߖT�̗֊s���o
	findContours(img_src, contours8_2, RETR_CCOMP, CHAIN_APPROX_NONE);	  //8�ߖT�̗֊s���o





	//���Ӓ������߂�
	double perimeter4_2 = arcLength(Mat(contours4_2[0]), true); //4�ߖT�̎��Ӓ�
	double perimeter8_2 = arcLength(Mat(contours8_2[0]), true); //8�ߖT�̎��Ӓ�

	cout << "4�ߖT�̎��Ӓ�" << perimeter4_2 << endl;
	cout << "8�ߖT�̎��Ӓ�" << perimeter8_2 << endl;


	waitKey(0);

	return 0;

}