#include"DxLib.h"
#include"../Result/Result.h"
#include"../../Scene/Scene.h"
#include"../../Input/Input.h"
#include"../Play/Play.h"

//������
void Result::Init()
{
	for (int i = 0; i < RESULT_IMAGE_MAX_NUM; i++)
	{
		//�摜�ǂݍ���
		imageHandle[i] = LoadGraph(RESULT_IMAGE_PATH[i]);
	}

	//bgm
	Sound::Bgm::Play(BGM_RESULT);
	Sound::Bgm::SetVolume(BGM_RESULT, 40);

	//�ʏ폈���Ɉڍs
	g_CurrentSceneID = SCENE_ID_LOOP_RESULT;
}

//�ʏ폈��
void Result::Step()
{
	//���N���b�N�ňȉ�
	if (Input::Key::Push(KEY_INPUT_SPACE))
	{
		//se
		Sound::Se::Play(SE_SYSTEM);

		//�I��������
		g_CurrentSceneID = SCENE_ID_FIN_RESULT;
	}
	
}

//�`��
void Result::Draw()
{
	//�w�i�`��
	DrawGraph(0, 0, imageHandle[RESULT_BACK_GROUND], true);

	//���U���g
	DrawRotaGraph(640, 75, 1.0f, 0.0f, imageHandle[RESULT_RESULT], true);

	//�X�R�A
	DrawRotaGraph(640, 200, 1.0f, 0.0f, imageHandle[RESULT_SCORE], true);

	//��
	DrawGraph(0, 0, imageHandle[RESULT_PILLAR1], true);
	DrawGraph(980, 0, imageHandle[RESULT_PILLAR1], true);


	//�����̑傫����ύX
	SetFontSize(60);
	
	//�����̑傫����ύX
	//SetFontSize(80);
	
}

//�I������
void Result::Fin()
{
	//bgm
	Sound::Bgm::StopSound(BGM_RESULT);

	//�v���C��ʂֈڍs
	g_CurrentSceneID = SCENE_ID_INIT_TITLE;
}