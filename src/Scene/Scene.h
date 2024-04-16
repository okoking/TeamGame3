#pragma once
#include"../Sound/Sound.h"

// define
#define	SCREEN_SIZE_X	800	// X�����̉�ʃT�C�Y���w��
#define	SCREEN_SIZE_Y	600	// Y�����̉�ʃT�C�Y���w��

enum SCENE_ID
{
	//�^�C�g���֘A
	SCENE_ID_INIT_TITLE = 100,
	SCENE_ID_LOOP_TITLE,
	SCENE_ID_FIN_TITLE,

	//�v���C�֘A
	SCENE_ID_INIT_PLAY = 200,
	SCENE_ID_LOOP_PLAY,
	SCENE_ID_FIN_PLAY,

	//�Q�[���N���A�֘A
	SCENE_ID_INIT_RESULT = 300,
	SCENE_ID_LOOP_RESULT,
	SCENE_ID_FIN_RESULT,

};

extern SCENE_ID g_CurrentSceneID;

