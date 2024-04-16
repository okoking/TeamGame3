#pragma once

//�摜�̎��
enum RESULT_IMAGE
{
	RESULT_BACK_GROUND,	//�w�i
	RESULT_FINISH,	//����

	RESULT_IMAGE_MAX_NUM,	//�ő吔
};

//�摜�̃p�X
const char RESULT_IMAGE_PATH[RESULT_IMAGE_MAX_NUM][255] =
{
	"data/result/backGround.png",	//�w�i
	"data/result/finish.png",	//����
};

class Rasult
{
private:
	int imageHandle[RESULT_IMAGE_MAX_NUM];	//�摜�n���h��
	int fade[2];	//�����x

	int y;	//�X�R�A�̍��W

	bool lighting;	//���͑҂��̓_��

	int progress;	//�i�s�x

public:
	//������
	void Init();

	//�ʏ폈��
	void Step();

	//�`�揈��
	void Draw();

	//�I������
	void Fin();
};