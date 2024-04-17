#pragma once
#include "DxLib.h"
#include "../Input/Input.h"

const char HEART_PATH[] = {"data/play/kari_heart2.png"};		//�n�[�g�̉摜�p�X
const char SHIELD_PATH[] = { "data/play/shield.png" };		//�V�[���h�̉摜�p�X
const char HP_PATH[] = { "data/play/HP.png" };		//HP�̉摜�p�X

// �v���C���[�̉摜�T�C�Y
const int HEART_SIZE = 32; // �n�[�g

const int SHIELD_WIDTH = 32;  // �V�[���h
const int SHIELD_HEIGHT = 16;

// �v���C���[�̏����̗�
const int PLAYER_HP = 5;

// �v���C���[�̖��G����
const int PLAYER_INVINCIBLE_TIME = 90;

// �v���C���[�̏����ʒu
const float HEART_INIT_POS_X = 400.0f;
const float HEART_INIT_POS_Y = 300.0f;

// ���̌����Ă������
enum SHIELD_ANGLE {
	SHIELD_ANGLE_RIGHT = 0,
	SHIELD_ANGLE_DOWN,
	SHIELD_ANGLE_LEFT,
	SHIELD_ANGLE_UP,
};

class Player
{
private:
	float HeartposX, HeartposY;		// �n�[�g�̍��W
	int HeartImageHundle;		// �n�[�g�摜�n���h��
	
	float ShieldposX, ShieldposY;	// �V�[���h�̉摜�T�C�Y
	int ShieldImageHundle;		// �V�[���h�̉摜�n���h��
	float Shieldangle;			// �V�[���h�̊p�x
	SHIELD_ANGLE CurrentShieldangle; // ���݂̏��̌���

	int Hp;	// �v���C���[��HP
	int invincibletimeCnt; // �v���C���[�̖��G���ԃJ�E���g�p
	bool isActive; // �v���C���[�������Ă��邩
	bool isDraw; // �`�悳��邩 

	int HpHundle;	// HP�̑����n���h��

	// HP�o�[�̐F�ۑ��p
	unsigned int Cr;

	// �K�[�h������
	int GuardCnt;

	//�v���C���[���쏈��
	void Operation();

	// ���G���ԏ���
	void Invincible();

public:
	//�v���C���[�̏�����
	void Init();

	//�v���C���[�̓ǂݍ��ݏ���
	void Load();

	//�v���C���[�̒ʏ폈��
	void Step();

	//�v���C���[�֘A�̕`�揈��
	void Draw();

	//�v���C���[�̏I������
	void Fin();

	// �v���C���[�_���[�W����
	void Damaged();

	// ���̌����擾�p
	SHIELD_ANGLE GetShieldAngle() { return CurrentShieldangle; }

	// �K�[�h�����Z
	void AddGuardCnt() { GuardCnt++; };

	// �K�[�h���擾�p
	int GetGuradCnt() { return GuardCnt; }
};
