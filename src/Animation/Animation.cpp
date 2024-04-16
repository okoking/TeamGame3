#include<DxLib.h>
#include"Animation.h"

//�A�j�����
AnimeClass animeInfo[ANIME_TYPE_NUM];

//==============================================================================================

//�t�@�C���p�X
const char animeFilePath[ANIME_TYPE_NUM][256] =
{
	"",	//
};

//�A�j����
const int animeImgNum[ANIME_TYPE_NUM] =
{
	0,	//
};

//�摜������ [0] = x, [1] = y
const int animeImageSplitNum[ANIME_TYPE_NUM][2] =
{
	{0,0},	//
};

//�摜�T�C�Y [0] = x, [1] = y
const int animeImageSize[ANIME_TYPE_NUM][2] =
{
	{0,0},	//
};

//�A�j���摜�؂�ւ�����
const float animwChageTime[ANIME_TYPE_NUM] =
{
	0.1f,	//
};

//�Đ��^�C�v�@���[�v���邩
const bool animeLoop[ANIME_TYPE_NUM] =
{
	true,	//
};

//==============================================================================================

//�A�j���̓ǂݍ���
void AnimeClass::Load()
{
	for (int animeIndex = 0; animeIndex < ANIME_TYPE_NUM; animeIndex++)
	{
	
		//���摜�𕪊��ǂݍ���
			LoadDivGraph(animeFilePath[animeIndex],				//�p�X
						animeImgNum[animeIndex],				//�摜����
						animeImageSplitNum[animeIndex][0],		//���̐�
						animeImageSplitNum[animeIndex][1],		//�c�̐�
						animeImageSize[animeIndex][0],			//�����T�C�Y�@��
						animeImageSize[animeIndex][1],			//�����T�C�Y�@�c
						animeInfo[animeIndex].ImgHundle);		//�n���h���ϐ�

		//�A�j�������i�[
		animeInfo[animeIndex].animeUsedNum = animeImgNum[animeIndex];

		//�P��������̕\�����Ԃ�ݒ�
		animeInfo[animeIndex].changeTime = animwChageTime[animeIndex];

		//���[�v�A�j���[�V�������ݒ�
		if (animeLoop[animeIndex])
		{
			animeInfo[animeIndex].loop = true;
		}
		else
		{
			animeInfo[animeIndex].loop = false;
		}
		
	}
}

//==============================================================================================

//�A�j���̏�����
void AnimeClass::Init()
{
	//���ׂẴG�t�F�N�g���̕ϐ����N���A����i�[���ɂ���j
	for (int i = 0; i < ANIME_TYPE_NUM; i++)
	{
		animeInfo[i].x = 0;
		animeInfo[i].y = 0;
		animeInfo[i].animeUsedNum = 0;
		animeInfo[i].currentAnimeIndex = 0;

		animeInfo[i].changeTime = 0.0f;
		animeInfo[i].currentAnimeTime = 0.0f;

		animeInfo[i].isUse = false;

		animeInfo[i].type = ANIME_FIRST;
		animeInfo[i].loop = false;

		for (int n = 0; n < ANIME_MAX_NUM; n++)
		{
			animeInfo[i].ImgHundle[n] = 0;
		}
	}

	//�摜�̃��[�h
	Load();
}

//==============================================================================================

//�A�j���ʏ폈��
void AnimeClass::Step()
{
	for (int animeIndex = 0; animeIndex < ANIME_TYPE_NUM; animeIndex++)
	{
		//�g�p���Ȃ�A�j�����Ԃ��o�߂����āA�A�j���ԍ����X�V����
		if (animeInfo[animeIndex].isUse)
		{
			//���ԍX�V
			animeInfo[animeIndex].currentAnimeTime += 1.0f / 60;	//60��FPS

			//�摜�؂�ւ��ɕK�v�Ȏ��Ԍo�߂�����
			if (animeInfo[animeIndex].currentAnimeTime >= animeInfo[animeIndex].changeTime)
			{	
				//���̉摜��
				animeInfo[animeIndex].currentAnimeIndex++;

				//�v�����ԃ��Z�b�g
				animeInfo[animeIndex].currentAnimeTime = 0.0f;

				//���̉摜�����������Ȃ�
				if (animeInfo[animeIndex].currentAnimeIndex >= animeInfo[animeIndex].animeUsedNum)
				{
					if (animeInfo[animeIndex].loop)
					{
						//���߂ɖ߂�
						animeInfo[animeIndex].currentAnimeIndex = 0;
					}
					else
					{
						//�Ō�̉摜�ɌŒ�
						animeInfo[animeIndex].currentAnimeIndex = animeInfo[animeIndex].animeUsedNum-1;
					}
				}
			}
		}
	}
}

//==============================================================================================

//�A�j���`�揈���i�ʏ�̕`��֐��Ƃ��Ďg���j
//�����F���WX,Y�@�A�j���^�C�v���i�[���Ă���ϐ�
void AnimeClass::Draw(float x, float y, int type, float size,float angle)
{
	//�g�p���Ȃ猻�݂̃A�j���ԍ��ŕ`�悷��
	if (animeInfo[type].isUse)
	{
		//�ϐ����܂Ƃ߂�
		int handleIndex = animeInfo[type].currentAnimeIndex;
		int imageHundle = animeInfo[type].ImgHundle[handleIndex];

		DrawRotaGraphF(x, y, size, angle, imageHundle, true);
	}
}

//==============================================================================================

//�A�j���̌㏈��
void AnimeClass::Fin()
{
	for (int animeIndex = 0; animeIndex < ANIME_TYPE_NUM; animeIndex++)
	{
		//���ׂẴG�t�F�N�g���폜����
		for (int imageindex = 0; imageindex < animeInfo[animeIndex].animeUsedNum; imageindex++)
		{
			//�[���ȊO�Ȃ�폜����
			if (animeInfo[animeIndex].ImgHundle[imageindex] != 0)
			{
				//�摜�폜������ݒ肷��
				DeleteGraph(animeInfo[animeIndex].ImgHundle[imageindex]);

				//�폜������[�������Ă���
				animeInfo[animeIndex].ImgHundle[imageindex] = 0;
			}
		}
	}
}

//==============================================================================================

//�A�j���̃Z�b�g
//�����F�A�j���̎��, ���A�j���^�C�v���i�[����ϐ�
void AnimeClass::SetType(ANIME_TYPE type, int* animaHundle)
{
	//�ς���A�j�������g�p�Ȃ�ȉ����s
	if (!CheckType(type))
	{
		//���ݎg�p���̃A�j���̃t���O��܂�
		animeInfo[*animaHundle].isUse = false;

		//�A�j����ύX���i�[����
		*animaHundle = type;

		//�g�p���Ȃ�ȉ��s��Ȃ�
		if (!animeInfo[type].isUse)
		{
			//�v���p�̕ϐ����N���A
			animeInfo[type].currentAnimeIndex = 0;		//���݂̃A�j���ԍ�
			animeInfo[type].currentAnimeTime = 0.0f;	//���݂̃A�j������
			//�g�p���ɂ���
			animeInfo[type].isUse = true;
		}
	}
}

//�A�j���̍Đ�
//�����F�A�j���̎��
bool AnimeClass::CheckType(ANIME_TYPE type)
{
	//�g�p���Ă��邩�m�F
	if (animeInfo[type].isUse)
	{
		return true;
	}
	else
	{
		return false;
	}
}
