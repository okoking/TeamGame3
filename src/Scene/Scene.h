#pragma once
#include"../Sound/Sound.h"

// define
#define	SCREEN_SIZE_X	1280	// X方向の画面サイズを指定
#define	SCREEN_SIZE_Y	720		// Y方向の画面サイズを指定

enum SCENE_ID
{
	//タイトル関連
	SCENE_ID_INIT_TITLE = 100,
	SCENE_ID_LOOP_TITLE,
	SCENE_ID_FIN_TITLE,

	//プレイ関連
	SCENE_ID_INIT_PLAY = 200,
	SCENE_ID_LOOP_PLAY,
	SCENE_ID_FIN_PLAY,

	//ゲームクリア関連
	SCENE_ID_INIT_RESULT = 300,
	SCENE_ID_LOOP_RESULT,
	SCENE_ID_FIN_RESULT,

};

// 問題の難易度
enum QUESTION_LEVEL
{
	QUESTION_LEVEL_44 = 0,	// 4×4マス
	QUESTION_LEVEL_55,		// 5×5マス
	QUESTION_LEVEL_66,		// 6×6マス

	QUESTION_LEVEL_NUM,
};

// 問題の種類
enum QUESTION_TYPE
{
	QUESTION_TYPE_1 = 0,
	QUESTION_TYPE_2,

	QUESTION_TYPE_NUM,
};

extern SCENE_ID g_CurrentSceneID;
extern QUESTION_LEVEL g_QuestonLevelID;
extern QUESTION_TYPE g_QuestonTypeID;
