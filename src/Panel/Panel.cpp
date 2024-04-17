#include "Panel.h"
#include "DxLib.h"
#include "../Collision/Collision.h"
#include "../Input/Input.h"

// コンストラクタ
Panel::Panel()
{
	// 反転するパネルの座標
	InversionXpos = -10;
	InversionYpos = -10;

	// 回転させるかどうか
	isInside = false;

	for (int PanelYIndex = 0; PanelYIndex < PANEL_X_NUM; PanelYIndex++) {
		for (int PanelXIndex = 0; PanelXIndex < PANEL_Y_NUM; PanelXIndex++) {
			for (int PanelPatternindex = 0; PanelPatternindex < PANEL_PATTERN_NUM; PanelPatternindex++) {
				//画像ハンドル
				problempanelInfo[PanelYIndex][PanelXIndex].handle[PanelPatternindex] = -1;
				anspanelInfo[PanelYIndex][PanelXIndex].handle[PanelPatternindex] = -1;
			}

			// パネルの模様保存用
			problempanelInfo[PanelYIndex][PanelXIndex].Panelpattern = PANEL_PATTERN_NORMAL;
			anspanelInfo[PanelYIndex][PanelXIndex].Panelpattern = PANEL_PATTERN_NORMAL;

			// 座標
			problempanelInfo[PanelYIndex][PanelXIndex].x = 0;
			anspanelInfo[PanelYIndex][PanelXIndex].x = 0;
			
			problempanelInfo[PanelYIndex][PanelXIndex].y = 0;
			anspanelInfo[PanelYIndex][PanelXIndex].y = 0;

			// 使用中フラグ
			problempanelInfo[PanelYIndex][PanelXIndex].isUse = false;
			anspanelInfo[PanelYIndex][PanelXIndex].isUse = false;

			// パネル回転中フラグ
			problempanelInfo[PanelYIndex][PanelXIndex].isInversion = false;
			anspanelInfo[PanelYIndex][PanelXIndex].isInversion = false;

			// 回転終了確認フラグ
			problempanelInfo[PanelYIndex][PanelXIndex].isInversioned = false;
			anspanelInfo[PanelYIndex][PanelXIndex].isInversioned = false;
		}
	}
}

// デストラクタ
Panel::~Panel()
{
}

// パネル初期化
void Panel::Init()
{
	// 反転するパネルの座標
	InversionXpos = -10;
	InversionYpos = -10;
	
	// 回転させるかどうか
	isInside = false;

	for (int PanelYIndex = 0; PanelYIndex < PANEL_X_NUM; PanelYIndex++) {
		for (int PanelXIndex = 0; PanelXIndex < PANEL_Y_NUM; PanelXIndex++) {
			for (int PanelPatternindex = 0; PanelPatternindex < PANEL_PATTERN_NUM; PanelPatternindex++) {
				// 画像ハンドル
				problempanelInfo[PanelYIndex][PanelXIndex].handle[PanelPatternindex] = 0;
				anspanelInfo[PanelYIndex][PanelXIndex].handle[PanelPatternindex] = 0;
			}

			// パネルの模様保存用
			problempanelInfo[PanelYIndex][PanelXIndex].Panelpattern = PANEL_PATTERN_NORMAL;
			anspanelInfo[PanelYIndex][PanelXIndex].Panelpattern = PANEL_PATTERN_NORMAL;

			// 座標
			problempanelInfo[PanelYIndex][PanelXIndex].x = PANEL_SIZE * PanelXIndex;
			problempanelInfo[PanelYIndex][PanelXIndex].y = PANEL_SIZE * PanelYIndex + 300;

			anspanelInfo[PanelYIndex][PanelXIndex].x = PANEL_SIZE * PanelXIndex + 400;
			anspanelInfo[PanelYIndex][PanelXIndex].y = PANEL_SIZE * PanelYIndex + 300;

			// 使用中フラグ
			problempanelInfo[PanelYIndex][PanelXIndex].isUse = true;
			anspanelInfo[PanelYIndex][PanelXIndex].isUse = true;

			// パネル回転中フラグ
			problempanelInfo[PanelYIndex][PanelXIndex].isInversion = false;
			anspanelInfo[PanelYIndex][PanelXIndex].isInversion = false;

			// 回転終了確認フラグ
			problempanelInfo[PanelYIndex][PanelXIndex].isInversioned = true;
			anspanelInfo[PanelYIndex][PanelXIndex].isInversioned = true;
		}
	}
}

