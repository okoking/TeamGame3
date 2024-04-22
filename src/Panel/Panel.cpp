#include "Panel.h"
#include "DxLib.h"
#include "../Collision/Collision.h"
#include "../Input/Input.h"

// �R���X�g���N�^
Panel::Panel()
{
	// ���]����p�l���̍��W
	InversionXpos = -10;
	InversionYpos = -10;

	// ��]�����邩�ǂ���
	isInside = false;
	isAllHit = false;

	// ��茈�ߗp
	questionLevel = (QUESTION_LEVEL)-1;
	questionType = (QUESTION_TYPE)-1;

	// �萔�J�E���g�p
	StepCnt = -1;

	// �c��HP 
	HP = -1;

	// �t���[���J�E���g�p
	FrameCnt = -1;
	EffectFrameCnt = -1;
	paneldisframeCnt = -1;

	for (int PanelYIndex = 0; PanelYIndex < PANEL_Y_MAX_NUM; PanelYIndex++) {
		for (int PanelXIndex = 0; PanelXIndex < PANEL_X_MAX_NUM; PanelXIndex++) {
			for (int PanelPatternindex = 0; PanelPatternindex < PANEL_PATTERN_NUM; PanelPatternindex++) {
				//�摜�n���h��
				questionpanelInfo[PanelYIndex][PanelXIndex].handle[PanelPatternindex] = -1;
				anspanelInfo[PanelYIndex][PanelXIndex].handle[PanelPatternindex] = -1;
			}


			// �p�l����]���t���O
			anspanelInfo[PanelYIndex][PanelXIndex].isInversion = false;

			// ��]�I���m�F�t���O
			anspanelInfo[PanelYIndex][PanelXIndex].isInversioned = false;

			// �Ԉ���Ă���t���O
			anspanelInfo[PanelYIndex][PanelXIndex].isMissTake = false;

			// �p�l���̖͗l�ۑ��p
			questionpanelInfo[PanelYIndex][PanelXIndex].Panelpattern = PANEL_PATTERN_NORMAL;
			anspanelInfo[PanelYIndex][PanelXIndex].Panelpattern = PANEL_PATTERN_NORMAL;

			// ���W
			questionpanelInfo[PanelYIndex][PanelXIndex].x = 0;
			anspanelInfo[PanelYIndex][PanelXIndex].x = 0;
			
			questionpanelInfo[PanelYIndex][PanelXIndex].y = 0;
			anspanelInfo[PanelYIndex][PanelXIndex].y = 0;

			// �g�p���t���O
			questionpanelInfo[PanelYIndex][PanelXIndex].isUse = false;
			anspanelInfo[PanelYIndex][PanelXIndex].isUse = false;

			anspanelInfo[PanelYIndex][PanelXIndex].MissTakeCnt = -1;

			// �t�@�C���ǂݍ��ݗp
			questionpanelInfo[PanelYIndex][PanelXIndex].m_FileReadLevelData = -1;
		}
	}
}

// �f�X�g���N�^
Panel::~Panel()
{
}

