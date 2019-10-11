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
	//動画ファイルのパス
	string video_name = "C:\\Users\\date\\画像処理用\\動画\\604-1080.mp4";

	//動画ファイルを取り込むためのオブジェクトを宣言する
	VideoCapture cap;
	cap.open(video_name);

	//動画ファイルが開けたか調べる
	if (cap.isOpened() == false) 
	{
		cout << "ファイルが開けません" << endl;
		return -1;
	}

	//動画の詳細
	int width, height, count;
	double fps, time, time_now;
	

	width = cap.get(CAP_PROP_FRAME_WIDTH);		//フレームの幅
	height = cap.get(CAP_PROP_FRAME_HEIGHT);	//フレームの高さ
	count = cap.get(CAP_PROP_FRAME_COUNT);		//フレームの数
	fps = cap.get(CAP_PROP_FPS);				//フレームレート

	//再生時間を計算
	time = (double)count / fps;

	//動画再生から3秒、6秒、9秒の画像を切り取る
	vector<Mat> frames(3);
	Mat frame;					//フレームごとのに一度格納するオブジェクト
	int timecounter = 0, i = 0;	//break判定に使用

	cout << "toota" << endl;
	for (;;)
	{
		//1フレームを取り込む
		cap >> frame;			//capからframeへ

		//画像が空の時、無限ループを抜ける
		if (frame.empty() == true)
		{
			break;
		}

		//3秒、6秒、9秒の時
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
	
	//画像をグレースケールに変換して別々に格納
	Mat img_src1, img_src2, img_src3;

	cvtColor(frames[0], img_src1, COLOR_BGR2GRAY);
	cvtColor(frames[1], img_src2, COLOR_BGR2GRAY);
	cvtColor(frames[2], img_src3, COLOR_BGR2GRAY);

	//リサイズ
	resize(img_src1, img_src1, Size(300, 200));
	resize(img_src2, img_src2, Size(300, 200));
	resize(img_src3, img_src3, Size(300, 200));

	//1と2、2と3の差分画像を作成
	Mat img_diff12, img_diff23;
	absdiff(img_src1, img_src2, img_diff12);
	absdiff(img_src2, img_src3, img_diff23);

	//二値化処理をする
	Mat diff12_thresh, diff23_thresh;
	threshold(img_diff12, diff12_thresh, 30, 255, THRESH_BINARY);
	threshold(img_diff23, diff23_thresh, 30, 255, THRESH_BINARY);

	//膨張・収縮処理（今回はなし）

	//マスク画像の生成
	Mat img1_msk, img2_msk, img3_msk;

	//img_src2のマスク
	bitwise_and(diff12_thresh, diff23_thresh, img2_msk);
	//img_src1のマスク
	bitwise_xor(diff12_thresh, img2_msk, img1_msk);
	//img_src3のマスク
	bitwise_xor(diff23_thresh, img2_msk, img3_msk);

	//各画像の前景画像を作成
	Mat img1_front, img2_front, img3_front;
	bitwise_and(img_src1, img1_msk, img1_front);
	bitwise_and(img_src2, img2_msk, img2_front);
	bitwise_and(img_src3, img3_msk, img3_front);

	///////////////////////////////////////////////////////////////////////////////////////////////////

	cout << "start back" << endl;

	//背景画像の読み込み
	string file_back_name = "C:\\Users\\date\\画像処理用\\夕焼け背景.jpg";

	Mat img_back = imread(file_back_name, 1);		//カラー画像


	if (!img_back.data)
	{
		cout << "error" << endl;

		return -1;
	}

	//グレースケール変換
	cvtColor(img_back, img_back, COLOR_BGR2GRAY);


	//リサイズ
	resize(img_back, img_back, Size(300, 200));


	//前景画像のマスク画像を反転,背景画像のマスク画像の生成
	Mat img1_mskn, img2_mskn, img3_mskn;

	bitwise_not(img1_msk, img1_mskn);
	bitwise_not(img2_msk, img2_mskn);
	bitwise_not(img3_msk, img3_mskn);


	//背景画像と背景マスク画像を使用して背景画像から移動物体部分を取り出す。
	Mat back_msk1, back_msk2, back_msk3;

	bitwise_and(img_back, img1_mskn, back_msk1);		//3秒時の反転マスク画像を使い移動物体部分の切り取り
	bitwise_and(back_msk1, img2_mskn, back_msk2);		//6秒時の反転マスク画像を使い移動物体部分の切り取り
	bitwise_and(back_msk2, img3_mskn, back_msk3);		//9秒時の反転マスク画像を使い移動物体部分の切り取り


	//移動物体を挿入
	Mat img_dst;

	bitwise_or(back_msk3, img1_front, img_dst);
	bitwise_or(img_dst, img2_front, img_dst);
	bitwise_or(img_dst, img3_front, img_dst);
	
	//画像の表示
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