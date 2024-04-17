#include "Panel.h"
#include "DxLib.h"
#include "../Collision/Collision.h"
#include "../Input/Input.h"
#include "../Scene/Scene.h"

// �R���X�g���N�^
Panel::Panel()
{
	// ���]����p�l���̍��W
	InversionXpos = -10;
	InversionYpos = -10;

	// ��]�����邩�ǂ���
	isInside = false;

	for (int PanelYIndex = 0; PanelYIndex < PANEL_X_NUM; PanelYIndex++) {
		for (int PanelXIndex = 0; PanelXIndex < PANEL_Y_NUM; PanelXIndex++) {
			for (int PanelPatternindex = 0; PanelPatternindex < PANEL_PATTERN_NUM; PanelPatternindex++) {
				//�摜�n���h��
				problempanelInfo[PanelYIndex][PanelXIndex].handle[PanelPatternindex] = -1;
				anspanelInfo[PanelYIndex][PanelXIndex].handle[PanelPatternindex] = -1;
			}

			// �p�l���̖͗l�ۑ��p
			problempanelInfo[PanelYIndex][PanelXIndex].Panelpattern = PANEL_PATTERN_NORMAL;
			anspanelInfo[PanelYIndex][PanelXIndex].Panelpattern = PANEL_PATTERN_NORMAL;

			// ���W
			problempanelInfo[PanelYIndex][PanelXIndex].x = 0;
			anspanelInfo[PanelYIndex][PanelXIndex].x = 0;
			
			problempanelInfo[PanelYIndex][PanelXIndex].y = 0;
			anspanelInfo[PanelYIndex][PanelXIndex].y = 0;

			// �g�p���t���O
			problempanelInfo[PanelYIndex][PanelXIndex].isUse = false;
			anspanelInfo[PanelYIndex][PanelXIndex].isUse = false;

			// �p�l����]���t���O
			problempanelInfo[PanelYIndex][PanelXIndex].isInversion = false;
			anspanelInfo[PanelYIndex][PanelXIndex].isInversion = false;

			// ��]�I���m�F�t���O
			problempanelInfo[PanelYIndex][PanelXIndex].isInversioned = false;
			anspanelInfo[PanelYIndex][PanelXIndex].isInversioned = false;
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

	for (int PanelYIndex = 0; PanelYIndex < PANEL_X_NUM; PanelYIndex++) {
		for (int PanelXIndex = 0; PanelXIndex < PANEL_Y_NUM; PanelXIndex++) {
			for (int PanelPatternindex = 0; PanelPatternindex < PANEL_PATTERN_NUM; PanelPatternindex++) {
				// �摜�n���h��
				problempanelInfo[PanelYIndex][PanelXIndex].handle[PanelPatternindex] = 0;
				anspanelInfo[PanelYIndex][PanelXIndex].handle[PanelPatternindex] = 0;
			}

			// �p�l���̖͗l�ۑ��p
			problempanelInfo[PanelYIndex][PanelXIndex].Panelpattern = PANEL_PATTERN_INSIDE;
			anspanelInfo[PanelYIndex][PanelXIndex].Panelpattern = PANEL_PATTERN_NORMAL;

			// ���W
			problempanelInfo[PanelYIndex][PanelXIndex].x = PANEL_SIZE * PanelXIndex;
			problempanelInfo[PanelYIndex][PanelXIndex].y = PANEL_SIZE * PanelYIndex + 300;

			anspanelInfo[PanelYIndex][PanelXIndex].x = PANEL_SIZE * PanelXIndex + 400;
			anspanelInfo[PanelYIndex][PanelXIndex].y = PANEL_SIZE * PanelYIndex + 300;

			// �g�p���t���O
			problempanelInfo[PanelYIndex][PanelXIndex].isUse = true;
			anspanelInfo[PanelYIndex][PanelXIndex].isUse = true;

			// �p�l����]���t���O
			problempanelInfo[PanelYIndex][PanelXIndex].isInversion = false;
			anspanelInfo[PanelYIndex][PanelXIndex].isInversion = false;

			// ��]�I���m�F�t���O
			problempanelInfo[PanelYIndex][PanelXIndex].isInversioned = true;
			anspanelInfo[PanelYIndex][PanelXIndex].isInversioned = true;
		}
	}
}

// �f�[�^���[�h
void Panel::Load()
{
	for (int PanelYIndex = 0; PanelYIndex < PANEL_X_NUM; PanelYIndex++) {
		for (int PanelXIndex = 0; PanelXIndex < PANEL_Y_NUM; PanelXIndex++) {
			//�p�l���n���h��
			problempanelInfo[PanelYIndex][PanelXIndex].handle[PANEL_PATTERN_NORMAL] = LoadGraph(NORMALPANEL_PATH);
			anspanelInfo[PanelYIndex][PanelXIndex].handle[PANEL_PATTERN_NORMAL] = LoadGraph(NORMALPANEL_PATH);

			//���]�����p�l���n���h��
			problempanelInfo[PanelYIndex][PanelXIndex].handle[PANEL_PATTERN_INSIDE] = LoadGraph(INSIDEPANEL_PATH);
			anspanelInfo[PanelYIndex][PanelXIndex].handle[PANEL_PATTERN_INSIDE] = LoadGraph(INSIDEPANEL_PATH);
		}
	}
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
}

// �p�l���̕`��
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

// �p�l���I������
void Panel::Fin()
{
	for (int PanelYIndex = 0; PanelYIndex < PANEL_X_NUM; PanelYIndex++) {
		for (int PanelXIndex = 0; PanelXIndex < PANEL_Y_NUM; PanelXIndex++) {
			//�p�l���n���h��
			DeleteGraph(problempanelInfo[PanelYIndex][PanelXIndex].handle[PANEL_PATTERN_NORMAL]);
			DeleteGraph(problempanelInfo[PanelYIndex][PanelXIndex].handle[PANEL_PATTERN_NORMAL]);

			//���]�����p�l���n���h��
			DeleteGraph(anspanelInfo[PanelYIndex][PanelXIndex].handle[PANEL_PATTERN_INSIDE]);
			DeleteGraph(anspanelInfo[PanelYIndex][PanelXIndex].handle[PANEL_PATTERN_INSIDE]);
		}
	}
}

// �p�l���̃����_���v�f�����Z�b�g
void Panel::ResetPanel(int _xindex, int _yindex)
{
}

// �p�l���ƃ}�E�X�̓����蔻��
void Panel::PaneltoMouseCollision()
{
	int MousePosX, MousePosY;

	GetMousePoint(&MousePosX, &MousePosY);

	for (int PanelYIndex = 0; PanelYIndex < PANEL_X_NUM; PanelYIndex++) {
		for (int PanelXIndex = 0; PanelXIndex < PANEL_Y_NUM; PanelXIndex++) {
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
				if (PanelYIndex < 0 || PanelYIndex >= PANEL_Y_NUM || PanelXIndex < 0 || PanelXIndex >= PANEL_X_NUM) {
					continue;
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

	// ���]���I��点��
	isInside = false;
}

// �p�l���̖͗l����v���Ă��邩
void Panel::PanelPatternMatch()
{
	for (int PanelYIndex = 0; PanelYIndex < PANEL_X_NUM; PanelYIndex++) {
		for (int PanelXIndex = 0; PanelXIndex < PANEL_Y_NUM; PanelXIndex++) {
			// �ЂƂł���v���Ȃ��Ȃ�break����
			if (anspanelInfo[PanelYIndex][PanelXIndex].Panelpattern != problempanelInfo[PanelYIndex][PanelXIndex].Panelpattern) {
				break;
			}

			// ���ׂĈ�v����Ȃ烊�U���g��
			if (PanelXIndex == PANEL_X_NUM - 1 && PanelYIndex == PANEL_Y_NUM - 1) {
				g_CurrentSceneID = SCENE_ID_INIT_RESULT;
			}
		}
	}
}
