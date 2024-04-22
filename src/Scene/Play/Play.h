#pragma once

#include "../../Scene/Scene.h"
#include "DxLib.h"
#include "../../Collision/Collision.h"
#include "../../MathPlus/MathPlus.h"
#include "../../Panel/Panel.h"

class Play
{
private:
	// パネルの変数宣言
	Panel panel;

	int backgroundHandle;	//背景画像ハンドル
	int enemyhandle;
	int ImgHP;
	int img_sikaku;

public:
	//プレイシーンの初期化
	void Init();

	//プレイシーンの読み込み
	void Load();

	//プレイシーンの通常処理
	void Step();

	//プレイシーンの描画処理
	void Draw();

	//プレイシーンの終了処理
	void Fin();
};
