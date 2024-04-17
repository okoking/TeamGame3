#pragma once

// パネルの模様
enum PANEL_PATTERN {
	PANEL_PATTERN_NORMAL = 0,	// 通常
	PANEL_PATTERN_INSIDE,		// 裏

	PANEL_PATTERN_NUM,
};

// パネルの種類
enum PANEL_TYPE
{
	PANEL_TYPE_PROBLEM = 0,	// 問題
	PANEL_TYPE_ANS,			// 回答

	PANEL_TYPE_NUM,
};

// パネルの画像ファイルパス
const char NORMALPANEL_PATH[] = { "data/play/パネル表.png" };
const char INSIDEPANEL_PATH[] = { "data/play/パネル裏.png" };

// 画像サイズ
const int PANEL_SIZE = 40;

// パネルの配置
const int PANEL_X_NUM = 5;
const int PANEL_Y_NUM = 5;

struct PanelInfo
{
	int handle[PANEL_PATTERN_NUM];		//画像ハンドル
	PANEL_PATTERN Panelpattern;	// パネルの模様保存用

	int x, y;			// 座標
	bool isUse;			// 使用中フラグ
	bool isInversion;	// パネル回転中フラグ
	bool isInversioned; // 回転終了確認フラグ
};

class Panel
{
private:
	PanelInfo problempanelInfo[PANEL_Y_NUM][PANEL_X_NUM];
	PanelInfo anspanelInfo[PANEL_Y_NUM][PANEL_X_NUM];

	int InversionXpos, InversionYpos;	// 反転するパネルの座標

	bool isInside;	// 回転させるかどうか

public:
	Panel();
	~Panel();

	// パネル初期化
	void Init();

	// データロード
	void Load();

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

	// パネルのランダム要素をリセット
	void ResetPanel(int _xindex, int _yindex);

	// 回転中フラグ取得用
	bool GetisInversion(int _xindex, int _yindex) const { return anspanelInfo[_xindex][_yindex].isInversion; }

	// パネルとマウスの当たり判定
	void PaneltoMouseCollision();

	// パネル反転用
	void InversionPanel();

	// パネルの模様が一致しているか
	void PanelPatternMatch();
};
