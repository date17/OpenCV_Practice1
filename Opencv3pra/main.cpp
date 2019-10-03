#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <string>

using namespace std;

// openCV 課題5-1-1

//RGBからYCbCrのYの変換
int changeY(int a[3][1]) 
{
	int y = 0;

	y = (0.257 * a[0][0]) + (0.504 * a[1][0]) + (0.098 * a[2][0]) + 16;

	return y;
}

//RGBからYCbCrのCbの変換
int changeCb(int a[3][1])
{
	int cb = 0;

	cb = (-0.148 * a[0][0]) + (-0.291 * a[1][0]) + (0.439 * a[2][0]) + 128;

	return cb;
}

//RGBからYCbCrのCrの変換
int changeCr(int a[3][1])
{
	int cr = 0; 
	
	cr = (0.439 * a[0][0]) + (-0.368 * a[1][0]) + (-0.071 * a[2][0]) + 128;

	return cr;
}


int main() {
	const int width = 2400, height = 240;
	// char image[height][width]; //画像用配列
	string filename = "kadai5_1_3.ppm";     //ファイル名
	ofstream fout(filename);            //ファイルを開く



	//各色のRGBの値
	int white[3][1] = { 255,255,255 };		//白色
	int yellow[3][1] = { 255,255,0 };		//黄色
	int cian[3][1] = { 0, 255, 255 };		//シアン
	int green[3][1] = { 0,255,0 };			//緑
	int mazenda[3][1] = { 255, 0,255 };		//マゼンダ
	int red[3][1] = { 255,0,0 };			//赤
	int brue[3][1] = { 0,0,255 };			//青
	int brack[3][1] = { 0,0,0 };			//黒

	//バッファ
	int buffer;

	/*5-1-2
	//RとBを入れ替えた画像にする
	//白
	buffer = white[0][0];
	white[0][0] = white[2][0];
	white[2][0] = buffer;
	//黄色
	buffer = yellow[0][0];
	yellow[0][0] = yellow[2][0];
	yellow[2][0] = buffer;
	//シアン
	buffer = cian[0][0];
	cian[0][0] = cian[2][0];
	cian[2][0] = buffer;
	//緑
	buffer = green[0][0];
	green[0][0] = green[2][0];
	green[2][0] = buffer;
	//マゼンダ
	buffer = mazenda[0][0];
	mazenda[0][0] = mazenda[2][0];
	mazenda[2][0] = buffer;
	//白
	buffer = white[0][0];
	white[0][0] = white[2][0];
	white[2][0] = buffer;
	//赤
	buffer = red[0][0];
	red[0][0] = red[2][0];
	red[2][0] = buffer;
	//青
	buffer = brue[0][0];
	brue[0][0] = brue[2][0];
	brue[2][0] = buffer;
	//黒
	buffer = brack[0][0];
	brack[0][0] = brack[2][0];
	brack[2][0] = buffer;
	*/

	/*5-1-3*/
	//RGBからYCbCrに変換
	int whiteYCbCr[3][1] = {changeY(white), changeCb(white), changeCr(white)};		//白のYCbCr
	int yellowYCbCr[3][1] = { changeY(yellow), changeCb(yellow), changeCr(yellow) };		//黄色のYCbCr
	int cianYCbCr[3][1] = { changeY(cian), changeCb(cian), changeCr(cian) };		//シアンのYCbCr
	int greenYCbCr[3][1] = { changeY(green), changeCb(green), changeCr(green) };		//緑のYCbCr
	int mazendaYCbCr[3][1] = { changeY(mazenda), changeCb(mazenda), changeCr(mazenda) };		//マゼンダのYCbCr
	int redYCbCr[3][1] = { changeY(red), changeCb(red), changeCr(red) };			//赤のYCbCr
	int brueYCbCr[3][1] = { changeY(brue), changeCb(brue), changeCr(brue) };		//青のYCbCr
	int brackYCbCr[3][1] = { changeY(brack), changeCb(brack), changeCr(brack) };		//黒のYCbCr


	//ファイルの出力
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
	fout.flush(); //ファイルを保存する
	fout.close(); //ファイルを閉じる

	
}