// �p�l��������
void Panel::Init()
{
	// �t���[���J�E���g�p
	FrameCnt = 1;
	EffectFrameCnt = 0;
	paneldisframeCnt = MISSTAKE_MAX_FRAME + 25;

	hearthandle = -1;

	// �G�t�F�N�g
	effect.Init();

	// ���]����p�l���̍��W
	InversionXpos = -10;
	InversionYpos = -10;
	
	// ��]�����邩�ǂ���
	isInside = false;
	isAllHit = false;

	// ��茈�ߗp
	//questionLevel = g_QuestonLevelID;
	//questionType = g_QuestonTypeID;

	// �c��萔�J�E���g�p
	StepCnt = STEP_NUM[g_QuestonLevelID][g_QuestonTypeID];

	// �c��HP 
	HP = INIT_HP;

	for (int PanelYIndex = 0; PanelYIndex < PANEL_Y_MAX_NUM; PanelYIndex++) {
		for (int PanelXIndex = 0; PanelXIndex < PANEL_X_MAX_NUM; PanelXIndex++) {
			for (int PanelPatternindex = 0; PanelPatternindex < PANEL_PATTERN_NUM; PanelPatternindex++) {
				// �摜�n���h��
				questionpanelInfo[PanelYIndex][PanelXIndex].handle[PanelPatternindex] = 0;
				anspanelInfo[PanelYIndex][PanelXIndex].handle[PanelPatternindex] = 0;
			}
			// �p�l����]���t���O
			anspanelInfo[PanelYIndex][PanelXIndex].isInversion = false;

			// ��]�I���m�F�t���O
			anspanelInfo[PanelYIndex][PanelXIndex].isInversioned = true;

			anspanelInfo[PanelYIndex][PanelXIndex].isMissTake = false;	// �Ԉ���Ă���t���O

			// �p�l���̖͗l�ۑ��p
			questionpanelInfo[PanelYIndex][PanelXIndex].Panelpattern = PANEL_PATTERN_NORMAL;
			anspanelInfo[PanelYIndex][PanelXIndex].Panelpattern = PANEL_PATTERN_NORMAL;

			// ���W
			questionpanelInfo[PanelYIndex][PanelXIndex].x = PANEL_SIZE * PanelXIndex;
			questionpanelInfo[PanelYIndex][PanelXIndex].y = PANEL_SIZE * PanelYIndex + 300;

			anspanelInfo[PanelYIndex][PanelXIndex].x = PANEL_SIZE * PanelXIndex + 500;
			anspanelInfo[PanelYIndex][PanelXIndex].y = PANEL_SIZE * PanelYIndex + 300;
			
			anspanelInfo[PanelYIndex][PanelXIndex].MissTakeCnt = MISSTAKE_MAX_FRAME;

			// �g�p���t���O
			// ���x���ɂ������͈͂�true�ɂ���
			if (PanelYIndex < PANEL_Y_NUM[g_QuestonLevelID] && PanelXIndex < PANEL_X_NUM[g_QuestonLevelID]) {
				questionpanelInfo[PanelYIndex][PanelXIndex].isUse = true;
				anspanelInfo[PanelYIndex][PanelXIndex].isUse = true;
			}

			// �t�@�C���ǂݍ��ݗp
			questionpanelInfo[PanelYIndex][PanelXIndex].m_FileReadLevelData = PANEL_PATTERN_NORMAL;
		}
	}
}

// �f�[�^���[�h
void Panel::Load()
{
	// �G�t�F�N�g
	effect.Load(EFFECT_TYPE_NORMAL, 9);
	effect.Load(EFFECT_TYPE_INSIDE, 9);

	hearthandle = LoadGraph(HEART_PATH);

	// �t�@�C���ǂݍ���
	ReadFile();

	for (int PanelYIndex = 0; PanelYIndex < PANEL_Y_MAX_NUM; PanelYIndex++) {
		for (int PanelXIndex = 0; PanelXIndex < PANEL_X_MAX_NUM; PanelXIndex++) {
			//�p�l���n���h��
			questionpanelInfo[PanelYIndex][PanelXIndex].handle[PANEL_PATTERN_NORMAL] = LoadGraph(NORMALPANEL_PATH);
			anspanelInfo[PanelYIndex][PanelXIndex].handle[PANEL_PATTERN_NORMAL] = LoadGraph(NORMALPANEL_PATH);

			//���]�����p�l���n���h��
			questionpanelInfo[PanelYIndex][PanelXIndex].handle[PANEL_PATTERN_INSIDE] = LoadGraph(INSIDEPANEL_PATH);
			anspanelInfo[PanelYIndex][PanelXIndex].handle[PANEL_PATTERN_INSIDE] = LoadGraph(INSIDEPANEL_PATH);

			// �ǂݍ��񂾃f�[�^����
			questionpanelInfo[PanelYIndex][PanelXIndex].Panelpattern = (PANEL_PATTERN)questionpanelInfo[PanelYIndex][PanelXIndex].m_FileReadLevelData;
			anspanelInfo[PanelYIndex][PanelXIndex].Panelpattern = (PANEL_PATTERN)anspanelInfo[PanelYIndex][PanelXIndex].m_FileReadLevelData;
		}
	}
}

