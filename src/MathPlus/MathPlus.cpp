#include"DxLib.h"
#define _USE_MATH_DEFINES
#include<math.h>

#include"MathPlus.h"

//�Q����P�ւ̐i�s�����ƈړ��ʁF�������ꏊXY1  ��������������XY2  X��Y�̂ǂ�����o����  ������
float GetDirection(float x1, float y1, float x2, float y2, char moji,float s)
{
	float x = x1 - x2;
	float y = y1 - y2;

	float n = x * x + y * y;

	n = sqrtf(n);

	if (moji == 'x')
	{
		return x / n * s;
	}
	else if (moji == 'y')
	{
		return y / n * s;
	}
	return 0;
}

//2�_�Ԃ̋����F�J�n�n�_XY�@�I���n�_XY
float GetDistance(float startX, float startY, float endX, float endY)
{
	float num = 0.0f;
	num = ((startX - endX) * (startX - endX)) + ((startY - endY) * (startY - endY));
	num = sqrtf(num);

	return num;
}

//1����2�ւ̊p�x(���W�A��)�F�J�n�n�_XY�@�I���n�_XY
float GetAngle(float Ax, float Ay, float Bx, float By)
{
	float num = 0.0f;
	num=atan2f(Ay - By, Ax - Bx);

	return num;
}

//�x�N�g���̓��ς����߂Đ�������Ԃ��F��������ꏊXY�@��������������XY
bool GetInnerProduct(float Ax, float Ay, float Bx, float By)
{
	float num = 0.0f;

	num = Ax * Bx + Ay * By;
	if (num > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//�x�����W�A���ɕϊ��i�����F�x�j
float DegToRad(float degree)
{
	return degree * (float)M_PI / 180.0f;
}