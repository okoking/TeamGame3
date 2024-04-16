#pragma once
#include "DxLib.h"
#include "../Input/Input.h"

const char HEART_PATH[] = {"data/play/kari_heart.png"};		//�n�[�g�̉摜�p�X
const char SHIELD_PATH[] = { "data/play/fishingpowerbar.png" };		//�V�[���h�̉摜�p�X

// �v���C���[�̉摜�T�C�Y
const int HEART_SIZE = 32; // �n�[�g

const int SHIELD_WIDTH = 32;  // �V�[���h
const int SHIELD_HEIGHT = 16;

// �v���C���[�̏����̗�
const int PLAYER_HP = 5;

// �v���C���[�̖��G����
const int PLAYER_INVINCIBLE_TIME = 120;

// �v���C���[�̏����ʒu
const float HEART_INIT_POS_X = 400.0f;
const float HEART_INIT_POS_Y = 300.0f;

class Player
{
private:
	float HeartposX, HeartposY;		// �n�[�g�̍��W
	int HeartImageHundle;		// �n�[�g�摜�n���h��
	
	float ShieldposX, ShieldposY;	// �V�[���h�̉摜�T�C�Y
	int ShieldImageHundle;		// �V�[���h�̉摜�n���h��
	float Shieldangle;			// �V�[���h�̊p�x

	int Hp;	// �v���C���[��HP
	int invincibletimeCnt; // �v���C���[�̖��G���ԃJ�E���g�p
	bool isActive; // �v���C���[�������Ă��邩
	bool isDraw; // �`�悳��邩 

	// HP�o�[�̐F�ۑ��p
	unsigned int Cr;

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
};
