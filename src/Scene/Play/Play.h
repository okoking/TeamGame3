#pragma once

#include "../../Scene/Scene.h"
#include "DxLib.h"
#include "../../Player/Player.h"
#include "../../Collision/Collision.h"
#include "../../MathPlus/MathPlus.h"

class Play
{
private:
	//�N���X�̕ϐ��錾
	Player player;

	int backgroundHandle;	//�w�i�摜�n���h��
	int enemyhandle;
	int ImgHP;
	int img_sikaku;

public:
	//�v���C�V�[���̏�����
	void Init();

	//�v���C�V�[���̓ǂݍ���
	void Load();

	//�v���C�V�[���̒ʏ폈��
	void Step();

	//�v���C�V�[���̕`�揈��
	void Draw();

	//�v���C�V�[���̏I������
	void Fin();
};
