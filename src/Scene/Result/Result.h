#pragma once

//画像の種類
enum RESULT_IMAGE
{
	RESULT_BACK_GROUND,	//背景
	RESULT_RESULT,		//リザルト
	RESULT_SCORE,		//スコア
	RESULT_PILLAR1,		//柱1
	RESULT_PILLAR2,		//柱2

	RESULT_IMAGE_MAX_NUM,	//最大数
};

//画像のパス
const char RESULT_IMAGE_PATH[RESULT_IMAGE_MAX_NUM][255] =
{
	"data/result/resultback.png",	//背景
	"data/result/text1.png",		//リザルト
	"data/result/text2.png",		//スコア
	"data/result/resultpillar.png",	//柱1
	"data/result/resultpillar.png",	//柱2
};

class Result
{
	private:
		int imageHandle[RESULT_IMAGE_MAX_NUM];	//画像ハンドル
		int fade[2];	//透明度

		int y;	//スコアの座標

		bool lighting;	//入力待ちの点滅

		int progress;	//進行度

	public:
		//初期化
		void Init();

		//通常処理
		void Step();

		//描画処理
		void Draw();

		//終了処理
		void Fin();
};