#pragma once

//�ݒ�t���[�����[�g�i60FPS�j
#define FRAME_RATE	(60)

//1�t���[���̎��ԁi�~���b�j
#define FRAME_TIME	(1000/FRAME_RATE)

//����FPS�֐�
bool FPS();

//FPS�v�Z
void CalcFPS();

//FPS�\���i�f�o�b�N�p�j
void DrawFPS();