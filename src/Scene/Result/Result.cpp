#include"DxLib.h"
#include"../Result/Result.h"
#include"../../Scene/Scene.h"
#include"../../Input/Input.h"


//������
void Rasult::Init()
{
	for (int i = 0; i < RESULT_IMAGE_MAX_NUM; i++)
	{
		//�摜�ǂݍ���
		imageHandle[i] = LoadGraph(RESULT_IMAGE_PATH[i]);
	}

	y = 0;
	fade[0] = 0;
	fade[1] = 0;
	lighting = false;
	progress = 1;

	//bgm
	Sound::Bgm::Play(BGM_RESULT);

	//�ʏ폈���Ɉڍs
	g_CurrentSceneID = SCENE_ID_LOOP_RESULT;
}

//�ʏ폈��
void Rasult::Step()
{
	switch (progress)
	{
	case 0:	//�X�R�A�\��

		//�X�R�A�̓����x
		if (fade[0] >= 255)
		{
			fade[0] = 255;
		}
		else
		{
			fade[0] += 2;
		}

		//�X�R�A�̍��W
		if (y >= 120)
		{
			y = 120;
		}
		else
		{
			y += 1;
		}

		//�ȏオ�w��ʂ�Ȃ�i�s
		if (fade[0] == 255 && y == 120)
		{
			progress++;
		}

		break;

	case 1:	//���͑҂�

		//�_��
		//�_��
		if (lighting)
		{
			fade[1] += 5;

			if (fade[1] >= 255)
			{
				lighting = false;
			}
		}
		//������
		else
		{
			fade[1] -= 5;

			if (fade[1] <= 0)
			{
				lighting = true;
			}
		}

		//���N���b�N�ňȉ�
		if (Input::Mouse::Push(MOUSE_INPUT_LEFT))
		{
			//se
			Sound::Se::Play(SE_SYSTEM);

			//�I��������
			g_CurrentSceneID = SCENE_ID_FIN_RESULT;
		}

		break;

		
	default:
		break;
	}
	
}

//�`��
void Rasult::Draw()
{
	//�w�i�`��
	DrawGraph(0, 0, imageHandle[RESULT_BACK_GROUND], true);

	//fade�œ����x�ύX
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fade[0]);
	//�����̑傫����ύX
	SetFontSize(60);
	DrawFormatString(300, y, GetColor(255, 255, 255), "�X�R�A");
	//�����̑傫����ύX
	SetFontSize(80);

	//�����̑傫�������ɖ߂�
	SetFontSize(20);
	//�\�������ɖ߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//fade�œ����x�ύX
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fade[1]);
	DrawGraphF(0, 0, imageHandle[RESULT_FINISH], true);	//�^�C�g��
	//�\�������ɖ߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//�I������
void Rasult::Fin()
{
	//bgm
	Sound::Bgm::StopSound(BGM_RESULT);

	//�v���C��ʂֈڍs
	g_CurrentSceneID = SCENE_ID_INIT_TITLE;
}