// �t�@�C���ǂݍ���
void Panel::ReadFile()
{
	FILE* fp;

	fopen_s(&fp, QuestionCsvFilePath[g_QuestonLevelID][g_QuestonTypeID], "r");

	int mapIndexX = 0;
	int mapIndexY = 0;

	while (true) {
		// ���l������ǂݍ���
		fscanf_s(fp, "%d", &questionpanelInfo[mapIndexY][mapIndexX].m_FileReadLevelData);
		mapIndexX++;

		// �u,�v���΂����߂ɓǂݍ��݂����s
		char chara = fgetc(fp);

		// EOF�̏ꍇ�͓ǂݍ��ݏI��
		if (chara == EOF) {
			break;
		}

		// ���s�R�[�h�̏ꍇ�͕ۑ����ύX����
		if (chara == '\n') {
			mapIndexY++;
			mapIndexX = 0;
		}
	}

	fopen_s(&fp, AnsCsvFilePath[g_QuestonLevelID][g_QuestonTypeID], "r");

	mapIndexX = 0;
	mapIndexY = 0;

	while (true) {
		// ���l������ǂݍ���
		fscanf_s(fp, "%d", &anspanelInfo[mapIndexY][mapIndexX].m_FileReadLevelData);
		mapIndexX++;

		// �u,�v���΂����߂ɓǂݍ��݂����s
		char chara = fgetc(fp);

		// EOF�̏ꍇ�͓ǂݍ��ݏI��
		if (chara == EOF) {
			break;
		}

		// ���s�R�[�h�̏ꍇ�͕ۑ����ύX����
		if (chara == '\n') {
			mapIndexY++;
			mapIndexX = 0;
		}
	}

	fclose(fp);
}

// �p�l���̒ʏ폈��
void Panel::Step()
{
	// �G�t�F�N�g
	effect.Step();

	// �p�l���ƃ}�E�X�̓����蔻��
	PaneltoMouseCollision();

	// �p�l�����]�p
	InversionPanel();

	// �p�l���̖͗l����v���Ă��邩
	PanelPatternMatch();

	// �̗͂̏���
	StepHp();

	// �Ԉ���Ă���Ƃ�����
	MissTake();

}

