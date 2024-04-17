#include"DxLib.h"
#include"../Title/Title.h"
#include"../../Scene/Scene.h"
#include"../../Input/Input.h"
#include"../../FrameRate/FrameRate.h"

SCENE_ID g_CurrentSceneID;	//�V�[���ϐ�

//�Q�[�����[�h
GAME_MODE g_GameModeID;

//������
void Title::Init()
{
	//�摜�ǂݍ���
	for (int i = 0; i < TITLE_IMAGE_MAX_NUM; i++)
	{
		imageHandle[i] = LoadGraph(TITLE_IMAGE_PATH[i]);
	}

	//bgm
	Sound::Bgm::Play(BGM_TITLE);
	Sound::Bgm::SetVolume(BGM_TITLE,50);
	//���ԉ�]
	gearAngle = 0.0f;

	//���ߓ_��
	fade[0] = 0;
	fade[1] = 0;

	//�ʏ폈���Ɉڍs
	g_CurrentSceneID = SCENE_ID_LOOP_TITLE;

	//�Q�[�����[�h��������
	g_GameModeID = GAME_MODE_EASY;
}

//�ʏ폈��
void Title::Step()
{
	//�����
	if (lighting)
	{
		fade[0] += 4;
		fade[1] += 7;

		if (fade[0] >= 255)
		{
			lighting = false;
		}
		if (fade[1] >= 255)
		{
			lighting = false;
		}
	}
	//������
	else
	{
		fade[0] -= 4;
		fade[1] -= 7;

		if (fade[0] <= 0)
		{
			lighting = true;
		}
		if (fade[1] <= 0)
		{
			lighting = true;
		}
	}

	gearAngle+=0.1f;
		

	//�X�y�[�X�L�[�ŉ�ʕω�
	if (Input::Key::Push(KEY_INPUT_SPACE))
	{
		//se
		Sound::Se::Play(SE_SYSTEM);

		//�I��������
		g_CurrentSceneID = SCENE_ID_FIN_TITLE;
	}

	//���L�[�ŏ�ԕω�
	if (g_GameModeID != GAME_MODE_EASY) {
		if (Input::Key::Push(KEY_INPUT_LEFT))
		{
			//se
			Sound::Se::Play(SE_SYSTEM);
			if(g_GameModeID== GAME_MODE_HARD)
				g_GameModeID= GAME_MODE_NORMAL;
			else
				g_GameModeID = GAME_MODE_EASY;
		}
	}
	if (g_GameModeID != GAME_MODE_HARD) {
		if (Input::Key::Push(KEY_INPUT_RIGHT))
		{
			//se
			Sound::Se::Play(SE_SYSTEM);
			if (g_GameModeID == GAME_MODE_EASY)
				g_GameModeID = GAME_MODE_NORMAL;
			else
				g_GameModeID = GAME_MODE_HARD;
		}
	}
	
}


void Title::Draw()//800 600
{	
	//�^�C�g�����n
	DrawGraph(0, 0, imageHandle[TITLE_TITLE], true);	

	//����
	DrawRotaGraph(15, 30,1.0f, (int)gearAngle, imageHandle[TITLE_GEAR1], true);

	//����
	DrawRotaGraph(0, 450,0.5, (int)gearAngle*-1+0.4, imageHandle[TITLE_GEAR2], true);	
	DrawRotaGraph(34, 552, 0.5, (int)gearAngle*-1+0.1, imageHandle[TITLE_GEAR2], true);
	DrawRotaGraph(92, 479, 0.5, (int)gearAngle, imageHandle[TITLE_GEAR2], true);

	//�E��
	DrawRotaGraph(760, 460,1.0f, (int)gearAngle*-1+0.5, imageHandle[TITLE_GEAR3], true);	
	DrawRotaGraph(663, 576,1.0f, (int)gearAngle, imageHandle[TITLE_GEAR3], true);	

	DrawRotaGraph(400, 440, 1.0f, 0.0f, imageHandle[TITLE_EASY+g_GameModeID], true);

	//�^�C�g�����̐� ���W�A������W�A�`�悷��T�C�Y�A�n���h���A�������A�摜���]�L��  421 43
	DrawGraph(210, 310, imageHandle[TITLE_LINE], true);
	//DrawRotaGraph(400, 380, 1.0f,0.0f,imageHandle[TITLE_GEARHARF], true);

	//���
	if (g_GameModeID != GAME_MODE_NORMAL) {
		//fade�œ����x�ύX
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, fade[1]);
		DrawRotaGraph(250, 440, 0.5, 0, imageHandle[TITLE_ARROW2], true);
		DrawRotaGraph(540, 440, 0.5, 0.0f, imageHandle[TITLE_ARROW], true);
		//�\�������ɖ߂�
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	}
	else {
		//fade�œ����x�ύX
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, fade[1]);
		DrawRotaGraph(200, 440, 0.5, 0, imageHandle[TITLE_ARROW2], true);
		DrawRotaGraph(590, 440, 0.5, 0.0f, imageHandle[TITLE_ARROW], true);
		//�\�������ɖ߂�
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	}

	//fade�œ����x�ύX
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fade[0]);
	DrawGraphF(300, 370, imageHandle[TITLE_START], true);	//���͑҂�
	//�\�������ɖ߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

//�I������
void Title::Fin()
{
	//bgm
	Sound::Bgm::StopSound(BGM_TITLE);
	
	//�v���C��ʂֈڍs
	g_CurrentSceneID = SCENE_ID_INIT_PLAY;
}