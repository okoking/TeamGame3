#include "Collision.h"

//IsHitRect�̒�`�i�l�p�j
bool Collision::Rect(int Ax, int Ay, int Aw, int Ah, int Bx, int By, int Bw, int Bh)		//X,Y�͍��W�Aw�������Ah���c���A�摜��DrawGraph�ŕ\�������
{
	if (Bx< Ax + Aw &&
		Bx + Bw>Ax &&
		By + Bh > Ay &&
		By < Ay + Ah)
	{
		return true;
	}
	return false;
}

bool Collision::Rect(float Ax, float Ay, float Aw, float Ah, float Bx, float By, float Bw, float Bh)
{
	if (Bx< Ax + Aw &&
		Bx + Bw>Ax &&
		By + Bh > Ay &&
		By < Ay + Ah)
	{
		return true;
	}
	return false;
}

//IsHitCircle�̒�`�i�~�`�j
bool Collision::Circlr(int Ra, int Rb, int Xa, int Ya, int Xb, int Yb)					//R�����a�AX,Y�͒����A�摜��DrawRotaGraph�ŕ\�������
{
	if ((Ra + Rb) * (Ra + Rb) > (Xa - Xb) * (Xa - Xb) + (Ya - Yb) * (Ya - Yb))
	{
		return true;
	}
	return false;
}
