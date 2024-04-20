//�E�B���h�E��\������v���O�����i�ЂȌ`�j

#include "DxLib.h"					//DX���C�u�����̃C���N���[�h
#include "FrameRate/FrameRate.h"	//�t���[�����[�g
#include "Input/Input.h"			//���͋@�\
#include "Scene/Scene.h"			//�V�[���֘A
#include "Scene/Title/Title.h"		//�^�C�g��
#include "Scene/Play/Play.h"		//�v���C
#include "Scene/Result/Result.h"	//���U���g

// Win32�A�v���P�[�V������ WinMain�֐� ����n�܂�
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	//�E�B���h�E�̖��O��ς���
	SetMainWindowText("�p�l���p�Y��");

	//�E�B���h�E�̏�Ԃ�ݒ肷��
	ChangeWindowMode(true);

	// ��ʃT�C�Y��ύX
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);

	//DX���C�u�����̏�����
	if (DxLib_Init() == -1) 
	{
		return -1;
	}

	//�`�悷��X�N���[����ݒ肷��
	SetDrawScreen(DX_SCREEN_BACK);

	//-----------------------------------------
	//��ԍŏ��ɂP�񂾂���鏈���������ɏ���
	g_CurrentSceneID = SCENE_ID_INIT_TITLE;		//�V�[��ID

	//�V�[���N���X�錾
	Title title{};			//�^�C�g���V�[��
	Play play{};			//�v���C�V�[��
	Result result{};		//���U���g�V�[��

	//���͐��䏉����
	Input::Init();

	//�T�E���h������
	Sound::Init();

	//-----------------------------------------
	//�Q�[�����C�����[�v
	while (ProcessMessage() != -1)
	{
		//�t���[�����[�g�Ǘ�
		if (FPS())
		{
			if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
			{
				//�G�X�P�[�v�L�[�������ꂽ��I��
				break;
			}

			//��ʂɕ\�����ꂽ���̂�������
			ClearDrawScreen();

			//���͏����ʏ폈��
			Input::Step();

			//-----------------------------------------
			//��������Q�[���̖{�̂��������ƂɂȂ�
			//-----------------------------------------

			//�ΎR
			//�V�[���J��
			switch (g_CurrentSceneID)
			{
				//�^�C�g���V�[��������
			case SCENE_ID_INIT_TITLE:

				//������
				title.Init();

				break;

				//�^�C�g���V�[���ʏ폈��
			case SCENE_ID_LOOP_TITLE:

				//�ʏ폈��
				title.Step();

				//�`��
				title.Draw();

				break;

				//�^�C�g���V�[���I������
			case SCENE_ID_FIN_TITLE:

				//�I������
				title.Fin();

				break;


				//�v���C�V�[��������
			case SCENE_ID_INIT_PLAY:

				play.Init();	//�v���C�V�[��������

				play.Load();	//�v���C�V�[���̓ǂݍ���

				break;
				//�v���C�V�[���ʏ폈��
			case SCENE_ID_LOOP_PLAY:

				play.Step();	//�v���C�V�[���̒ʏ폈��

				play.Draw();	//�v���C�V�[���̕`�揈��

				break;
				//�v���C�V�[���I������
			case SCENE_ID_FIN_PLAY:

				play.Fin();		//�v���C�V�[���̏I������

				break;


				//���U���g�V�[������������
			case SCENE_ID_INIT_RESULT:

				result.Init();

				break;
				//���U���g�V�[���ʏ폈��
			case SCENE_ID_LOOP_RESULT:

				result.Step();
				result.Draw();

				break;
				//���U���g�V�[���I������
			case SCENE_ID_FIN_RESULT:

				result.Fin();

				break;
			}


			//-----------------------------------------
			//���[�v�̏I����

			//FPS�v�Z
			CalcFPS();

			//FPS�\���i�f�o�b�N�p�j
			DrawFPS();

			//�t���b�v�֐�
			ScreenFlip();
		}
	}

	//-----------------------------------------
	//�Ō�ɂP�񂾂���鏈���������ɏ���


	//-----------------------------------------
	//DX���C�u�����̌㏈��
	DxLib_End();

	return 0;
}

