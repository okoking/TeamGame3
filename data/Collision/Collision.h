
#ifndef __COLLISION_H__
#define __COLLISION_H__

class Collision
{
public:
	//�l�p�FX,Y�͍��W�Aw�������Ah���c���A�摜��DrawGraph�ŕ\�������
	static bool Rect(int Ax, int Ay, int Aw, int Ah, int Bx, int By, int Bw, int Bh);
	static bool Rect(float Ax, float Ay, float Aw, float Ah, float Bx, float By, float Bw, float Bh);

	//�~�`�FR�����a�AX,Y�͒����A�摜��DrawRotaGraph�ŕ\�������
	static bool Circlr(int Ra, int Rb, int Xa, int Ya, int Xb, int Yb);
};

#endif
