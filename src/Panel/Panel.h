#pragma once

// �p�l���̖͗l
enum PANEL_PATTERN {
	PANEL_PATTERN_NORMAL = 0,	// �ʏ�
	PANEL_PATTERN_INSIDE,		// ��

	PANEL_PATTERN_NUM,
};

// �p�l���̎��
enum PANEL_TYPE
{
	PANEL_TYPE_PROBLEM = 0,	// ���
	PANEL_TYPE_ANS,			// ��

	PANEL_TYPE_NUM,
};

// �p�l���̉摜�t�@�C���p�X
const char NORMALPANEL_PATH[] = { "data/play/�p�l���\.png" };
const char INSIDEPANEL_PATH[] = { "data/play/�p�l����.png" };

// �摜�T�C�Y
const int PANEL_SIZE = 40;

// �p�l���̔z�u
const int PANEL_X_NUM = 5;
const int PANEL_Y_NUM = 5;

struct PanelInfo
{
	int handle[PANEL_PATTERN_NUM];		//�摜�n���h��
	PANEL_PATTERN Panelpattern;	// �p�l���̖͗l�ۑ��p

	int x, y;			// ���W
	bool isUse;			// �g�p���t���O
	bool isInversion;	// �p�l����]���t���O
	bool isInversioned; // ��]�I���m�F�t���O
};

class Panel
{
private:
	PanelInfo problempanelInfo[PANEL_Y_NUM][PANEL_X_NUM];
	PanelInfo anspanelInfo[PANEL_Y_NUM][PANEL_X_NUM];

	int InversionXpos, InversionYpos;	// ���]����p�l���̍��W

	bool isInside;	// ��]�����邩�ǂ���

public:
	Panel();
	~Panel();

	// �p�l��������
	void Init();

	// �f�[�^���[�h
	void Load();

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

	// �p�l���̃����_���v�f�����Z�b�g
	void ResetPanel(int _xindex, int _yindex);

	// ��]���t���O�擾�p
	bool GetisInversion(int _xindex, int _yindex) const { return anspanelInfo[_xindex][_yindex].isInversion; }

	// �p�l���ƃ}�E�X�̓����蔻��
	void PaneltoMouseCollision();

	// �p�l�����]�p
	void InversionPanel();

	// �p�l���̖͗l����v���Ă��邩
	void PanelPatternMatch();
};
