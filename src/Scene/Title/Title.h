#pragma once

//�摜�̎��
enum TITLE_IMAGE_NUM
{
	
	TITLE_TITLE,	//�^�C�g��
	TITLE_START,	//���͑҂�
	TITLE_GEAR1,	//����
	TITLE_GEAR2,
	TITLE_GEAR3,
	TITLE_GEARHARF,
	TITLE_LINE,		//��
	TITLE_EASY,		//easy
	TITLE_NORMAL,	//normal
	TITLE_HARD,		//hard
	TITLE_ARROW,	//��Փx�I��p�₶�邵
	TITLE_ARROW2,	//��Փx�I��p�₶�邵

	TITLE_IMAGE_MAX_NUM,	//�摜��
};

//�摜�p�X
const char TITLE_IMAGE_PATH[TITLE_IMAGE_MAX_NUM][255] =
{
	"data/title/title2.png",	//�^�C�g��
	"data/title/push.png",	//���͑҂�
	"data/title/gear1.png",	//����1
	"data/title/gear2.png",	//����2
	"data/title/gear3.png",	//����3
	"data/title/gear2herf .png",	//����3
	"data/title/sen.png",	//��
	
	"data/title/easy.png",	//easy
	"data/title/normal.png",//normal
	"data/title/hard.png",	//hard 
	"data/title/sankaku.png",//�O�p
	"data/title/sankaku02.png",//�O�p


	//"data/title/start.png",	//���͑҂�
};

class Title
{
private:
	int imageHandle[TITLE_IMAGE_MAX_NUM];	//�摜�n���h��

	
	int fade[2];	//�����x�F�^�C�g�� ���͑҂�

	bool lighting;	//���͑҂��̓_��

	int progress;	//�i�s�x

	float gearAngle;	//���Ԃ̉�]
	float lineX;		//�^�C�g�����̐�
	float lineY;		//�^�C�g�����̐�
	float lineW;		//�^�C�g�����̐�
	float lineH;		//�^�C�g�����̐�

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