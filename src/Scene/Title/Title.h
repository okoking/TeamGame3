#pragma once

//画像の種類
enum TITLE_IMAGE_NUM
{
	TITLE_BACK,		//背景
	TITLE_TITLE1,	//タイトル1
	TITLE_TITLE2,	//タイトル2
	TITLE_START,	//スタート
	TITLE_EASY,		//イージー(4×4)
	TITLE_NORMAL,	//ノーマル(5×5)
	TITLE_HARD,		//ハード(6×6)
	TITLE_PILLAR1,	//柱1
	TITLE_PILLAR2,	//柱2
	TITLE_ARROW1,	//矢印1
	TITLE_ARROW2,	//矢印2

	TITLE_IMAGE_MAX_NUM,	//画像数
};

//画像パス
const char TITLE_IMAGE_PATH[TITLE_IMAGE_MAX_NUM][255] =
{
	"data/title/back.png",			//背景
	"data/title/titletext1.png",	//タイトル1
	"data/title/titletext2.png",	//タイトル2
	"data/title/pressenter.png",	//スタート
	"data/title/easy.png",			//イージー
	"data/title/normal.png",		//ノーマル
	"data/title/hard.png",			//ハード
	"data/title/pillar.png",		//柱1
	"data/title/pillar.png",		//柱2
	"data/title/arrow1.png",		//矢印1
	"data/title/arrow2.png",		//矢印2
};

class Title
{
private:
	int imageHandle[TITLE_IMAGE_MAX_NUM];	//画像ハンドル

	int fade[2];	//透明度：スタート 矢印

	bool lighting;	//入力待ちの点滅

	int progress;	//進行度

	float titlePosY[2];	//タイトルのY座標

	bool isReach[2];	//到達フラグ

	int FrameCount;		//フレームカウント

public:

	//初期化
	void Init();

	//通常処理
	void Step();

	//描画
	void Draw();

	//終了処理
	void Fin();

};