// データロード
void Panel::Load()
{
	for (int PanelYIndex = 0; PanelYIndex < PANEL_X_NUM; PanelYIndex++) {
		for (int PanelXIndex = 0; PanelXIndex < PANEL_Y_NUM; PanelXIndex++) {
			//パネルハンドル
			problempanelInfo[PanelYIndex][PanelXIndex].handle[PANEL_PATTERN_NORMAL] = LoadGraph(NORMALPANEL_PATH);
			anspanelInfo[PanelYIndex][PanelXIndex].handle[PANEL_PATTERN_NORMAL] = LoadGraph(NORMALPANEL_PATH);

			//反転したパネルハンドル
			problempanelInfo[PanelYIndex][PanelXIndex].handle[PANEL_PATTERN_INSIDE] = LoadGraph(INSIDEPANEL_PATH);
			anspanelInfo[PanelYIndex][PanelXIndex].handle[PANEL_PATTERN_INSIDE] = LoadGraph(INSIDEPANEL_PATH);
		}
	}
}

// パネルの通常処理
void Panel::Step()
{
	// パネルとマウスの当たり判定
	PaneltoMouseCollision();

	// パネル反転用
	InversionPanel();
}

// パネルの描画
void Panel::Draw()
{
	for (int PanelYIndex = 0; PanelYIndex < PANEL_X_NUM; PanelYIndex++) {
		for (int PanelXIndex = 0; PanelXIndex < PANEL_Y_NUM; PanelXIndex++) {
			if (problempanelInfo[PanelYIndex][PanelXIndex].isUse) {
				DrawGraph(problempanelInfo[PanelYIndex][PanelXIndex].x, problempanelInfo[PanelYIndex][PanelXIndex].y,
					problempanelInfo[PanelYIndex][PanelXIndex].handle[problempanelInfo[PanelYIndex][PanelXIndex].Panelpattern], true);
			}

			if (anspanelInfo[PanelYIndex][PanelXIndex].isUse) {
				DrawGraph(anspanelInfo[PanelYIndex][PanelXIndex].x, anspanelInfo[PanelYIndex][PanelXIndex].y,
					anspanelInfo[PanelYIndex][PanelXIndex].handle[anspanelInfo[PanelYIndex][PanelXIndex].Panelpattern], true);
			}

		}
	}
}

// パネル終了処理
void Panel::Fin()
{
	for (int PanelYIndex = 0; PanelYIndex < PANEL_X_NUM; PanelYIndex++) {
		for (int PanelXIndex = 0; PanelXIndex < PANEL_Y_NUM; PanelXIndex++) {
			//パネルハンドル
			DeleteGraph(problempanelInfo[PanelYIndex][PanelXIndex].handle[PANEL_PATTERN_NORMAL]);
			DeleteGraph(problempanelInfo[PanelYIndex][PanelXIndex].handle[PANEL_PATTERN_NORMAL]);

			//反転したパネルハンドル
			DeleteGraph(anspanelInfo[PanelYIndex][PanelXIndex].handle[PANEL_PATTERN_INSIDE]);
			DeleteGraph(anspanelInfo[PanelYIndex][PanelXIndex].handle[PANEL_PATTERN_INSIDE]);
		}
	}
}

// パネルのランダム要素をリセット
void Panel::ResetPanel(int _xindex, int _yindex)
{
}

// パネルとマウスの当たり判定
void Panel::PaneltoMouseCollision()
{
	int MousePosX, MousePosY;

	GetMousePoint(&MousePosX, &MousePosY);

	if (Input::Mouse::Push(MOUSE_INPUT_LEFT)) {
		for (int PanelYIndex = 0; PanelYIndex < PANEL_X_NUM; PanelYIndex++) {
			for (int PanelXIndex = 0; PanelXIndex < PANEL_Y_NUM; PanelXIndex++) {
				if (Collision::Rect(anspanelInfo[PanelYIndex][PanelXIndex].x, anspanelInfo[PanelYIndex][PanelXIndex].y, PANEL_SIZE, PANEL_SIZE,
					MousePosX, MousePosY, 1, 1)) {
					// 反転を左上から始める
					InversionXpos = PanelXIndex - 1;
					InversionYpos = PanelYIndex - 1;

					// 反転を始める
					isInside = true;
				}
			}
		}
	}

}

// パネル反転用
void Panel::InversionPanel()
{
	if (isInside) {	// 反転開始
		for (int PanelYIndex = InversionYpos; PanelYIndex < InversionYpos + 3; PanelYIndex++) {
			if (PanelYIndex < 0) {
				continue;
			}
			if (PanelYIndex >= PANEL_Y_NUM) {
				break;
			}
			for (int PanelXIndex = InversionXpos; PanelXIndex < InversionXpos + 3; PanelXIndex++) {
				if (PanelXIndex < 0) {
					continue;
				}
				if (PanelXIndex >= PANEL_X_NUM) {
					PanelXIndex = InversionXpos;
					break;
				}

				if (anspanelInfo[PanelYIndex][PanelXIndex].Panelpattern == PANEL_PATTERN_NORMAL) {
					anspanelInfo[PanelYIndex][PanelXIndex].Panelpattern = PANEL_PATTERN_INSIDE;
				}
				else {
					anspanelInfo[PanelYIndex][PanelXIndex].Panelpattern = PANEL_PATTERN_NORMAL;
				}
			}
		}
	}

	// 反転を終わらせる
	isInside = false;
}
