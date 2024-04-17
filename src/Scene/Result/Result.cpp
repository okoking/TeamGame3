#include"DxLib.h"
#include"../Result/Result.h"
#include"../../Scene/Scene.h"
#include"../../Input/Input.h"
#include"../Play/Play.h"

//������
void Rasult::Init()
{
	for (int i = 0; i < RESULT_IMAGE_MAX_NUM; i++)
	{
		//�摜�ǂݍ���
		imageHandle[i] = LoadGraph(RESULT_IMAGE_PATH[i]);
	}
	RgearAngle = 0;

	//bgm
	Sound::Bgm::Play(BGM_RESULT);
	Sound::Bgm::SetVolume(BGM_RESULT, 50);

	//�ʏ폈���Ɉڍs
	g_CurrentSceneID = SCENE_ID_LOOP_RESULT;
}

//�ʏ폈��
void Rasult::Step()
{
	//�M�A�̉�]
	RgearAngle += 0.1f;

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
void Rasult::Draw()
{
	//�w�i�`��
	DrawGraph(0, 0, imageHandle[RESULT_BACK_GROUND], true);

	//����
	DrawRotaGraph(10, 10, 0.7, (int)RgearAngle, imageHandle[RESULT_GAER1], true);
	DrawRotaGraph(-3, 90, 0.3, (int)RgearAngle*-1, imageHandle[RESULT_GAER1], true);
	DrawRotaGraph(750, 50, 1.1, (int)RgearAngle, imageHandle[RESULT_GAER2], true);


	//�����̑傫����ύX
	SetFontSize(60);
	
	//�����̑傫����ύX
	//SetFontSize(80);
	
}

//�I������
void Rasult::Fin()
{
	//bgm
	Sound::Bgm::StopSound(BGM_RESULT);

	//�v���C��ʂֈڍs
	g_CurrentSceneID = SCENE_ID_INIT_TITLE;
}