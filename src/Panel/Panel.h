#pragma once
#include "../Scene/Scene.h"

// パネルの模様
enum PANEL_PATTERN {
	PANEL_PATTERN_NORMAL = 0,	// 通常
	PANEL_PATTERN_INSIDE,		// 裏

	PANEL_PATTERN_NUM,
};

// パネルの種類
enum PANEL_TYPE
{
	PANEL_TYPE_QUESTION = 0,	// 問題
	PANEL_TYPE_ANS,				// 回答

	PANEL_TYPE_NUM,
};

// パネルの画像ファイルパス
const char NORMALPANEL_PATH[] = { "data/play/パネル表.png" };
const char INSIDEPANEL_PATH[] = { "data/play/パネル裏.png" };

// 画像サイズ
const int PANEL_SIZE = 64;

// 初期体力
const int INIT_HP = 3;

// csv関係===========================================
// パネルの配置
const int PANEL_X_MAX_NUM = 6;
const int PANEL_Y_MAX_NUM = 6;

const int PANEL_X_NUM[QUESTION_LEVEL_NUM] = 
{
	4,	// QUESTION_LEVEL_44
	5,	// QUESTION_LEVEL_55
	6,	// QUESTION_LEVEL_66
};

const int PANEL_Y_NUM[QUESTION_LEVEL_NUM] = 
{
	4,	// QUESTION_LEVEL_44
	5,	// QUESTION_LEVEL_55
	6,	// QUESTION_LEVEL_66
};

// 問題の種類
enum QUESTION_TYPE
{
	QUESTION_TYPE_1 = 0,
	QUESTION_TYPE_2,

	QUESTION_TYPE_NUM,
};

// csvのファイルパス
// 問題の方
const char QuestionCsvFilePath[QUESTION_LEVEL_NUM][QUESTION_TYPE_NUM][256] =
{
	// QUESTION_LEVEL_44
	{
		"Data/csv/question/44/Question1.csv",	// QUESTION_TYPE_1
		"Data/csv/question/44/Question2.csv",	// QUESTION_TYPE_2
	},

	// QUESTION_LEVEL_55
	{
		"Data/csv/question/55/Question1.csv",	// QUESTION_TYPE_1
		"Data/csv/question/55/Question2.csv",	// QUESTION_TYPE_2

	},

	// QUESTION_LEVEL_66
	{
		"Data/csv/question/66/Question1.csv",	// QUESTION_TYPE_1
		"Data/csv/question/66/Question2.csv",	// QUESTION_TYPE_2
	},
};
// 回答の方
const char AnsCsvFilePath[QUESTION_LEVEL_NUM][QUESTION_TYPE_NUM][256] =
{
	// QUESTION_LEVEL_44
	{
		"Data/csv/ans/44/ans1.csv",	// QUESTION_TYPE_1
		"Data/csv/ans/44/ans2.csv",	// QUESTION_TYPE_2
	},

	// QUESTION_LEVEL_55
	{
		"Data/csv/ans/55/ans1.csv",	// QUESTION_TYPE_1
		"Data/csv/ans/55/ans2.csv",	// QUESTION_TYPE_2

	},

	// QUESTION_LEVEL_66
	{
		"Data/csv/ans/66/ans1.csv",	// QUESTION_TYPE_1
		"Data/csv/ans/66/ans2.csv",	// QUESTION_TYPE_2
	},
};

// 各問題の手数
const int STEP_NUM[QUESTION_LEVEL_NUM][QUESTION_TYPE_NUM] = {
	// QUESTION_LEVEL_44
	{
		1,	// QUESTION_TYPE_1
		2,	// QUESTION_TYPE_2
	},

	// QUESTION_LEVEL_55
	{
		1,	// QUESTION_TYPE_1
		2,	// QUESTION_TYPE_2

	},

	// QUESTION_LEVEL_66
	{
		1,	// QUESTION_TYPE_1
		2,	// QUESTION_TYPE_2
	},
};

//=================================================

struct PanelInfo
{
	int handle[PANEL_PATTERN_NUM];		//画像ハンドル

	int m_FileReadLevelData;		// ファイル読み込み用

	PANEL_PATTERN Panelpattern;	// パネルの模様保存用

	int x, y;			// 座標
	bool isUse;			// 使用中フラグ
};

class Panel
{
private:
	PanelInfo questionpanelInfo[PANEL_Y_MAX_NUM][PANEL_X_MAX_NUM];
	PanelInfo anspanelInfo[PANEL_Y_MAX_NUM][PANEL_X_MAX_NUM];

	int InversionXpos, InversionYpos;	// 反転するパネルの座標

	bool isInside;	// 回転させるかどうか

	bool isInversion;	// パネル回転中フラグ
	bool isInversioned; // 回転終了確認フラグ

	// 問題決め用
	QUESTION_LEVEL questionLevel;
	QUESTION_TYPE questionType;

	// 残り手数カウント用
	int StepCnt;

	// 残りHP 
	int HP;

public:
	Panel();
	~Panel();

	// パネル初期化
	void Init();

	// データロード
	void Load();

	// ファイル読み込み
	void ReadFile();

	// パネルの通常処理
	void Step();

	// パネルの描画
	void Draw();

	// パネル終了処理
	void Fin();

	// 回答するパネル情報構造体の使用中フラグを取得
	bool IsUse(int _xindex, int _yindex) const { return anspanelInfo[_xindex][_yindex].isUse; }

	// 回答するパネル情報構造体の使用中フラグを設定
	void SetUse(int _xindex, int _yindex, bool _isUse) { anspanelInfo[_xindex][_yindex].isUse = _isUse; }

	// 回答するパネル情報構造体のX座標を取得
	int GetPosX(int _xindex, int _yindex) const { return anspanelInfo[_xindex][_yindex].x; }

	// 回答するパネル情報構造体のY座標を取得
	int GetPosY(int _xindex, int _yindex) const { return anspanelInfo[_xindex][_yindex].y; }

	// 回答するパネルの模様を取得
	PANEL_PATTERN GetPanelAngle(int _xindex, int _yindex) const { return anspanelInfo[_xindex][_yindex].Panelpattern; }

	// パネルの要素をリセット
	void ResetPanel();

	// 回転中フラグ取得用
	bool GetisInversion() const { return isInversion; }

	// パネルとマウスの当たり判定
	void PaneltoMouseCollision();

	// パネル反転用
	void InversionPanel();

	// パネルの模様が一致しているか
	void PanelPatternMatch();

	// 体力の処理
	void StepHp();

	// 次の問題に向かう処理
	void NextQuestion();
};
