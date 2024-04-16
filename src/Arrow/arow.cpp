#include "DxLib.h"
#include "arow.h"
#include "../Collision/Collision.h"
#include "../Player/Player.h"
#include "../Scene/Scene.h"

// �R���X�g���N�^
Arrow::Arrow() 
{
	for (int ArrowIndex = 0; ArrowIndex < ARROW_MAX_NUM; ArrowIndex++) {
		for (int ArrowType = 0; ArrowType < ARROW_TYPE_NUM; ArrowType++) {
			arrowInfo[ArrowIndex].handle[ArrowType] = -1;
		}

		arrowInfo[ArrowIndex].x = 0;
		arrowInfo[ArrowIndex].y = 0;
		arrowInfo[ArrowIndex].isUse = false;

		arrowInfo[ArrowIndex].angle = ARROW_ANGLE_RIGHT;
		arrowInfo[ArrowIndex].arrowtype = ARROW_TYPE_NORMAL;
	}
}
Arrow::~Arrow() {}


// �����
void Arrow::Init()
{
	for (int  ArrowIndex = 0; ArrowIndex < ARROW_MAX_NUM; ArrowIndex++) {
		for (int ArrowType = 0; ArrowType < ARROW_TYPE_NUM; ArrowType++) {
			arrowInfo[ArrowIndex].handle[ArrowType] = 0;
		}

		arrowInfo[ArrowIndex].x = 0;
		arrowInfo[ArrowIndex].y = 0;
		arrowInfo[ArrowIndex].isUse = false;

		arrowInfo[ArrowIndex].angle = ARROW_ANGLE_RIGHT;
		arrowInfo[ArrowIndex].arrowtype = ARROW_TYPE_NORMAL;
	}
}

// �f�[�^���[�h
void Arrow::Load()
{
	for (int i = 0; i < ARROW_MAX_NUM; i++) {
		arrowInfo[i].handle[ARROW_TYPE_NORMAL] = LoadGraph("data/play/kari_arrow.png");
	}
}

// ��ˏ���
void Arrow::IsShot()
{
	for (int i = 0; i < ARROW_MAX_NUM; i++) {
		if (!arrowInfo[i].isUse) {
			// ���E�㉺����o��
			// ����W�̏����ʒu�ɐݒ�
			// ��̔��˕����ɑΉ������l������

			if (arrowInfo[i].angle == ARROW_ANGLE_RIGHT) {
				arrowInfo[i].x = 0;
				arrowInfo[i].y = HEART_INIT_POS_Y;
			}
			if (arrowInfo[i].angle == ARROW_ANGLE_DOWN) {
				arrowInfo[i].x = HEART_INIT_POS_X;
				arrowInfo[i].y = 0;
			}
			if (arrowInfo[i].angle == ARROW_ANGLE_LEFT) {
				arrowInfo[i].x = SCREEN_SIZE_X;
				arrowInfo[i].y = HEART_INIT_POS_Y;
			}
			if (arrowInfo[i].angle == ARROW_ANGLE_UP) {
				arrowInfo[i].x = HEART_INIT_POS_X;
				arrowInfo[i].y = SCREEN_SIZE_Y;
			}

			arrowInfo[i].isUse = true;
		}
	}
}

// ��̈ړ�����
void Arrow::Move()
{
	for (int i = 0; i < ARROW_MAX_NUM; i++) {
		if (arrowInfo[i].isUse) {
			// ��g�p���Ȃ�ړ�������
			// ��̔��˕����ɑΉ������l������
			if (arrowInfo[i].angle == ARROW_ANGLE_RIGHT) {
				arrowInfo[i].x += ARROW_SPEED;
			}
			if (arrowInfo[i].angle == ARROW_ANGLE_DOWN) {
				arrowInfo[i].y += ARROW_SPEED;
			}
			if (arrowInfo[i].angle == ARROW_ANGLE_LEFT) {
				arrowInfo[i].x -= ARROW_SPEED;
			}
			if (arrowInfo[i].angle == ARROW_ANGLE_UP) {
				arrowInfo[i].y -= ARROW_SPEED;
			}
		}
	}
}

// ��̒ʏ폈��
void Arrow::Step()
{
	// ��ˏ���
	IsShot();

	// ��̈ړ�����
	Move();
}

// ��̕`��
void Arrow::Draw()
{
	for (int i = 0; i < ARROW_MAX_NUM; i++) {
		if (arrowInfo[i].isUse) {
			DrawRotaGraph((int)arrowInfo[i].x, (int)arrowInfo[i].y, 1.0f, 
				arrowInfo[i].angle * 3.14 / 2, arrowInfo[i].handle[arrowInfo[i].arrowtype], true);
		}
	}
}

// ��I������
void Arrow::Fin()
{
}
