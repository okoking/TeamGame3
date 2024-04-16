#pragma once

//�摜�̎��
enum TITLE_IMAGE_NUM
{
	TITLE_SKY,	//��
	TITLE_SEA,	//�C
	TITLE_JETTY,	//�V��
	TITLE_CLOUD1,	//�_1
	TITLE_CLOUD2,	//�_2
	TITLE_CLOUD3,	//�_3
	TITLE_CLOUD4,	//�_4
	TITLE_TITLE,	//�^�C�g��
	TITLE_START,	//���͑҂�

	TITLE_IMAGE_MAX_NUM,	//�摜��
};

//�摜�p�X
const char TITLE_IMAGE_PATH[TITLE_IMAGE_MAX_NUM][255] =
{
	"data/title/sky.png",	//��
	"data/title/sea.png",	//�C
	"data/title/jetty.png",	//�V��
	"data/title/cloud1.png",	//�_1
	"data/title/cloud2.png",	//�_2
	"data/title/cloud3.png",	//�_3
	"data/title/cloud4.png",	//�_4
	"data/title/title.png",	//�^�C�g��
	"data/title/start.png",	//���͑҂�
};

class Title
{
private:
	int imageHandle[TITLE_IMAGE_MAX_NUM];	//�摜�n���h��

	float seaY;	//�C�x
	float jettyY;	//�V���x
	float cloudX[4][2];	//�_�w
	float cloudY;	//�_�w
	float titleY;	//�^�C�g���x

	int fade[2];	//�����x�F�^�C�g�� ���͑҂�

	bool lighting;	//���͑҂��̓_��

	int progress;	//�i�s�x

public:

	//������
	void Init();

	//�ʏ폈��
	void Step();

	//�`��
	void Draw();

	//�I������
	void Fin();

};