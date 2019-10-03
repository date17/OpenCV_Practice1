#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <string>

using namespace std;

// openCV �ۑ�5-1-1

//RGB����YCbCr��Y�̕ϊ�
int changeY(int a[3][1]) 
{
	int y = 0;

	y = (0.257 * a[0][0]) + (0.504 * a[1][0]) + (0.098 * a[2][0]) + 16;

	return y;
}

//RGB����YCbCr��Cb�̕ϊ�
int changeCb(int a[3][1])
{
	int cb = 0;

	cb = (-0.148 * a[0][0]) + (-0.291 * a[1][0]) + (0.439 * a[2][0]) + 128;

	return cb;
}

//RGB����YCbCr��Cr�̕ϊ�
int changeCr(int a[3][1])
{
	int cr = 0; 
	
	cr = (0.439 * a[0][0]) + (-0.368 * a[1][0]) + (-0.071 * a[2][0]) + 128;

	return cr;
}


int main() {
	const int width = 2400, height = 240;
	// char image[height][width]; //�摜�p�z��
	string filename = "kadai5_1_3.ppm";     //�t�@�C����
	ofstream fout(filename);            //�t�@�C�����J��



	//�e�F��RGB�̒l
	int white[3][1] = { 255,255,255 };		//���F
	int yellow[3][1] = { 255,255,0 };		//���F
	int cian[3][1] = { 0, 255, 255 };		//�V�A��
	int green[3][1] = { 0,255,0 };			//��
	int mazenda[3][1] = { 255, 0,255 };		//�}�[���_
	int red[3][1] = { 255,0,0 };			//��
	int brue[3][1] = { 0,0,255 };			//��
	int brack[3][1] = { 0,0,0 };			//��

	//�o�b�t�@
	int buffer;

	/*5-1-2
	//R��B�����ւ����摜�ɂ���
	//��
	buffer = white[0][0];
	white[0][0] = white[2][0];
	white[2][0] = buffer;
	//���F
	buffer = yellow[0][0];
	yellow[0][0] = yellow[2][0];
	yellow[2][0] = buffer;
	//�V�A��
	buffer = cian[0][0];
	cian[0][0] = cian[2][0];
	cian[2][0] = buffer;
	//��
	buffer = green[0][0];
	green[0][0] = green[2][0];
	green[2][0] = buffer;
	//�}�[���_
	buffer = mazenda[0][0];
	mazenda[0][0] = mazenda[2][0];
	mazenda[2][0] = buffer;
	//��
	buffer = white[0][0];
	white[0][0] = white[2][0];
	white[2][0] = buffer;
	//��
	buffer = red[0][0];
	red[0][0] = red[2][0];
	red[2][0] = buffer;
	//��
	buffer = brue[0][0];
	brue[0][0] = brue[2][0];
	brue[2][0] = buffer;
	//��
	buffer = brack[0][0];
	brack[0][0] = brack[2][0];
	brack[2][0] = buffer;
	*/

	/*5-1-3*/
	//RGB����YCbCr�ɕϊ�
	int whiteYCbCr[3][1] = {changeY(white), changeCb(white), changeCr(white)};		//����YCbCr
	int yellowYCbCr[3][1] = { changeY(yellow), changeCb(yellow), changeCr(yellow) };		//���F��YCbCr
	int cianYCbCr[3][1] = { changeY(cian), changeCb(cian), changeCr(cian) };		//�V�A����YCbCr
	int greenYCbCr[3][1] = { changeY(green), changeCb(green), changeCr(green) };		//�΂�YCbCr
	int mazendaYCbCr[3][1] = { changeY(mazenda), changeCb(mazenda), changeCr(mazenda) };		//�}�[���_��YCbCr
	int redYCbCr[3][1] = { changeY(red), changeCb(red), changeCr(red) };			//�Ԃ�YCbCr
	int brueYCbCr[3][1] = { changeY(brue), changeCb(brue), changeCr(brue) };		//��YCbCr
	int brackYCbCr[3][1] = { changeY(brack), changeCb(brack), changeCr(brack) };		//����YCbCr


	//�t�@�C���̏o��
	fout << "P3" << endl;
	fout << "800" << " " << "240" << endl;
	fout << "255" << endl;
	for (int y = 0; y < height; y++) {
		int x = 0;
		if (y >= 210)
		{
			while (x < 2400)
			{
				//fout << brack[0][0] << " " << brack[1][0] << " " << brack[2][0] << " ";
				fout << brackYCbCr[0][0] << " " << brackYCbCr[1][0] << " " << brackYCbCr[2][0] << " ";
				x += 3;
			}
			fout << endl;
		}
		else if (y >= 180)
		{
			while (x < 2400)
			{
				//fout << brue[0][0] << " " << brue[1][0] << " " << brue[2][0] << " ";
				fout << brueYCbCr[0][0] << " " << brueYCbCr[1][0] << " " << brueYCbCr[2][0] << " ";
				x += 3;
			}
			fout << endl;
		}
		else if (y >= 150)
		{
			while (x < 2400)
			{
				//fout << red[0][0] << " " << red[1][0] << " " << red[2][0] << " ";
				fout << redYCbCr[0][0] << " " << redYCbCr[1][0] << " " << redYCbCr[2][0] << " ";
				x += 3;
			}
			fout << endl;
		}
		else if (y >= 120)
		{
			while (x < 2400)
			{
				//fout << mazenda[0][0] << " " << mazenda[1][0] << " " << mazenda[2][0] << " ";
				fout << mazendaYCbCr[0][0] << " " << mazendaYCbCr[1][0] << " " << mazendaYCbCr[2][0] << " ";
				x += 3;
			}
			fout << endl;
		}
		else if (y >= 90)
		{
			while (x < 2400)
			{
				//fout << green[0][0] << " " << green[1][0] << " " << green[2][0] << " ";
				fout << greenYCbCr[0][0] << " " << greenYCbCr[1][0] << " " << greenYCbCr[2][0] << " ";
				x += 3;
			}
			fout << endl;
		}
		else if (y >= 60)
		{
			while (x < 2400)
			{
				//fout << cian[0][0] << " " << cian[1][0] << " " << cian[2][0] << " ";
				fout << cianYCbCr[0][0] << " " << cianYCbCr[1][0] << " " << cianYCbCr[2][0] << " ";
				x += 3;
			}
			fout << endl;
		}
		else if (y >= 30)
		{
			while (x < 2400)
			{
				//fout << yellow[0][0] << " " << yellow[1][0] << " " << yellow[2][0] << " ";
				fout << yellowYCbCr[0][0] << " " << yellowYCbCr[1][0] << " " << yellowYCbCr[2][0] << " ";
				x += 3;
			}
			fout << endl;
		}
		else
		{
			while (x < 2400)
			{
				//fout << white[0][0] << " " << white[1][0] << " " << white[2][0] << " ";
				fout << whiteYCbCr[0][0] << " " << whiteYCbCr[1][0] << " " << whiteYCbCr[2][0] << " ";
				x += 3;
			}
			fout << endl;
		}

	}
	fout.flush(); //�t�@�C����ۑ�����
	fout.close(); //�t�@�C�������

	
}