// �p�l���̕`��
void Panel::Draw()
{
	for (int PanelYIndex = 0; PanelYIndex < PANEL_Y_MAX_NUM; PanelYIndex++) {
		for (int PanelXIndex = 0; PanelXIndex < PANEL_X_MAX_NUM; PanelXIndex++) {
			// ���
			if (questionpanelInfo[PanelYIndex][PanelXIndex].isUse) {
				DrawGraph(questionpanelInfo[PanelYIndex][PanelXIndex].x, questionpanelInfo[PanelYIndex][PanelXIndex].y,
					questionpanelInfo[PanelYIndex][PanelXIndex].handle[questionpanelInfo[PanelYIndex][PanelXIndex].Panelpattern], true);
			}

			// ��
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


	DrawFormatString(0, 64, GetColor(255, 255, 255), "�c��萔�F%d", StepCnt, true);


	// �G�t�F�N�g
	effect.Draw();

}

// �p�l���I������
void Panel::Fin()
{
	// �G�t�F�N�g
	effect.Fin();

	for (int PanelYIndex = 0; PanelYIndex < PANEL_Y_MAX_NUM; PanelYIndex++) {
		for (int PanelXIndex = 0; PanelXIndex < PANEL_X_MAX_NUM; PanelXIndex++) {
			//�p�l���n���h��
			DeleteGraph(questionpanelInfo[PanelYIndex][PanelXIndex].handle[PANEL_PATTERN_NORMAL]);
			DeleteGraph(questionpanelInfo[PanelYIndex][PanelXIndex].handle[PANEL_PATTERN_NORMAL]);

			//���]�����p�l���n���h��
			DeleteGraph(anspanelInfo[PanelYIndex][PanelXIndex].handle[PANEL_PATTERN_INSIDE]);
			DeleteGraph(anspanelInfo[PanelYIndex][PanelXIndex].handle[PANEL_PATTERN_INSIDE]);

		}
	}
	DeleteGraph(hearthandle);

	g_CurrentSceneID = SCENE_ID_INIT_RESULT;

	if (isAllHit) {
		// ���̖��Ɍ���������
		NextQuestion();
	}

}

// �p�l���̗v�f�����Z�b�g
void Panel::ResetPanel()
{
	// �c��萔�J�E���g������
	StepCnt = STEP_NUM[g_QuestonLevelID][g_QuestonTypeID];

	Sound::Se::Play(SE_MISS);

	for (int PanelYIndex = 0; PanelYIndex < PANEL_Y_MAX_NUM; PanelYIndex++) {
		for (int PanelXIndex = 0; PanelXIndex < PANEL_X_MAX_NUM; PanelXIndex++) {
			// �ǂݍ��񂾃f�[�^����
			anspanelInfo[PanelYIndex][PanelXIndex].Panelpattern = (PANEL_PATTERN)anspanelInfo[PanelYIndex][PanelXIndex].m_FileReadLevelData;
		}
	}
}

// �p�l���ƃ}�E�X�̓����蔻��
void Panel::PaneltoMouseCollision()
{
	// ��]���Ă���Ȃ�Ƃ�Ȃ�
	if (EffectFrameCnt == 0) {
		int MousePosX, MousePosY;

		GetMousePoint(&MousePosX, &MousePosY);

		for (int PanelYIndex = 0; PanelYIndex < PANEL_Y_MAX_NUM; PanelYIndex++) {
			for (int PanelXIndex = 0; PanelXIndex < PANEL_X_MAX_NUM; PanelXIndex++) {
				if (anspanelInfo[PanelYIndex][PanelXIndex].isUse) {
					if (Collision::Rect(anspanelInfo[PanelYIndex][PanelXIndex].x, anspanelInfo[PanelYIndex][PanelXIndex].y, PANEL_SIZE, PANEL_SIZE,
						MousePosX, MousePosY, 1, 1)) {
						if (Input::Mouse::Push(MOUSE_INPUT_LEFT)) {
							// ���]�����ォ��n�߂�
							InversionXpos = PanelXIndex - 1;
							InversionYpos = PanelYIndex - 1;

							// ���]���n�߂�
							isInside = true;

							// ���]���m�F����
							anspanelInfo[PanelYIndex][PanelXIndex].isInversion = true;

							paneldisframeCnt = 0;

							//se
							Sound::Se::Play(SE_CLICK_PANEL);

							// �c��萔�J�E���g�f�N�������g
							StepCnt--;
						}
					}
				}
			}
		}	
	}
	paneldisframeCnt++;
}

// �p�l�����]�p
void Panel::InversionPanel()
{
	if (isInside) {	// ���]�J�n
		if (EffectFrameCnt == 0) {	// �������
			for (int PanelYIndex = InversionYpos; PanelYIndex < InversionYpos + 3; PanelYIndex++) {
				for (int PanelXIndex = InversionXpos; PanelXIndex < InversionXpos + 3; PanelXIndex++) {
					// ���]����ꏊ���p�l���͈̔͊O�Ȃ��΂�
					if (PanelYIndex < 0 || PanelYIndex >= PANEL_Y_MAX_NUM || PanelXIndex < 0 || PanelXIndex >= PANEL_X_MAX_NUM) {
						continue;
					}

					if (anspanelInfo[PanelYIndex][PanelXIndex].isUse) {
						if (anspanelInfo[PanelYIndex][PanelXIndex].Panelpattern == PANEL_PATTERN_NORMAL) {
							effect.Play(EFFECT_TYPE_NORMAL,
								anspanelInfo[PanelYIndex][PanelXIndex].x + PANEL_SIZE / 2, anspanelInfo[PanelYIndex][PanelXIndex].y + PANEL_SIZE / 2);
							// �p�l����]���t���O
							anspanelInfo[PanelYIndex][PanelXIndex].isInversion = true;

							anspanelInfo[PanelYIndex][PanelXIndex].Panelpattern = PANEL_PATTERN_INSIDE;
						}
						else {
							effect.Play(EFFECT_TYPE_INSIDE,
								anspanelInfo[PanelYIndex][PanelXIndex].x + PANEL_SIZE / 2, anspanelInfo[PanelYIndex][PanelXIndex].y + PANEL_SIZE / 2);
							// �p�l����]���t���O
							anspanelInfo[PanelYIndex][PanelXIndex].isInversion = true;

							anspanelInfo[PanelYIndex][PanelXIndex].Panelpattern = PANEL_PATTERN_NORMAL;
						}
					}
				}
			}
		}

		EffectFrameCnt++;

		if (EffectFrameCnt > 25) {
			// ���]���I��点��
			isInside = false;
			EffectFrameCnt = 0;
			for (int PanelYIndex = InversionYpos; PanelYIndex < InversionYpos + 3; PanelYIndex++) {
				for (int PanelXIndex = InversionXpos; PanelXIndex < InversionXpos + 3; PanelXIndex++) {
					if (anspanelInfo[PanelYIndex][PanelXIndex].isInversion) {
						anspanelInfo[PanelYIndex][PanelXIndex].isInversion = false;
					}
					// �Ԉ���Ă��镔�����o��
					if (anspanelInfo[PanelYIndex][PanelXIndex].Panelpattern != questionpanelInfo[PanelYIndex][PanelXIndex].Panelpattern) {
						anspanelInfo[PanelYIndex][PanelXIndex].isMissTake = true;
						anspanelInfo[PanelYIndex][PanelXIndex].MissTakeCnt = 0;
					}
				}
			}
		}
	}
}

// �p�l���̖͗l����v���Ă��邩
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
				// ���ׂĈ�v����Ȃ玟�̖���
				if (Cnt == PANEL_Y_NUM[g_QuestonLevelID] * PANEL_X_NUM[g_QuestonLevelID]) {
					isAllHit = true;
				}
			}
		}
	}
}

