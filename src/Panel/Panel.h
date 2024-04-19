#pragma once
#include "../Scene/Scene.h"

// �p�l���̖͗l
enum PANEL_PATTERN {
	PANEL_PATTERN_NORMAL = 0,	// �ʏ�
	PANEL_PATTERN_INSIDE,		// ��

	PANEL_PATTERN_NUM,
};

// �p�l���̎��
enum PANEL_TYPE
{
	PANEL_TYPE_QUESTION = 0,	// ���
	PANEL_TYPE_ANS,				// ��

	PANEL_TYPE_NUM,
};

// �p�l���̉摜�t�@�C���p�X
const char NORMALPANEL_PATH[] = { "data/play/�p�l���\.png" };
const char INSIDEPANEL_PATH[] = { "data/play/�p�l����.png" };

// �摜�T�C�Y
const int PANEL_SIZE = 64;

// �����̗�
const int INIT_HP = 3;

// csv�֌W===========================================
// �p�l���̔z�u
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

// ���̎��
enum QUESTION_TYPE
{
	QUESTION_TYPE_1 = 0,
	QUESTION_TYPE_2,

	QUESTION_TYPE_NUM,
};

// csv�̃t�@�C���p�X
// ���̕�
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
// �񓚂̕�
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

// �e���̎萔
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
	int handle[PANEL_PATTERN_NUM];		//�摜�n���h��

	int m_FileReadLevelData;		// �t�@�C���ǂݍ��ݗp

	PANEL_PATTERN Panelpattern;	// �p�l���̖͗l�ۑ��p

	int x, y;			// ���W
	bool isUse;			// �g�p���t���O
};

class Panel
{
private:
	PanelInfo questionpanelInfo[PANEL_Y_MAX_NUM][PANEL_X_MAX_NUM];
	PanelInfo anspanelInfo[PANEL_Y_MAX_NUM][PANEL_X_MAX_NUM];

	int InversionXpos, InversionYpos;	// ���]����p�l���̍��W

	bool isInside;	// ��]�����邩�ǂ���

	bool isInversion;	// �p�l����]���t���O
	bool isInversioned; // ��]�I���m�F�t���O

	// ��茈�ߗp
	QUESTION_LEVEL questionLevel;
	QUESTION_TYPE questionType;

	// �c��萔�J�E���g�p
	int StepCnt;

	// �c��HP 
	int HP;

public:
	Panel();
	~Panel();

	// �p�l��������
	void Init();

	// �f�[�^���[�h
	void Load();

	// �t�@�C���ǂݍ���
	void ReadFile();

	// �p�l���̒ʏ폈��
	void Step();

	// �p�l���̕`��
	void Draw();

	// �p�l���I������
	void Fin();

	// �񓚂���p�l�����\���̂̎g�p���t���O���擾
	bool IsUse(int _xindex, int _yindex) const { return anspanelInfo[_xindex][_yindex].isUse; }

	// �񓚂���p�l�����\���̂̎g�p���t���O��ݒ�
	void SetUse(int _xindex, int _yindex, bool _isUse) { anspanelInfo[_xindex][_yindex].isUse = _isUse; }

	// �񓚂���p�l�����\���̂�X���W���擾
	int GetPosX(int _xindex, int _yindex) const { return anspanelInfo[_xindex][_yindex].x; }

	// �񓚂���p�l�����\���̂�Y���W���擾
	int GetPosY(int _xindex, int _yindex) const { return anspanelInfo[_xindex][_yindex].y; }

	// �񓚂���p�l���̖͗l���擾
	PANEL_PATTERN GetPanelAngle(int _xindex, int _yindex) const { return anspanelInfo[_xindex][_yindex].Panelpattern; }

	// �p�l���̗v�f�����Z�b�g
	void ResetPanel();

	// ��]���t���O�擾�p
	bool GetisInversion() const { return isInversion; }

	// �p�l���ƃ}�E�X�̓����蔻��
	void PaneltoMouseCollision();

	// �p�l�����]�p
	void InversionPanel();

	// �p�l���̖͗l����v���Ă��邩
	void PanelPatternMatch();

	// �̗͂̏���
	void StepHp();

	// ���̖��Ɍ���������
	void NextQuestion();
};
