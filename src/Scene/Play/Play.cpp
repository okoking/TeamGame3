#include "Play.h"
#include "../../FrameRate/FrameRate.h"

//�摜�p�X
const char BACKGROUND_PATH[] = { "data/play/backGround.png" };		//�v���C�V�[���̔w�i�摜�̃p�X

//�v���C�V�[���̏�����
void Play::Init()
{
	//�v���C���[�֘A
	player.Init();

	// ��
	arrow.Init();

	//�v���C�V�[���̒ʏ폈���ɑJ��
	g_CurrentSceneID = SCENE_ID_LOOP_PLAY;
}

//�v���C�V�[���̓ǂݍ���
void Play::Load()
{
	//�摜�ǂݍ���
	//�w�i�֘A
	backgroundHandle = LoadGraph(BACKGROUND_PATH);	//�w�i
	
	//�v���C���[�֘A
	player.Load();									//�v���C���[�摜�̓ǂݍ���

	// ��
	arrow.Load();

}

//�v���C�V�[���̒ʏ폈��
void Play::Step()
{
	player.Step();			//�v���C���[�̒ʏ폈��

	arrow.Step();			// ��̒ʏ폈��
}

//�v���C�V�[���̕`�揈��
void Play::Draw()
{
	//�w�i�`��
	//DrawGraph(0, 0, backgroundHandle, true);	//�w�i

	player.Draw();		//�v���C���[�摜�̕`��
	arrow.Draw();		//��̕`��

	//�����̑傫����ύX
	SetFontSize(20);
	//�������������
	DrawFormatString(20, 465, GetColor(255, 255, 255), "��������ɏ���������");
	//�����̑傫�������ɖ߂�
	SetFontSize(20);
}

//�v���C���[�V�[���̏I������
void Play::Fin()
{
	player.Fin();		//�v���C���[�̏I������
	arrow.Fin();		//��I������
	//gem
	Sound::Bgm::StopSound(BGM_PLAY);
	Sound::Bgm::StopSound(BGM_SEA);

	Sound::Bgm::StopSound(BGM_FISH);
	Sound::Bgm::StopSound(BGM_FISHING);
	Sound::Bgm::StopSound(BGM_RECOVERY);


	g_CurrentSceneID = SCENE_ID_INIT_RESULT;
}