// �̗͂̏���
void Panel::StepHp()
{
	// �c��萔��0�Ȃ���s
	if (StepCnt == 0 || isAllHit) {
		// 2�b�o�܂ŏ�����x�点��
		if (FrameCnt == MISSTAKE_MAX_FRAME + 25) {
			FrameCnt = 0;
			if (StepCnt == 0) {
				HP--;
			}

			if (HP == 0 || isAllHit) {
				// �̗͂��Ȃ��Ȃ����Ȃ烊�U���g��
				g_CurrentSceneID = SCENE_ID_FIN_PLAY;
			}
		}
		else if (FrameCnt == 0) {
			// �p�l���̗v�f�����Z�b�g
			ResetPanel();
			// ���Z
			FrameCnt++;
		}
		else {
			// ���Z
			FrameCnt++;
		}

		if (FrameCnt > MISSTAKE_MAX_FRAME + 25) {
			FrameCnt = MISSTAKE_MAX_FRAME + 25;
		}
	}
}

// ���̖��Ɍ���������
void Panel::NextQuestion()
{
	g_CurrentSceneID = SCENE_ID_INIT_PLAY;

	switch (g_QuestonTypeID) {
		case QUESTION_TYPE_1:
			// �v���C�������V�[����
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

// �Ԉ���Ă���Ƃ�����
void Panel::MissTake()
{
	// �Ԉ���Ă��镔�����o��
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
