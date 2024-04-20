#pragma once

//�摜�̎��
enum RESULT_IMAGE
{
	RESULT_BACK_GROUND,	//�w�i
	RESULT_RESULT,		//���U���g
	RESULT_SCORE,		//�X�R�A
	RESULT_PILLAR1,		//��1
	RESULT_PILLAR2,		//��2

	RESULT_IMAGE_MAX_NUM,	//�ő吔
};

//�摜�̃p�X
const char RESULT_IMAGE_PATH[RESULT_IMAGE_MAX_NUM][255] =
{
	"data/result/resultback.png",	//�w�i
	"data/result/text1.png",		//���U���g
	"data/result/text2.png",		//�X�R�A
	"data/result/resultpillar.png",	//��1
	"data/result/resultpillar.png",	//��2
};

class Result
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