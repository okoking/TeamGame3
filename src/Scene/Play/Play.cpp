#include "Play.h"
#include "../../FrameRate/FrameRate.h"

//画像パス
const char BACKGROUND_PATH[] = { "data/play/backGround.png" };		//プレイシーンの背景画像のパス
const char ENEMY_PATH[] = { "data/play/move1.png" };				//プレイシーンの背景画像のパス

//プレイシーンの初期化
void Play::Init()
{
	// パネル
	panel.Init();

	//音
	Sound::Bgm::Play(BGM_PLAY);
	Sound::Bgm::SetVolume(BGM_PLAY, 50);

	//プレイシーンの通常処理に遷移
	g_CurrentSceneID = SCENE_ID_LOOP_PLAY;
}

//プレイシーンの読み込み
void Play::Load()
{
	//画像読み込み
	// パネル
	panel.Load();

	//背景関連
	backgroundHandle = LoadGraph(BACKGROUND_PATH);	//背景
	enemyhandle = LoadGraph(ENEMY_PATH);	//敵
	ImgHP = LoadGraph("data/play/HP.png");
	img_sikaku = LoadGraph("data/play/sikaku.png");
}

//プレイシーンの通常処理
void Play::Step()
{
	panel.Step();			// パネルの通常処理
}

//プレイシーンの描画処理
void Play::Draw()
{
	//敵500, 0
	DrawGraph(500, 0,enemyhandle, true);
	//DrawRotaGraph(400, 300,1.0f,0.0f, enemyhandle, true);

	panel.Draw();			// パネルの通常処理

	//文字の大きさを変更
	SetFontSize(20);
	////操作説明を書く
	//DrawFormatString(20, 100, GetColor(255, 255, 255), "来る方向に盾を向けろ");
	//DrawFormatString(20, 120, GetColor(255, 255, 255), "赤い矢は防ぐな");
	//DrawFormatString(20, 140, GetColor(255, 255, 255), "後は雰囲気でなんとかしろ");
	//DrawFormatString(500, 40, GetColor(255, 255, 255), "ガード成功数:%d",player.GetGuradCnt());
	
	DrawRotaGraph(400, 300, 1.0f, 0.0f, img_sikaku, true);
	
	//文字の大きさを元に戻す
	SetFontSize(20);
}

//プレイヤーシーンの終了処理
void Play::Fin()
{
	panel.Fin();		// パネル終了処理

	Sound::Se::Play(SE_CLEAR);

	DeleteGraph(enemyhandle);	// 敵画像処理
	//gem
	Sound::Bgm::StopSound(BGM_PLAY);
}

