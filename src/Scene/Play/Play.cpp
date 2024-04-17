#include "Play.h"
#include "../../FrameRate/FrameRate.h"

//�摜�p�X
const char BACKGROUND_PATH[] = { "data/play/backGround.png" };		//�v���C�V�[���̔w�i�摜�̃p�X
const char ENEMY_PATH[] = { "data/play/move1.png" };				//�v���C�V�[���̔w�i�摜�̃p�X

//�v���C�V�[���̏�����
void Play::Init()
{
	//�v���C���[�֘A
	player.Init();

	//��
	Sound::Bgm::Play(BGM_PLAY);
	Sound::Bgm::SetVolume(BGM_PLAY, 50);

	//�v���C�V�[���̒ʏ폈���ɑJ��
	g_CurrentSceneID = SCENE_ID_LOOP_PLAY;
}

//�v���C�V�[���̓ǂݍ���
void Play::Load()
{
	//�摜�ǂݍ���
	//�w�i�֘A
	backgroundHandle = LoadGraph(BACKGROUND_PATH);	//�w�i
	enemyhandle = LoadGraph(ENEMY_PATH);	//�G
	ImgHP = LoadGraph("data/play/HP.png");
	img_sikaku = LoadGraph("data/play/sikaku.png");
	//�v���C���[�֘A
	player.Load();									//�v���C���[�摜�̓ǂݍ���
}

//�v���C�V�[���̒ʏ폈��
void Play::Step()
{
	player.Step();			//�v���C���[�̒ʏ폈��
}

//�v���C�V�[���̕`�揈��
void Play::Draw()
{
	//�G500 0
	DrawGraph(500, 0,enemyhandle, true);
	//DrawRotaGraph(400, 300,1.0f,0.0f, enemyhandle, true);

	DrawLineBox(HEART_INIT_POS_X - HEART_INIT_POS_Y, 0, HEART_INIT_POS_X + HEART_INIT_POS_Y, HEART_INIT_POS_Y + HEART_INIT_POS_Y,
		GetColor(255, 255, 255));

	player.Draw();		//�v���C���[�摜�̕`��

	//�����̑傫����ύX
	SetFontSize(20);
	//�������������
	DrawFormatString(20, 100, GetColor(255, 255, 255), "��������ɏ���������");
	DrawFormatString(20, 120, GetColor(255, 255, 255), "�Ԃ���͖h����");
	DrawFormatString(20, 140, GetColor(255, 255, 255), "��͕��͋C�łȂ�Ƃ�����");
	DrawFormatString(500, 40, GetColor(255, 255, 255), "�K�[�h������:%d",player.GetGuradCnt());
	
	DrawRotaGraph(400, 300, 1.0f, 0.0f, img_sikaku, true);
	
	//�����̑傫�������ɖ߂�
	SetFontSize(20);
}

//�v���C���[�V�[���̏I������
void Play::Fin()
{
	player.Fin();		//�v���C���[�̏I������
	DeleteGraph(enemyhandle);	// �G�摜����
	//gem
	Sound::Bgm::StopSound(BGM_PLAY);	

	g_CurrentSceneID = SCENE_ID_INIT_RESULT;
}

