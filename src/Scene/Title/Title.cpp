#include"DxLib.h"
#include"../Title/Title.h"
#include"../../Scene/Scene.h"
#include"../../Input/Input.h"
#include"../../FrameRate/FrameRate.h"

SCENE_ID g_CurrentSceneID;	//�V�[���ϐ�

//�Q�[�����[�h
QUESTION_LEVEL g_QuestonLevelID;

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

	//���ߓ_��
	fade[0] = 0;
	fade[1] = 0;

	//�^�C�g���̏���Y���W��ݒ�
	for (int i = 0; i < 2; i++)
	{
		titlePosY[i] = -150.0f;
		//���B�t���O��܂�
		isReach[i] = false;
	}

	FrameCount = 0;

	//�ʏ폈���Ɉڍs
	g_CurrentSceneID = SCENE_ID_LOOP_TITLE;

	//�Q�[�����[�h��������
	g_QuestonLevelID = QUESTION_LEVEL_44;
}

//�ʏ폈��
void Title::Step()
{
	//���B�t���O��false�Ȃ�
	if (!isReach[0])
	{
		titlePosY[0]++;

		if (titlePosY[0] >= 75.0f)
		{
			titlePosY[0] = 75.0f;
			isReach[0] = true;
		}
	}

	else if (isReach[0] && !isReach[1])
	{
		titlePosY[1] += 2.0f;

		if (titlePosY[1] >= 200.0f)
		{
			titlePosY[1] = 200.0f;

			FrameCount++;
			{
				if (FrameCount >= FRAME_RATE)
				{
					FrameCount = 0;
					isReach[1] = true;
				}
			}
		}
	}

	if (isReach[1])
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
		//�G���^�[�L�[�ŉ�ʕω�
		if (Input::Key::Push(KEY_INPUT_RETURN))
		{
			// ���Ƃ��ďI��������==================
			g_CurrentSceneID = SCENE_ID_FIN_TITLE;
			//=====================================
			
			//se
			Sound::Se::Play(SE_SYSTEM);

			//�I��������
			g_CurrentSceneID = SCENE_ID_FIN_TITLE;
		}

		//���L�[�ŏ�ԕω�
		if (g_QuestonLevelID != QUESTION_LEVEL_44) {
			if (Input::Key::Push(KEY_INPUT_LEFT))
			{
				//se
				Sound::Se::Play(SE_SYSTEM);
				if (g_QuestonLevelID == QUESTION_LEVEL_66)
					g_QuestonLevelID = QUESTION_LEVEL_55;
				else
					g_QuestonLevelID = QUESTION_LEVEL_44;
			}
		}
		if (g_QuestonLevelID != QUESTION_LEVEL_66) {
			if (Input::Key::Push(KEY_INPUT_RIGHT))
			{
				//se
				Sound::Se::Play(SE_SYSTEM);
				if (g_QuestonLevelID == QUESTION_LEVEL_44)
					g_QuestonLevelID = QUESTION_LEVEL_55;
				else
					g_QuestonLevelID = QUESTION_LEVEL_66;
			}
		}
	}
}


void Title::Draw()//1280 720
{
	//�w�i
	DrawGraph(0, 0, imageHandle[TITLE_BACK], true);

	//�^�C�g��
	DrawRotaGraph(640, (int)titlePosY[0], 0.75f, 0.0f, imageHandle[TITLE_TITLE1], true);
	DrawRotaGraph(640, (int)titlePosY[1], 0.75f, 0.0f, imageHandle[TITLE_TITLE2], true);

	if (isReach[1])
	{
		//��Փx
		DrawRotaGraph(640, 360, 0.75f, 0.0f, imageHandle[TITLE_EASY + g_QuestonLevelID], true);
	}

	//��
	DrawGraph(0, 0, imageHandle[TITLE_PILLAR1], true);
	DrawGraph(980, 0, imageHandle[TITLE_PILLAR2], true);

	if (isReach[1])
	{
		//���
		if (g_QuestonLevelID != QUESTION_LEVEL_55) {
			//fade�œ����x�ύX
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, fade[1]);
			DrawRotaGraph(500, 360, 0.75f, 0.0f, imageHandle[TITLE_ARROW2], true);
			DrawRotaGraph(778, 360, 0.75f, 0.0f, imageHandle[TITLE_ARROW1], true);
			//�\�������ɖ߂�
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		}
		else {
			//fade�œ����x�ύX
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, fade[1]);
			DrawRotaGraph(500, 360, 0.75f, 0.0f, imageHandle[TITLE_ARROW2], true);
			DrawRotaGraph(778, 360, 0.75f, 0.0f, imageHandle[TITLE_ARROW1], true);
			//�\�������ɖ߂�
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		}

		//fade�œ����x�ύX
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, fade[0]);
		DrawRotaGraph(640, 600, 0.75f, 0.0f, imageHandle[TITLE_START], true);	//���͑҂�
		//�\�������ɖ߂�
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	}
}

//�I������
void Title::Fin()
{
	//bgm
	Sound::Bgm::StopSound(BGM_TITLE);
	
	//�v���C��ʂֈڍs
	g_CurrentSceneID = SCENE_ID_INIT_PLAY;
}