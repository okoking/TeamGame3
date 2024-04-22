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
	isAllHit = false;

	// 問題決め用
	questionLevel = (QUESTION_LEVEL)-1;
	questionType = (QUESTION_TYPE)-1;

	// 手数カウント用
	StepCnt = -1;

	// 残りHP 
	HP = -1;

	// フレームカウント用
	FrameCnt = -1;
	EffectFrameCnt = -1;
	paneldisframeCnt = -1;

	for (int PanelYIndex = 0; PanelYIndex < PANEL_Y_MAX_NUM; PanelYIndex++) {
		for (int PanelXIndex = 0; PanelXIndex < PANEL_X_MAX_NUM; PanelXIndex++) {
			for (int PanelPatternindex = 0; PanelPatternindex < PANEL_PATTERN_NUM; PanelPatternindex++) {
				//画像ハンドル
				questionpanelInfo[PanelYIndex][PanelXIndex].handle[PanelPatternindex] = -1;
				anspanelInfo[PanelYIndex][PanelXIndex].handle[PanelPatternindex] = -1;
			}


			// パネル回転中フラグ
			anspanelInfo[PanelYIndex][PanelXIndex].isInversion = false;

			// 回転終了確認フラグ
			anspanelInfo[PanelYIndex][PanelXIndex].isInversioned = false;

			// 間違っているフラグ
			anspanelInfo[PanelYIndex][PanelXIndex].isMissTake = false;

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

			anspanelInfo[PanelYIndex][PanelXIndex].MissTakeCnt = -1;

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
	// フレームカウント用
	FrameCnt = 1;
	EffectFrameCnt = 0;
	paneldisframeCnt = MISSTAKE_MAX_FRAME + 25;

	hearthandle = -1;

	// エフェクト
	effect.Init();

	// 反転するパネルの座標
	InversionXpos = -10;
	InversionYpos = -10;
	
	// 回転させるかどうか
	isInside = false;
	isAllHit = false;

	// 問題決め用
	//questionLevel = g_QuestonLevelID;
	//questionType = g_QuestonTypeID;

	// 残り手数カウント用
	StepCnt = STEP_NUM[g_QuestonLevelID][g_QuestonTypeID];

	// 残りHP 
	HP = INIT_HP;

	for (int PanelYIndex = 0; PanelYIndex < PANEL_Y_MAX_NUM; PanelYIndex++) {
		for (int PanelXIndex = 0; PanelXIndex < PANEL_X_MAX_NUM; PanelXIndex++) {
			for (int PanelPatternindex = 0; PanelPatternindex < PANEL_PATTERN_NUM; PanelPatternindex++) {
				// 画像ハンドル
				questionpanelInfo[PanelYIndex][PanelXIndex].handle[PanelPatternindex] = 0;
				anspanelInfo[PanelYIndex][PanelXIndex].handle[PanelPatternindex] = 0;
			}
			// パネル回転中フラグ
			anspanelInfo[PanelYIndex][PanelXIndex].isInversion = false;

			// 回転終了確認フラグ
			anspanelInfo[PanelYIndex][PanelXIndex].isInversioned = true;

			anspanelInfo[PanelYIndex][PanelXIndex].isMissTake = false;	// 間違っているフラグ

			// パネルの模様保存用
			questionpanelInfo[PanelYIndex][PanelXIndex].Panelpattern = PANEL_PATTERN_NORMAL;
			anspanelInfo[PanelYIndex][PanelXIndex].Panelpattern = PANEL_PATTERN_NORMAL;

			// 座標
			questionpanelInfo[PanelYIndex][PanelXIndex].x = PANEL_SIZE * PanelXIndex;
			questionpanelInfo[PanelYIndex][PanelXIndex].y = PANEL_SIZE * PanelYIndex + 300;

			anspanelInfo[PanelYIndex][PanelXIndex].x = PANEL_SIZE * PanelXIndex + 500;
			anspanelInfo[PanelYIndex][PanelXIndex].y = PANEL_SIZE * PanelYIndex + 300;
			
			anspanelInfo[PanelYIndex][PanelXIndex].MissTakeCnt = MISSTAKE_MAX_FRAME;

			// 使用中フラグ
			// レベルにあった範囲をtrueにする
			if (PanelYIndex < PANEL_Y_NUM[g_QuestonLevelID] && PanelXIndex < PANEL_X_NUM[g_QuestonLevelID]) {
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
	// エフェクト
	effect.Load(EFFECT_TYPE_NORMAL, 9);
	effect.Load(EFFECT_TYPE_INSIDE, 9);

	hearthandle = LoadGraph(HEART_PATH);

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

	fopen_s(&fp, QuestionCsvFilePath[g_QuestonLevelID][g_QuestonTypeID], "r");

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

	fopen_s(&fp, AnsCsvFilePath[g_QuestonLevelID][g_QuestonTypeID], "r");

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
	// エフェクト
	effect.Step();

	// パネルとマウスの当たり判定
	PaneltoMouseCollision();

	// パネル反転用
	InversionPanel();

	// パネルの模様が一致しているか
	PanelPatternMatch();

	// 体力の処理
	StepHp();

	// 間違っているとき処理
	MissTake();

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
				if (!anspanelInfo[PanelYIndex][PanelXIndex].isInversion) {
					if (anspanelInfo[PanelYIndex][PanelXIndex].MissTakeCnt % 12 < 6) {
						DrawGraph(anspanelInfo[PanelYIndex][PanelXIndex].x, anspanelInfo[PanelYIndex][PanelXIndex].y,
							anspanelInfo[PanelYIndex][PanelXIndex].handle[anspanelInfo[PanelYIndex][PanelXIndex].Panelpattern], true);
					}
				}
			}
		}
	}

	for (int i = 0; i < HP; i++) {
		DrawGraph(32 * i, 0, hearthandle, true);
	}


	DrawFormatString(0, 64, GetColor(255, 255, 255), "残り手数：%d", StepCnt, true);


	// エフェクト
	effect.Draw();

}

// パネル終了処理
void Panel::Fin()
{
	// エフェクト
	effect.Fin();

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
	DeleteGraph(hearthandle);

	g_CurrentSceneID = SCENE_ID_INIT_RESULT;

	if (isAllHit) {
		// 次の問題に向かう処理
		NextQuestion();
	}

}

// パネルの要素をリセット
void Panel::ResetPanel()
{
	// 残り手数カウント初期化
	StepCnt = STEP_NUM[g_QuestonLevelID][g_QuestonTypeID];

	Sound::Se::Play(SE_MISS);

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
	if (EffectFrameCnt == 0) {
		int MousePosX, MousePosY;

		GetMousePoint(&MousePosX, &MousePosY);

		for (int PanelYIndex = 0; PanelYIndex < PANEL_Y_MAX_NUM; PanelYIndex++) {
			for (int PanelXIndex = 0; PanelXIndex < PANEL_X_MAX_NUM; PanelXIndex++) {
				if (anspanelInfo[PanelYIndex][PanelXIndex].isUse) {
					if (Collision::Rect(anspanelInfo[PanelYIndex][PanelXIndex].x, anspanelInfo[PanelYIndex][PanelXIndex].y, PANEL_SIZE, PANEL_SIZE,
						MousePosX, MousePosY, 1, 1)) {
						if (Input::Mouse::Push(MOUSE_INPUT_LEFT)) {
							// 反転を左上から始める
							InversionXpos = PanelXIndex - 1;
							InversionYpos = PanelYIndex - 1;

							// 反転を始める
							isInside = true;

							// 反転を確認する
							anspanelInfo[PanelYIndex][PanelXIndex].isInversion = true;

							paneldisframeCnt = 0;

							//se
							Sound::Se::Play(SE_CLICK_PANEL);

							// 残り手数カウントデクリメント
							StepCnt--;
						}
					}
				}
			}
		}	
	}
	paneldisframeCnt++;
}

// パネル反転用
void Panel::InversionPanel()
{
	if (isInside) {	// 反転開始
		if (EffectFrameCnt == 0) {	// 一周だけ
			for (int PanelYIndex = InversionYpos; PanelYIndex < InversionYpos + 3; PanelYIndex++) {
				for (int PanelXIndex = InversionXpos; PanelXIndex < InversionXpos + 3; PanelXIndex++) {
					// 反転する場所がパネルの範囲外なら飛ばす
					if (PanelYIndex < 0 || PanelYIndex >= PANEL_Y_MAX_NUM || PanelXIndex < 0 || PanelXIndex >= PANEL_X_MAX_NUM) {
						continue;
					}

					if (anspanelInfo[PanelYIndex][PanelXIndex].isUse) {
						if (anspanelInfo[PanelYIndex][PanelXIndex].Panelpattern == PANEL_PATTERN_NORMAL) {
							effect.Play(EFFECT_TYPE_NORMAL,
								anspanelInfo[PanelYIndex][PanelXIndex].x + PANEL_SIZE / 2, anspanelInfo[PanelYIndex][PanelXIndex].y + PANEL_SIZE / 2);
							// パネル回転中フラグ
							anspanelInfo[PanelYIndex][PanelXIndex].isInversion = true;

							anspanelInfo[PanelYIndex][PanelXIndex].Panelpattern = PANEL_PATTERN_INSIDE;
						}
						else {
							effect.Play(EFFECT_TYPE_INSIDE,
								anspanelInfo[PanelYIndex][PanelXIndex].x + PANEL_SIZE / 2, anspanelInfo[PanelYIndex][PanelXIndex].y + PANEL_SIZE / 2);
							// パネル回転中フラグ
							anspanelInfo[PanelYIndex][PanelXIndex].isInversion = true;

							anspanelInfo[PanelYIndex][PanelXIndex].Panelpattern = PANEL_PATTERN_NORMAL;
						}
					}
				}
			}
		}

		EffectFrameCnt++;

		if (EffectFrameCnt > 25) {
			// 反転を終わらせる
			isInside = false;
			EffectFrameCnt = 0;
			for (int PanelYIndex = InversionYpos; PanelYIndex < InversionYpos + 3; PanelYIndex++) {
				for (int PanelXIndex = InversionXpos; PanelXIndex < InversionXpos + 3; PanelXIndex++) {
					if (anspanelInfo[PanelYIndex][PanelXIndex].isInversion) {
						anspanelInfo[PanelYIndex][PanelXIndex].isInversion = false;
					}
					// 間違っている部分を出す
					if (anspanelInfo[PanelYIndex][PanelXIndex].Panelpattern != questionpanelInfo[PanelYIndex][PanelXIndex].Panelpattern) {
						anspanelInfo[PanelYIndex][PanelXIndex].isMissTake = true;
						anspanelInfo[PanelYIndex][PanelXIndex].MissTakeCnt = 0;
					}
				}
			}
		}
	}
}

// パネルの模様が一致しているか
void Panel::PanelPatternMatch()
{
	int Cnt = 0;
	isAllHit = false;

	for (int PanelYIndex = 0; PanelYIndex < PANEL_Y_MAX_NUM; PanelYIndex++) {
		for (int PanelXIndex = 0; PanelXIndex < PANEL_X_MAX_NUM; PanelXIndex++) {
			if (anspanelInfo[PanelYIndex][PanelXIndex].isUse) {
				if (anspanelInfo[PanelYIndex][PanelXIndex].Panelpattern != questionpanelInfo[PanelYIndex][PanelXIndex].Panelpattern) {
					continue;
				}
				
				Cnt++;
				// すべて一致するなら次の問題へ
				if (Cnt == PANEL_Y_NUM[g_QuestonLevelID] * PANEL_X_NUM[g_QuestonLevelID]) {
					isAllHit = true;
				}
			}
		}
	}
}

// 体力の処理
void Panel::StepHp()
{
	// 残り手数が0なら実行
	if (StepCnt == 0 || isAllHit) {
		// 2秒経つまで処理を遅らせる
		if (FrameCnt == MISSTAKE_MAX_FRAME + 25) {
			FrameCnt = 0;
			if (StepCnt == 0) {
				HP--;
			}

			if (HP == 0 || isAllHit) {
				// 体力がなくなったならリザルトへ
				g_CurrentSceneID = SCENE_ID_FIN_PLAY;
			}
		}
		else if (FrameCnt == 0) {
			// パネルの要素をリセット
			ResetPanel();
			// 加算
			FrameCnt++;
		}
		else {
			// 加算
			FrameCnt++;
		}

		if (FrameCnt > MISSTAKE_MAX_FRAME + 25) {
			FrameCnt = MISSTAKE_MAX_FRAME + 25;
		}
	}
}

// 次の問題に向かう処理
void Panel::NextQuestion()
{
	g_CurrentSceneID = SCENE_ID_INIT_PLAY;

	switch (g_QuestonTypeID) {
		case QUESTION_TYPE_1:
			// プレイ初期化シーンへ
			g_QuestonTypeID = QUESTION_TYPE_2;
			break;
		case QUESTION_TYPE_2:
			g_CurrentSceneID = SCENE_ID_INIT_RESULT;
			// g_QuestonTypeID = QUESTION_TYPE_2;
			break;
		default:
			break;
	}

}

// 間違っているとき処理
void Panel::MissTake()
{
	// 間違っている部分を出す
	if (StepCnt == 0) {
		for (int PanelYIndex = 0; PanelYIndex < PANEL_Y_MAX_NUM; PanelYIndex++) {
			for (int PanelXIndex = 0; PanelXIndex < PANEL_X_MAX_NUM; PanelXIndex++) {
				if (anspanelInfo[PanelYIndex][PanelXIndex].isMissTake) {
					if (anspanelInfo[PanelYIndex][PanelXIndex].MissTakeCnt > MISSTAKE_MAX_FRAME) {
						anspanelInfo[PanelYIndex][PanelXIndex].MissTakeCnt = MISSTAKE_MAX_FRAME;
					}
					else if (anspanelInfo[PanelYIndex][PanelXIndex].MissTakeCnt == MISSTAKE_MAX_FRAME) {
						anspanelInfo[PanelYIndex][PanelXIndex].isMissTake = false;
					}
					else if (anspanelInfo[PanelYIndex][PanelXIndex].MissTakeCnt < MISSTAKE_MAX_FRAME) {
						anspanelInfo[PanelYIndex][PanelXIndex].MissTakeCnt++;
					}
				}
			}
		}
	}
}
