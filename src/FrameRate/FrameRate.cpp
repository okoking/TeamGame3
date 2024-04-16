#include"DxLib.h"
#include"FrameRate.h"
#include"../Scene/Scene.h"

//�t���[�����[�g���
struct FrameRateInfo
{
	int currentTime;		//���݂̎���
	int lastFrameTime;		//�O��̃t���[�����s���̎���
	int count;				//�t���[���J�E���g�p
	int calcFpsTime;		//FPS���v�Z��������
	float fps;				//�v������FPS�i�\���p�j
};

//�t���[�����[�g���ϐ�
FrameRateInfo frameRateInfo;

//���⋭��FPS�֐�
bool FPS()
{
	Sleep(1);	//�V�X�e���ɏ�����Ԃ�

	//���݂̎��Ԃ��擾
	frameRateInfo.currentTime = GetNowCount();

	//�ŏ��̃��[�v�Ȃ�
	//���݂̎��Ԃ��AFPS�̌v�Z�������Ԃɐݒ�
	if (frameRateInfo.calcFpsTime == 0.0f)
	{
		frameRateInfo.calcFpsTime = frameRateInfo.currentTime;
		frameRateInfo.fps = (float)FRAME_RATE;
	}

	//���݂̎��Ԃ��A�O��̃t���[�������
	//1000/60�~���b�i1/60�b�j�ȏ�o�߂��Ă����珈�������s����
	if (frameRateInfo.currentTime - frameRateInfo.lastFrameTime >= FRAME_TIME)
	{
		//�t���[�����s���̎��Ԃ��X�V
		frameRateInfo.lastFrameTime = frameRateInfo.currentTime;

		//�t���[�������J�E���g
		frameRateInfo.count++;

		return true;
	}
	return false;
}

//FPS�v�Z
void CalcFPS()
{
	//�O���FPS���v�Z�������Ԃ���o�ߎ��Ԃ����߂�
	int difTime = frameRateInfo.currentTime - frameRateInfo.calcFpsTime;

	//�O���FPS���v�Z�������Ԃ���
	//1�b�ȏ�o�߂��Ă�����FPS���v�Z����
	if (difTime > 1000)
	{
		//�t���[���񐔂��~���b�ɍ��킹��
		//�����܂ŏo�������̂�float�ɃL���X�g
		float frameCount = (float)(frameRateInfo.count * 1000.0f);

		//FPS�����߂�
		//���z�̐��l�� 60000 / 1000 �� 60 �ƂȂ�
		frameRateInfo.fps = frameCount / difTime;

		//�t���[�����[�g�J�E���g���N���A
		frameRateInfo.count = 0;

		//FPS���v�Z�������Ԃ��X�V
		frameRateInfo.calcFpsTime = frameRateInfo.currentTime;
	}
}

//FPS�\���i�f�o�b�N�p�j
void DrawFPS()
{
	SetFontSize(20);
	unsigned int color = GetColor(255, 30, 30);
	DrawFormatString(SCREEN_SIZE_X -120, SCREEN_SIZE_Y -20, color, "FPS[%.2f]", frameRateInfo.fps);
}