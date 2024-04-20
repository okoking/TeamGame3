#pragma once

//�摜�̎��
enum TITLE_IMAGE_NUM
{
	TITLE_BACK,		//�w�i
	TITLE_TITLE1,	//�^�C�g��1
	TITLE_TITLE2,	//�^�C�g��2
	TITLE_START,	//�X�^�[�g
	TITLE_EASY,		//�C�[�W�[(4�~4)
	TITLE_NORMAL,	//�m�[�}��(5�~5)
	TITLE_HARD,		//�n�[�h(6�~6)
	TITLE_PILLAR1,	//��1
	TITLE_PILLAR2,	//��2
	TITLE_ARROW1,	//���1
	TITLE_ARROW2,	//���2

	TITLE_IMAGE_MAX_NUM,	//�摜��
};

//�摜�p�X
const char TITLE_IMAGE_PATH[TITLE_IMAGE_MAX_NUM][255] =
{
	"data/title/back.png",			//�w�i
	"data/title/titletext1.png",	//�^�C�g��1
	"data/title/titletext2.png",	//�^�C�g��2
	"data/title/pressenter.png",	//�X�^�[�g
	"data/title/easy.png",			//�C�[�W�[
	"data/title/normal.png",		//�m�[�}��
	"data/title/hard.png",			//�n�[�h
	"data/title/pillar.png",		//��1
	"data/title/pillar.png",		//��2
	"data/title/arrow1.png",		//���1
	"data/title/arrow2.png",		//���2
};

class Title
{
private:
	int imageHandle[TITLE_IMAGE_MAX_NUM];	//�摜�n���h��

	int fade[2];	//�����x�F�X�^�[�g ���

	bool lighting;	//���͑҂��̓_��

	int progress;	//�i�s�x

	float titlePosY[2];	//�^�C�g����Y���W

	bool isReach[2];	//���B�t���O

	int FrameCount;		//�t���[���J�E���g

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