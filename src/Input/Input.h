#pragma once

#define KEY_BUF_LEN		256
#define MOUSE_BUF_LEN	3

class Input
{
private:
	//���݃t���[���̃L�[���
	static char currentKeyBuf[KEY_BUF_LEN];
	//���݃t���[���̃}�E�X���
	static char currentMouseBuf[MOUSE_BUF_LEN];


	//�O�̃t���[���̃L�[���
	static char preKeyBuf[KEY_BUF_LEN];
	//�O�̃t���[���̃L�[���
	static char preMouseBuf[MOUSE_BUF_LEN];

public:
	//���͐��䏉����
	static void Init();

	//���͐���X�e�b�v
	//����Step��葁���Ă�
	static void Step();

	/*==========================================================
							�L�[�{�[�h
	==========================================================*/
	class Key
	{
	public:
		//�������ꂽ�FKEY_INPUT_�`
		static bool Push(int key_code);

		//�����������Ă���FKEY_INPUT_�`
		static bool Keep(int key_code);

		//�������������ꂽ�FKEY_INPUT_�`
		static bool Release(int key_code);

		//=======================================

		//�P���ɉ�����Ă��邩�FKEY_INPUT_�`
		static bool Down(int key_code);
	};

	/*==========================================================
								�}�E�X
	==========================================================*/
	class Mouse
	{
	public:
		//�������ꂽ�FMOUSE_INPUT_LEFT or MOUSE_INPUT_RIGHT
		static bool Push(int key_code);

		//�����������Ă���FMOUSE_INPUT_LEFT or MOUSE_INPUT_RIGHT
		static bool Keep(int key_code);

		//�������������ꂽ�FMOUSE_INPUT_LEFT or MOUSE_INPUT_RIGHT
		static bool Release(int key_code);
	};
};