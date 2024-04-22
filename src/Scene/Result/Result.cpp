#include"DxLib.h"
#include"../Result/Result.h"
#include"../../Scene/Scene.h"
#include"../../Input/Input.h"
#include"../Play/Play.h"

//初期化
void Result::Init()
{
	for (int i = 0; i < RESULT_IMAGE_MAX_NUM; i++)
	{
		//画像読み込み
		imageHandle[i] = LoadGraph(RESULT_IMAGE_PATH[i]);
	}

	//bgm
	Sound::Bgm::Play(BGM_RESULT);
	Sound::Bgm::SetVolume(BGM_RESULT, 40);

	//通常処理に移行
	g_CurrentSceneID = SCENE_ID_LOOP_RESULT;
}

//通常処理
void Result::Step()
{
	//左クリックで以下
	if (Input::Key::Push(KEY_INPUT_SPACE))
	{
		//se
		Sound::Se::Play(SE_SYSTEM);

		//終了処理へ
		g_CurrentSceneID = SCENE_ID_FIN_RESULT;
	}
	
}

//描画
void Result::Draw()
{
	//背景描画
	DrawGraph(0, 0, imageHandle[RESULT_BACK_GROUND], true);

	//リザルト
	DrawRotaGraph(640, 75, 1.0f, 0.0f, imageHandle[RESULT_RESULT], true);

	//スコア
	DrawRotaGraph(640, 200, 1.0f, 0.0f, imageHandle[RESULT_SCORE], true);

	//柱
	DrawGraph(0, 0, imageHandle[RESULT_PILLAR1], true);
	DrawGraph(980, 0, imageHandle[RESULT_PILLAR1], true);


	//文字の大きさを変更
	SetFontSize(60);
	
	//文字の大きさを変更
	//SetFontSize(80);
	
}

//終了処理
void Result::Fin()
{
	//bgm
	Sound::Bgm::StopSound(BGM_RESULT);

	//プレイ画面へ移行
	g_CurrentSceneID = SCENE_ID_INIT_TITLE;
}