#include "Panel.h"
#include "DxLib.h"
#include "../Collision/Collision.h"
#include "../Input/Input.h"
#include "../Scene/Scene.h"

int g_FrameCnt = 0;

// コンストラクタ
Panel::Panel()
{
	// 反転するパネルの座標
	InversionXpos = -10;
	InversionYpos = -10;

	// 回転させるかどうか
	isInside = false;

	// パネル回転中フラグ
	isInversion = false;

	// 回転終了確認フラグ
	isInversioned = false;

	// 問題決め用
	questionLevel = (QUESTION_LEVEL)-1;
	questionType = (QUESTION_TYPE)-1;

	// 手数カウント用
	StepCnt = -1;

	// 残りHP 
	HP = -1;

	for (int PanelYIndex = 0; PanelYIndex < PANEL_Y_MAX_NUM; PanelYIndex++) {
		for (int PanelXIndex = 0; PanelXIndex < PANEL_X_MAX_NUM; PanelXIndex++) {
			for (int PanelPatternindex = 0; PanelPatternindex < PANEL_PATTERN_NUM; PanelPatternindex++) {
				//画像ハンドル
				questionpanelInfo[PanelYIndex][PanelXIndex].handle[PanelPatternindex] = -1;
				anspanelInfo[PanelYIndex][PanelXIndex].handle[PanelPatternindex] = -1;
			}

			// パネルの模様保存用
			questionpanelInfo[PanelYIndex][PanelXIndex].Panelpattern = PANEL_PATTERN_NORMAL;
			anspanelInfo[PanelYIndex][PanelXIndex].Panelpattern = PANEL_PATTERN_NORMAL;

			// 座標
			questionpanelInfo[PanelYIndex][PanelXIndex].x = 0;
			anspanelInfo[PanelYIndex][PanelXIndex].x = 0;
			
			questionpanelInfo[PanelYIndex][PanelXIndex].y = 0;
			anspanelInfo[PanelYIndex][PanelXIndex].y = 0;

			// 使用中フラグ
			questionpanelInfo[PanelYIndex][PanelXIndex].isUse = false;
			anspanelInfo[PanelYIndex][PanelXIndex].isUse = false;

			// ファイル読み込み用
			questionpanelInfo[PanelYIndex][PanelXIndex].m_FileReadLevelData = -1;
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

	// 問題決め用
	questionLevel = QUESTION_LEVEL_44;
	questionType = QUESTION_TYPE_1;

	// 残り手数カウント用
	StepCnt = STEP_NUM[questionLevel][questionType];

	// 残りHP 
	HP = INIT_HP;

	// パネル回転中フラグ
	isInversion = false;

	// 回転終了確認フラグ
	isInversioned = true;

	for (int PanelYIndex = 0; PanelYIndex < PANEL_Y_MAX_NUM; PanelYIndex++) {
		for (int PanelXIndex = 0; PanelXIndex < PANEL_X_MAX_NUM; PanelXIndex++) {
			for (int PanelPatternindex = 0; PanelPatternindex < PANEL_PATTERN_NUM; PanelPatternindex++) {
				// 画像ハンドル
				questionpanelInfo[PanelYIndex][PanelXIndex].handle[PanelPatternindex] = 0;
				anspanelInfo[PanelYIndex][PanelXIndex].handle[PanelPatternindex] = 0;
			}

			// パネルの模様保存用
			questionpanelInfo[PanelYIndex][PanelXIndex].Panelpattern = PANEL_PATTERN_NORMAL;
			anspanelInfo[PanelYIndex][PanelXIndex].Panelpattern = PANEL_PATTERN_NORMAL;

			// 座標
			questionpanelInfo[PanelYIndex][PanelXIndex].x = PANEL_SIZE * PanelXIndex;
			questionpanelInfo[PanelYIndex][PanelXIndex].y = PANEL_SIZE * PanelYIndex + 300;

			anspanelInfo[PanelYIndex][PanelXIndex].x = PANEL_SIZE * PanelXIndex + 400;
			anspanelInfo[PanelYIndex][PanelXIndex].y = PANEL_SIZE * PanelYIndex + 300;

			// 使用中フラグ
			// レベルにあった範囲をtrueにする
			if (PanelYIndex < PANEL_Y_NUM[questionLevel] && PanelXIndex < PANEL_X_NUM[questionLevel]) {
				questionpanelInfo[PanelYIndex][PanelXIndex].isUse = true;
				anspanelInfo[PanelYIndex][PanelXIndex].isUse = true;
			}

			// ファイル読み込み用
			questionpanelInfo[PanelYIndex][PanelXIndex].m_FileReadLevelData = PANEL_PATTERN_NORMAL;
		}
	}
}

// データロード
void Panel::Load()
{

	// ファイル読み込み
	ReadFile();

	for (int PanelYIndex = 0; PanelYIndex < PANEL_Y_MAX_NUM; PanelYIndex++) {
		for (int PanelXIndex = 0; PanelXIndex < PANEL_X_MAX_NUM; PanelXIndex++) {
			//パネルハンドル
			questionpanelInfo[PanelYIndex][PanelXIndex].handle[PANEL_PATTERN_NORMAL] = LoadGraph(NORMALPANEL_PATH);
			anspanelInfo[PanelYIndex][PanelXIndex].handle[PANEL_PATTERN_NORMAL] = LoadGraph(NORMALPANEL_PATH);

			//反転したパネルハンドル
			questionpanelInfo[PanelYIndex][PanelXIndex].handle[PANEL_PATTERN_INSIDE] = LoadGraph(INSIDEPANEL_PATH);
			anspanelInfo[PanelYIndex][PanelXIndex].handle[PANEL_PATTERN_INSIDE] = LoadGraph(INSIDEPANEL_PATH);

			// 読み込んだデータを代入
			questionpanelInfo[PanelYIndex][PanelXIndex].Panelpattern = (PANEL_PATTERN)questionpanelInfo[PanelYIndex][PanelXIndex].m_FileReadLevelData;
			anspanelInfo[PanelYIndex][PanelXIndex].Panelpattern = (PANEL_PATTERN)anspanelInfo[PanelYIndex][PanelXIndex].m_FileReadLevelData;
		}
	}
}

// ファイル読み込み
void Panel::ReadFile()
{
	FILE* fp;

	fopen_s(&fp, QuestionCsvFilePath[questionLevel][questionType], "r");

	int mapIndexX = 0;
	int mapIndexY = 0;

	while (true) {
		// 数値部分を読み込む
		fscanf_s(fp, "%d", &questionpanelInfo[mapIndexY][mapIndexX].m_FileReadLevelData);
		mapIndexX++;

		// 「,」を飛ばすために読み込みを実行
		char chara = fgetc(fp);

		// EOFの場合は読み込み終了
		if (chara == EOF) {
			break;
		}

		// 改行コードの場合は保存先を変更する
		if (chara == '\n') {
			mapIndexY++;
			mapIndexX = 0;
		}
	}

	fopen_s(&fp, AnsCsvFilePath[questionLevel][questionType], "r");

	mapIndexX = 0;
	mapIndexY = 0;

	while (true) {
		// 数値部分を読み込む
		fscanf_s(fp, "%d", &anspanelInfo[mapIndexY][mapIndexX].m_FileReadLevelData);
		mapIndexX++;

		// 「,」を飛ばすために読み込みを実行
		char chara = fgetc(fp);

		// EOFの場合は読み込み終了
		if (chara == EOF) {
			break;
		}

		// 改行コードの場合は保存先を変更する
		if (chara == '\n') {
			mapIndexY++;
			mapIndexX = 0;
		}
	}

	fclose(fp);
}

// パネルの通常処理
void Panel::Step()
{
	// パネルとマウスの当たり判定
	PaneltoMouseCollision();

	// パネル反転用
	InversionPanel();

	// パネルの模様が一致しているか
	PanelPatternMatch();

	// 体力の処理
	StepHp();
}

// パネルの描画
void Panel::Draw()
{
	for (int PanelYIndex = 0; PanelYIndex < PANEL_Y_MAX_NUM; PanelYIndex++) {
		for (int PanelXIndex = 0; PanelXIndex < PANEL_X_MAX_NUM; PanelXIndex++) {
			// 問題
			if (questionpanelInfo[PanelYIndex][PanelXIndex].isUse) {
				DrawGraph(questionpanelInfo[PanelYIndex][PanelXIndex].x, questionpanelInfo[PanelYIndex][PanelXIndex].y,
					questionpanelInfo[PanelYIndex][PanelXIndex].handle[questionpanelInfo[PanelYIndex][PanelXIndex].Panelpattern], true);
			}

			// 回答
			if (anspanelInfo[PanelYIndex][PanelXIndex].isUse) {
				DrawGraph(anspanelInfo[PanelYIndex][PanelXIndex].x, anspanelInfo[PanelYIndex][PanelXIndex].y,
					anspanelInfo[PanelYIndex][PanelXIndex].handle[anspanelInfo[PanelYIndex][PanelXIndex].Panelpattern], true);
			}

			// 残りHPと手数の表示
			//文字の大きさを変更
			SetFontSize(32);

			DrawFormatString(0, 0, GetColor(255, 255, 255), "残りHP：%d", HP, true);
			DrawFormatString(0, 32, GetColor(255, 255, 255), "残り手数：%d", StepCnt, true);
			DrawFormatString(0, 64, GetColor(255, 255, 255), "g_FrameCnt：%d", g_FrameCnt, true);
		}
	}
}

// パネル終了処理
void Panel::Fin()
{
	for (int PanelYIndex = 0; PanelYIndex < PANEL_Y_MAX_NUM; PanelYIndex++) {
		for (int PanelXIndex = 0; PanelXIndex < PANEL_X_MAX_NUM; PanelXIndex++) {
			//パネルハンドル
			DeleteGraph(questionpanelInfo[PanelYIndex][PanelXIndex].handle[PANEL_PATTERN_NORMAL]);
			DeleteGraph(questionpanelInfo[PanelYIndex][PanelXIndex].handle[PANEL_PATTERN_NORMAL]);

			//反転したパネルハンドル
			DeleteGraph(anspanelInfo[PanelYIndex][PanelXIndex].handle[PANEL_PATTERN_INSIDE]);
			DeleteGraph(anspanelInfo[PanelYIndex][PanelXIndex].handle[PANEL_PATTERN_INSIDE]);
		}
	}
}

// パネルの要素をリセット
void Panel::ResetPanel()
{
	// 残り手数カウント初期化
	StepCnt = STEP_NUM[questionLevel][questionType];

	for (int PanelYIndex = 0; PanelYIndex < PANEL_Y_MAX_NUM; PanelYIndex++) {
		for (int PanelXIndex = 0; PanelXIndex < PANEL_X_MAX_NUM; PanelXIndex++) {
			// 読み込んだデータを代入
			anspanelInfo[PanelYIndex][PanelXIndex].Panelpattern = (PANEL_PATTERN)anspanelInfo[PanelYIndex][PanelXIndex].m_FileReadLevelData;
		}
	}
}

// パネルとマウスの当たり判定
void Panel::PaneltoMouseCollision()
{
	// 回転しているならとらない
	if (g_FrameCnt == 0) {
		int MousePosX, MousePosY;

		GetMousePoint(&MousePosX, &MousePosY);

		for (int PanelYIndex = 0; PanelYIndex < PANEL_Y_MAX_NUM; PanelYIndex++) {
			for (int PanelXIndex = 0; PanelXIndex < PANEL_X_MAX_NUM; PanelXIndex++) {
				if (anspanelInfo[PanelYIndex][PanelXIndex].isUse) {
					if (Collision::Rect(anspanelInfo[PanelYIndex][PanelXIndex].x, anspanelInfo[PanelYIndex][PanelXIndex].y, PANEL_SIZE, PANEL_SIZE,
						MousePosX, MousePosY, 1, 1)) {
						// マウスカーソルがパネルに当たっているなら囲う
						// 仮でここに直接書いてる
						DrawLineBox(anspanelInfo[PanelYIndex][PanelXIndex].x, anspanelInfo[PanelYIndex][PanelXIndex].y,
							anspanelInfo[PanelYIndex][PanelXIndex].x + PANEL_SIZE, anspanelInfo[PanelYIndex][PanelXIndex].y + PANEL_SIZE, GetColor(255, 255, 255));

						if (Input::Mouse::Push(MOUSE_INPUT_LEFT)) {
							// 反転を左上から始める
							InversionXpos = PanelXIndex - 1;
							InversionYpos = PanelYIndex - 1;

							// 反転を始める
							isInside = true;

							// 残り手数カウントデクリメント
							StepCnt--;
						}
					}
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
			for (int PanelXIndex = InversionXpos; PanelXIndex < InversionXpos + 3; PanelXIndex++) {
				// 反転する場所がパネルの範囲外なら飛ばす
				if (PanelYIndex < 0 || PanelYIndex >= PANEL_Y_MAX_NUM || PanelXIndex < 0 || PanelXIndex >= PANEL_X_MAX_NUM) {
					continue;
				}

				if (anspanelInfo[PanelYIndex][PanelXIndex].isUse) {
					if (anspanelInfo[PanelYIndex][PanelXIndex].Panelpattern == PANEL_PATTERN_NORMAL) {
						anspanelInfo[PanelYIndex][PanelXIndex].Panelpattern = PANEL_PATTERN_INSIDE;
					}
					else {
						anspanelInfo[PanelYIndex][PanelXIndex].Panelpattern = PANEL_PATTERN_NORMAL;
					}
					// 反転を終わらせる
					isInside = false;
				}
			}
		}
	}
}

// パネルの模様が一致しているか
void Panel::PanelPatternMatch()
{
	int Cnt = 0;

	for (int PanelYIndex = 0; PanelYIndex < PANEL_Y_MAX_NUM; PanelYIndex++) {
		for (int PanelXIndex = 0; PanelXIndex < PANEL_X_MAX_NUM; PanelXIndex++) {
			if (anspanelInfo[PanelYIndex][PanelXIndex].isUse) {
				if (anspanelInfo[PanelYIndex][PanelXIndex].Panelpattern != questionpanelInfo[PanelYIndex][PanelXIndex].Panelpattern) {
					continue;
				}
				
				Cnt++;
				// すべて一致するなら次の問題へ
				if (Cnt == PANEL_Y_NUM[questionLevel]* PANEL_X_NUM[questionLevel]) {
					// 次の問題に向かう処理
					NextQuestion();
				}
			}
		}
	}
}

// 体力の処理
void Panel::StepHp()
{
	if (StepCnt < 0) {
		StepCnt = 0;
	}

	// 残り手数が0なら実行
	if (StepCnt == 0) {
		// 3秒経つまで処理を遅らせる
		if (g_FrameCnt == 180) {
			g_FrameCnt = 0;
			HP--;

			if (HP == 0) {
				// 体力がなくなったならリザルトへ
				g_CurrentSceneID = SCENE_ID_INIT_RESULT;
			}

			// パネルの要素をリセット
			ResetPanel();
		}
		else {
			// 加算
			g_FrameCnt++;
		}

		if (g_FrameCnt > 180) {
			g_FrameCnt = 180;
		}
	}
}

// 次の問題に向かう処理
void Panel::NextQuestion()
{
	// プレイ初期化シーンへ
	g_CurrentSceneID = SCENE_ID_INIT_PLAY;

}
