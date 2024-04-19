#include "Panel.h"
#include "DxLib.h"
#include "../Collision/Collision.h"
#include "../Input/Input.h"
#include "../Scene/Scene.h"

int g_FrameCnt = 0;

// �R���X�g���N�^
Panel::Panel()
{
	// ���]����p�l���̍��W
	InversionXpos = -10;
	InversionYpos = -10;

	// ��]�����邩�ǂ���
	isInside = false;

	// �p�l����]���t���O
	isInversion = false;

	// ��]�I���m�F�t���O
	isInversioned = false;

	// ��茈�ߗp
	questionLevel = (QUESTION_LEVEL)-1;
	questionType = (QUESTION_TYPE)-1;

	// �萔�J�E���g�p
	StepCnt = -1;

	// �c��HP 
	HP = -1;

	for (int PanelYIndex = 0; PanelYIndex < PANEL_Y_MAX_NUM; PanelYIndex++) {
		for (int PanelXIndex = 0; PanelXIndex < PANEL_X_MAX_NUM; PanelXIndex++) {
			for (int PanelPatternindex = 0; PanelPatternindex < PANEL_PATTERN_NUM; PanelPatternindex++) {
				//�摜�n���h��
				questionpanelInfo[PanelYIndex][PanelXIndex].handle[PanelPatternindex] = -1;
				anspanelInfo[PanelYIndex][PanelXIndex].handle[PanelPatternindex] = -1;
			}

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
	// ���]����p�l���̍��W
	InversionXpos = -10;
	InversionYpos = -10;
	
	// ��]�����邩�ǂ���
	isInside = false;

	// ��茈�ߗp
	questionLevel = QUESTION_LEVEL_44;
	questionType = QUESTION_TYPE_1;

	// �c��萔�J�E���g�p
	StepCnt = STEP_NUM[questionLevel][questionType];

	// �c��HP 
	HP = INIT_HP;

	// �p�l����]���t���O
	isInversion = false;

	// ��]�I���m�F�t���O
	isInversioned = true;

	for (int PanelYIndex = 0; PanelYIndex < PANEL_Y_MAX_NUM; PanelYIndex++) {
		for (int PanelXIndex = 0; PanelXIndex < PANEL_X_MAX_NUM; PanelXIndex++) {
			for (int PanelPatternindex = 0; PanelPatternindex < PANEL_PATTERN_NUM; PanelPatternindex++) {
				// �摜�n���h��
				questionpanelInfo[PanelYIndex][PanelXIndex].handle[PanelPatternindex] = 0;
				anspanelInfo[PanelYIndex][PanelXIndex].handle[PanelPatternindex] = 0;
			}

			// �p�l���̖͗l�ۑ��p
			questionpanelInfo[PanelYIndex][PanelXIndex].Panelpattern = PANEL_PATTERN_NORMAL;
			anspanelInfo[PanelYIndex][PanelXIndex].Panelpattern = PANEL_PATTERN_NORMAL;

			// ���W
			questionpanelInfo[PanelYIndex][PanelXIndex].x = PANEL_SIZE * PanelXIndex;
			questionpanelInfo[PanelYIndex][PanelXIndex].y = PANEL_SIZE * PanelYIndex + 300;

			anspanelInfo[PanelYIndex][PanelXIndex].x = PANEL_SIZE * PanelXIndex + 400;
			anspanelInfo[PanelYIndex][PanelXIndex].y = PANEL_SIZE * PanelYIndex + 300;

			// �g�p���t���O
			// ���x���ɂ������͈͂�true�ɂ���
			if (PanelYIndex < PANEL_Y_NUM[questionLevel] && PanelXIndex < PANEL_X_NUM[questionLevel]) {
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

	fopen_s(&fp, QuestionCsvFilePath[questionLevel][questionType], "r");

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

	fopen_s(&fp, AnsCsvFilePath[questionLevel][questionType], "r");

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
	// �p�l���ƃ}�E�X�̓����蔻��
	PaneltoMouseCollision();

	// �p�l�����]�p
	InversionPanel();

	// �p�l���̖͗l����v���Ă��邩
	PanelPatternMatch();

	// �̗͂̏���
	StepHp();
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
				DrawGraph(anspanelInfo[PanelYIndex][PanelXIndex].x, anspanelInfo[PanelYIndex][PanelXIndex].y,
					anspanelInfo[PanelYIndex][PanelXIndex].handle[anspanelInfo[PanelYIndex][PanelXIndex].Panelpattern], true);
			}

			// �c��HP�Ǝ萔�̕\��
			//�����̑傫����ύX
			SetFontSize(32);

			DrawFormatString(0, 0, GetColor(255, 255, 255), "�c��HP�F%d", HP, true);
			DrawFormatString(0, 32, GetColor(255, 255, 255), "�c��萔�F%d", StepCnt, true);
			DrawFormatString(0, 64, GetColor(255, 255, 255), "g_FrameCnt�F%d", g_FrameCnt, true);
		}
	}
}

// �p�l���I������
void Panel::Fin()
{
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
}

// �p�l���̗v�f�����Z�b�g
void Panel::ResetPanel()
{
	// �c��萔�J�E���g������
	StepCnt = STEP_NUM[questionLevel][questionType];

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
	if (g_FrameCnt == 0) {
		int MousePosX, MousePosY;

		GetMousePoint(&MousePosX, &MousePosY);

		for (int PanelYIndex = 0; PanelYIndex < PANEL_Y_MAX_NUM; PanelYIndex++) {
			for (int PanelXIndex = 0; PanelXIndex < PANEL_X_MAX_NUM; PanelXIndex++) {
				if (anspanelInfo[PanelYIndex][PanelXIndex].isUse) {
					if (Collision::Rect(anspanelInfo[PanelYIndex][PanelXIndex].x, anspanelInfo[PanelYIndex][PanelXIndex].y, PANEL_SIZE, PANEL_SIZE,
						MousePosX, MousePosY, 1, 1)) {
						// �}�E�X�J�[�\�����p�l���ɓ������Ă���Ȃ�͂�
						// ���ł����ɒ��ڏ����Ă�
						DrawLineBox(anspanelInfo[PanelYIndex][PanelXIndex].x, anspanelInfo[PanelYIndex][PanelXIndex].y,
							anspanelInfo[PanelYIndex][PanelXIndex].x + PANEL_SIZE, anspanelInfo[PanelYIndex][PanelXIndex].y + PANEL_SIZE, GetColor(255, 255, 255));

						if (Input::Mouse::Push(MOUSE_INPUT_LEFT)) {
							// ���]�����ォ��n�߂�
							InversionXpos = PanelXIndex - 1;
							InversionYpos = PanelYIndex - 1;

							// ���]���n�߂�
							isInside = true;

							// �c��萔�J�E���g�f�N�������g
							StepCnt--;
						}
					}
				}
			}
		}
	}
}

// �p�l�����]�p
void Panel::InversionPanel()
{
	if (isInside) {	// ���]�J�n
		for (int PanelYIndex = InversionYpos; PanelYIndex < InversionYpos + 3; PanelYIndex++) {
			for (int PanelXIndex = InversionXpos; PanelXIndex < InversionXpos + 3; PanelXIndex++) {
				// ���]����ꏊ���p�l���͈̔͊O�Ȃ��΂�
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
					// ���]���I��点��
					isInside = false;
				}
			}
		}
	}
}

// �p�l���̖͗l����v���Ă��邩
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
				// ���ׂĈ�v����Ȃ玟�̖���
				if (Cnt == PANEL_Y_NUM[questionLevel]* PANEL_X_NUM[questionLevel]) {
					// ���̖��Ɍ���������
					NextQuestion();
				}
			}
		}
	}
}

// �̗͂̏���
void Panel::StepHp()
{
	if (StepCnt < 0) {
		StepCnt = 0;
	}

	// �c��萔��0�Ȃ���s
	if (StepCnt == 0) {
		// 3�b�o�܂ŏ�����x�点��
		if (g_FrameCnt == 180) {
			g_FrameCnt = 0;
			HP--;

			if (HP == 0) {
				// �̗͂��Ȃ��Ȃ����Ȃ烊�U���g��
				g_CurrentSceneID = SCENE_ID_INIT_RESULT;
			}

			// �p�l���̗v�f�����Z�b�g
			ResetPanel();
		}
		else {
			// ���Z
			g_FrameCnt++;
		}

		if (g_FrameCnt > 180) {
			g_FrameCnt = 180;
		}
	}
}

// ���̖��Ɍ���������
void Panel::NextQuestion()
{
	// �v���C�������V�[����
	g_CurrentSceneID = SCENE_ID_INIT_PLAY;

}
