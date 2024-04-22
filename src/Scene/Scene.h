#pragma once
#include"../Sound/Sound.h"

// define
#define	SCREEN_SIZE_X	1280	// X�����̉�ʃT�C�Y���w��
#define	SCREEN_SIZE_Y	720		// Y�����̉�ʃT�C�Y���w��

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

// ���̓�Փx
enum QUESTION_LEVEL
{
	QUESTION_LEVEL_44 = 0,	// 4�~4�}�X
	QUESTION_LEVEL_55,		// 5�~5�}�X
	QUESTION_LEVEL_66,		// 6�~6�}�X

	QUESTION_LEVEL_NUM,
};

// ���̎��
enum QUESTION_TYPE
{
	QUESTION_TYPE_1 = 0,
	QUESTION_TYPE_2,

	QUESTION_TYPE_NUM,
};

extern SCENE_ID g_CurrentSceneID;
extern QUESTION_LEVEL g_QuestonLevelID;
extern QUESTION_TYPE g_QuestonTypeID;
