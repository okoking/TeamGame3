#include"DxLib.h"
#include"../Title/Title.h"
#include"../../Scene/Scene.h"
#include"../../Input/Input.h"
#include"../../FrameRate/FrameRate.h"

SCENE_ID g_CurrentSceneID;	//シーン変数

//ゲームモード
QUESTION_LEVEL g_QuestonLevelID;

//初期化
void Title::Init()
{
	//画像読み込み
	for (int i = 0; i < TITLE_IMAGE_MAX_NUM; i++)
	{
		imageHandle[i] = LoadGraph(TITLE_IMAGE_PATH[i]);
	}

	//bgm
	Sound::Bgm::Play(BGM_TITLE);
	Sound::Bgm::SetVolume(BGM_TITLE,50);

	//透過点滅
	fade[0] = 0;
	fade[1] = 0;

	//タイトルの初期Y座標を設定
	for (int i = 0; i < 2; i++)
	{
		titlePosY[i] = -150.0f;
		//到達フラグを折る
		isReach[i] = false;
	}

	FrameCount = 0;

	//通常処理に移行
	g_CurrentSceneID = SCENE_ID_LOOP_TITLE;

	//ゲームモードを初期化
	g_QuestonLevelID = QUESTION_LEVEL_44;
}

//通常処理
void Title::Step()
{
	//到達フラグがfalseなら
	if (!isReach[0])
	{
		titlePosY[0]++;

		if (titlePosY[0] >= 75.0f)
		{
			titlePosY[0] = 75.0f;
			isReach[0] = true;
		}
	}

	else if (isReach[0] && !isReach[1])
	{
		titlePosY[1] += 2.0f;

		if (titlePosY[1] >= 200.0f)
		{
			titlePosY[1] = 200.0f;

			FrameCount++;
			{
				if (FrameCount >= FRAME_RATE)
				{
					FrameCount = 0;
					isReach[1] = true;
				}
			}
		}
	}

	if (isReach[1])
	{
		//現れる
		if (lighting)
		{
			fade[0] += 4;
			fade[1] += 7;

			if (fade[0] >= 255)
			{
				lighting = false;
			}
			if (fade[1] >= 255)
			{
				lighting = false;
			}
		}
		//消える
		else
		{
			fade[0] -= 4;
			fade[1] -= 7;

			if (fade[0] <= 0)
			{
				lighting = true;
			}
			if (fade[1] <= 0)
			{
				lighting = true;
			}
		}
		//エンターキーで画面変化
		if (Input::Key::Push(KEY_INPUT_RETURN))
		{
			// 仮として終了処理へ==================
			g_CurrentSceneID = SCENE_ID_FIN_TITLE;
			//=====================================
			
			//se
			Sound::Se::Play(SE_SYSTEM);

			//終了処理へ
			g_CurrentSceneID = SCENE_ID_FIN_TITLE;
		}

		//矢印キーで状態変化
		if (g_QuestonLevelID != QUESTION_LEVEL_44) {
			if (Input::Key::Push(KEY_INPUT_LEFT))
			{
				//se
				Sound::Se::Play(SE_SYSTEM);
				if (g_QuestonLevelID == QUESTION_LEVEL_66)
					g_QuestonLevelID = QUESTION_LEVEL_55;
				else
					g_QuestonLevelID = QUESTION_LEVEL_44;
			}
		}
		if (g_QuestonLevelID != QUESTION_LEVEL_66) {
			if (Input::Key::Push(KEY_INPUT_RIGHT))
			{
				//se
				Sound::Se::Play(SE_SYSTEM);
				if (g_QuestonLevelID == QUESTION_LEVEL_44)
					g_QuestonLevelID = QUESTION_LEVEL_55;
				else
					g_QuestonLevelID = QUESTION_LEVEL_66;
			}
		}
	}
}


void Title::Draw()//1280 720
{
	//背景
	DrawGraph(0, 0, imageHandle[TITLE_BACK], true);

	//タイトル
	DrawRotaGraph(640, (int)titlePosY[0], 0.75f, 0.0f, imageHandle[TITLE_TITLE1], true);
	DrawRotaGraph(640, (int)titlePosY[1], 0.75f, 0.0f, imageHandle[TITLE_TITLE2], true);

	if (isReach[1])
	{
		//難易度
		DrawRotaGraph(640, 360, 0.75f, 0.0f, imageHandle[TITLE_EASY + g_QuestonLevelID], true);
	}

	//柱
	DrawGraph(0, 0, imageHandle[TITLE_PILLAR1], true);
	DrawGraph(980, 0, imageHandle[TITLE_PILLAR2], true);

	if (isReach[1])
	{
		//矢印
		if (g_QuestonLevelID != QUESTION_LEVEL_55) {
			//fadeで透明度変更
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, fade[1]);
			DrawRotaGraph(500, 360, 0.75f, 0.0f, imageHandle[TITLE_ARROW2], true);
			DrawRotaGraph(778, 360, 0.75f, 0.0f, imageHandle[TITLE_ARROW1], true);
			//表示を元に戻す
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		}
		else {
			//fadeで透明度変更
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, fade[1]);
			DrawRotaGraph(500, 360, 0.75f, 0.0f, imageHandle[TITLE_ARROW2], true);
			DrawRotaGraph(778, 360, 0.75f, 0.0f, imageHandle[TITLE_ARROW1], true);
			//表示を元に戻す
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		}

		//fadeで透明度変更
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, fade[0]);
		DrawRotaGraph(640, 600, 0.75f, 0.0f, imageHandle[TITLE_START], true);	//入力待ち
		//表示を元に戻す
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	}
}

//終了処理
void Title::Fin()
{
	//bgm
	Sound::Bgm::StopSound(BGM_TITLE);
	
	//プレイ画面へ移行
	g_CurrentSceneID = SCENE_ID_INIT_PLAY;
}