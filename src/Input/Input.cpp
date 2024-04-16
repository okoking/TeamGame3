#include"DxLib.h"
#include"input.h"

//���݃t���[���̃L�[���
char Input::currentKeyBuf[KEY_BUF_LEN];
//���݃t���[���̃}�E�X���
char Input::currentMouseBuf[MOUSE_BUF_LEN];

//�O�̃t���[���̃L�[���
char Input::preKeyBuf[KEY_BUF_LEN];
//�O�̃t���[���̃L�[���
char Input::preMouseBuf[MOUSE_BUF_LEN];

//���͐��䏉����
void Input::Init()
{
	for (int index = 0; index < KEY_BUF_LEN; index++)
	{
		currentKeyBuf[index] = '\0';
		preKeyBuf[index] = '\0';
	}

	for (int index = 0; index < MOUSE_BUF_LEN; index++)
	{
		currentMouseBuf[index] = '\0';
		preMouseBuf[index] = '\0';
	}
}

//���͐���X�e�b�v
//����Step��葁���Ă�
void Input::Step()
{
	//�O�t���[���̃L�[���ϐ��ɋL�^���Ă���
	for (int index = 0; index < KEY_BUF_LEN; index++)
	{
		preKeyBuf[index] = currentKeyBuf[index];
	}

	for (int index = 0; index < MOUSE_BUF_LEN; index++)
	{
		preMouseBuf[index] = currentMouseBuf[index];
	}

	//���݂̃L�[�����擾
	GetHitKeyStateAll(currentKeyBuf);

	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
	{
		currentMouseBuf[MOUSE_INPUT_LEFT] = 1;
	}
	else
	{
		currentMouseBuf[MOUSE_INPUT_LEFT] = 0;
	}

	if ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)
	{
		currentMouseBuf[MOUSE_INPUT_RIGHT] = 1;
	}
	else
	{
		currentMouseBuf[MOUSE_INPUT_RIGHT] = 0;
	}
}

/*==========================================================
						�L�[�{�[�h
==========================================================*/

//�������ꂽ�FKEY_INPUT_�`
bool Input::Key::Push(int key_code)
{
	//�O�t���ŉ�����ĂȂ��@���@���t���ŉ�����Ă���
	if (preKeyBuf[key_code] == 0 && currentKeyBuf[key_code] == 1)
	{
		return true;
	}

	//������ĂȂ��̂� false
	return false;
}

//�����������Ă���FKEY_INPUT_�`
bool Input::Key::Keep(int key_code)
{
	//�O�t���ŉ�����Ă���@���@���t���ŉ�����Ă���
	if (preKeyBuf[key_code] == 1 && currentKeyBuf[key_code] == 1)
	{
		return true;
	}

	//������ĂȂ��̂� false
	return false;
}

//�������������ꂽ�FKEY_INPUT_�`
bool Input::Key::Release(int key_code)
{
	//�O�t���ŉ�����Ă���@���@���t���ŉ�����Ă��Ȃ�
	if (preKeyBuf[key_code] == 1 && currentKeyBuf[key_code] == 0)
	{
		return true;
	}

	//������Ă�̂� false
	return false;
}

//=========================================================================================================

//�P���ɉ�����Ă��邩�FKEY_INPUT_�`
bool Input::Key::Down(int key_code)
{
	//���t���ŉ�����Ă���i�O�t���̏�Ԃ͊֌W�Ȃ��j
	if (currentKeyBuf[key_code] == 1)
	{
		return true;
	}

	return false;
}

/*==========================================================
							�}�E�X
==========================================================*/
//�������ꂽ�FMOUSE_INPUT_LEFT or MOUSE_INPUT_RIGHT
bool Input::Mouse::Push(int key_code)
{
	//�O�t���ŉ�����ĂȂ��@���@���t���ŉ�����Ă���
	if (preMouseBuf[key_code] == 0 && currentMouseBuf[key_code] == 1)
	{
		return true;
	}

	//������ĂȂ��̂� false
	return false;
}

//�����������Ă���FMOUSE_INPUT_LEFT or MOUSE_INPUT_RIGHT
bool Input::Mouse::Keep(int key_code)
{
	//�O�t���ŉ�����Ă���@���@���t���ŉ�����Ă���
	if (preMouseBuf[key_code] == 1 && currentMouseBuf[key_code] == 1)
	{
		return true;
	}

	//������ĂȂ��̂� false
	return false;
}

//�������������ꂽ�FMOUSE_INPUT_LEFT or MOUSE_INPUT_RIGHT
bool Input::Mouse::Release(int key_code)
{
	//�O�t���ŉ�����Ă���@���@���t���ŉ�����Ă��Ȃ�
	if (preMouseBuf[key_code] == 1 && currentMouseBuf[key_code] == 0)
	{
		return true;
	}

	//������Ă�̂� false
	return false;
}
