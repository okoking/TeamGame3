
#include <DxLib.h>
#include "Effect.h"

#include"../FrameRate/FrameRate.h"

//�G�t�F�N�g���
EffectInfo Effect::effectInfo[EFFECT_MAX_NUM];

//==============================================================================================

//�G�t�F�N�g�̃t�@�C���p�X
const char effectFilePath[EFFECT_TYPE_NUM][256] =
{
	"data/effect/ripple_96�~96.png",	//�g��
};

//�e�G�t�F�N�g�̃A�j����
const int effectAnimeImgNum[EFFECT_TYPE_NUM] =
{
	8,	//�g��
};

//�e�G�t�F�N�g�̉摜������ [0] = x, [1] = y
const int effectImageSplitNum[EFFECT_TYPE_NUM][2] =
{
	{ 8, 1,},	//�g��
};

//�G�t�F�N�g�̉摜�T�C�Y
const int effectImageSize[EFFECT_TYPE_NUM][2] =
{
	{ 96, 96,},	//�g��
};

//�e�G�t�F�N�g�̃A�j���摜�؂�ւ�����
const float effectChageTime[EFFECT_TYPE_NUM] =
{
	0.15f,	//�g��
};

//==============================================================================================

//�G�t�F�N�g�̓ǂݍ���
//����	�F�G�t�F�N�g�̎�ށA�쐬��
void Effect::Load(EFFECT_TYPE type, int create_num)
{
	for (int createNumIndex = 0; createNumIndex < create_num; createNumIndex++)
	{
		for (int effectIndex = 0; effectIndex < EFFECT_MAX_NUM; effectIndex++)
		{
			//���ǂݍ��݂��Ă��Ȃ��G�t�F�N�g����������
			//���i�ЂƂڂ̉摜�n���h�����[���Ȃ�ǂݍ��݂���ĂȂ��j
			if (effectInfo[effectIndex].ImgHundle[0] == -1)
			{
				//���摜�𕪊��ǂݍ���
				LoadDivGraph(	effectFilePath[type],	//�p�X
								effectAnimeImgNum[type],							//�摜����
								effectImageSplitNum[type][0],						//���̐�
								effectImageSplitNum[type][1],						//�c�̐�
								effectImageSize[type][0],								//�����T�C�Y�@��
								effectImageSize[type][1],								//�����T�C�Y�@�c
								effectInfo[effectIndex].ImgHundle);					//�n���h���ϐ�

				//��������
				if (effectInfo[effectIndex].ImgHundle[0] != -1)
				{
					//���A�j�������i�[
					effectInfo[effectIndex].animeUsedNum = effectAnimeImgNum[type];

					//���P��������̕\�����Ԃ�ݒ�
					effectInfo[effectIndex].changeTime = effectChageTime[type];

					//���G�t�F�N�g�̎�ނ�ݒ�
					effectInfo[effectIndex].type = type;
				}
				//�����ۂɂ�����炸������
				break;
			}
		}
	}
}

//==============================================================================================

//�G�t�F�N�g�̏�����
void Effect::Init()
{
	//�����ׂẴG�t�F�N�g���̕ϐ����N���A����i�[���ɂ���j
	for (int i = 0; i < EFFECT_MAX_NUM; i++)
	{		
		effectInfo[i].x = 0;
		effectInfo[i].y = 0;
		effectInfo[i].animeUsedNum = 0;
		effectInfo[i].currentAnimeIndex = 0;

		effectInfo[i].changeTime = 0.0f;
		effectInfo[i].currentAnimeTime = 0.0f;

		effectInfo[i].isUse = false;

		effectInfo[i].type = -1;

		for (int n=0; n < EFFECT_ANIME_MAX_NUM; n++)
		{
			effectInfo[i].ImgHundle[n] = -1;
		}
	}
}

//==============================================================================================

//�G�t�F�N�g�ʏ폈��
void Effect::Step()
{
	for (int effectindex = 0; effectindex < EFFECT_MAX_NUM; effectindex++)
	{
		//���g�p���Ȃ�A�j�����Ԃ��o�߂����āA�A�j���ԍ����X�V����
		if (effectInfo[effectindex].isUse)
		{
			//�����ԍX�V
			effectInfo[effectindex].currentAnimeTime += 1.0f/60;	//60��FPS

			//���摜�؂�ւ��ɕK�v�Ȏ��Ԍo�߂�����
			if (effectInfo[effectindex].currentAnimeTime >= effectInfo[effectindex].changeTime)
			{
				//�����̉摜��
				effectInfo[effectindex].currentAnimeIndex++;

				//���v�����ԃ��Z�b�g
				effectInfo[effectindex].currentAnimeTime = 0.0f;

				//�����̉摜�����������Ȃ�
				if (effectInfo[effectindex].currentAnimeIndex >= effectInfo[effectindex].animeUsedNum)
				{
					//���g�p���t���O��OFF��
					effectInfo[effectindex].isUse = false;
				}
			}
		}
	}
}

//==============================================================================================

//�G�t�F�N�g�`�揈���F�O�V�X�e�� �P�Q�[��
void Effect::Draw(int type)
{
	for(int effect_index = 0; effect_index < EFFECT_MAX_NUM; effect_index++)
	{
		switch (type)
		{
			//�V�X�e��
		case 0: {

			if (effectInfo[effect_index].type != EFFECT_TYPE_RIPPLE)
			{
				continue;
			}

			//���g�p���Ȃ猻�݂̃A�j���ԍ��ŕ`�悷��
			if (effectInfo[effect_index].isUse)
			{
				float x = effectInfo[effect_index].x;
				float y = effectInfo[effect_index].y;
				int hundleIndex = effectInfo[effect_index].currentAnimeIndex;
				int imageHundle = effectInfo[effect_index].ImgHundle[hundleIndex];

				DrawRotaGraphF(x, y, 1.0f, 0.0f, imageHundle, true);
			}

			break; }

			//�Q�[���F�ʏ�
		case 1: {

			if (effectInfo[effect_index].type < EFFECT_TYPE_SLASH)
			{
				continue;
			}

			//�ʏ�
			if (effectInfo[effect_index].type < EFFECT_TYPE_BLESSING)
			{
				if (effectInfo[effect_index].type != EFFECT_TYPE_GUN_HOLES)
				{
					//���g�p���Ȃ猻�݂̃A�j���ԍ��ŕ`�悷��
					if (effectInfo[effect_index].isUse)
					{
						float x = effectInfo[effect_index].x;
						float y = effectInfo[effect_index].y;
						int hundleIndex = effectInfo[effect_index].currentAnimeIndex;
						int imageHundle = effectInfo[effect_index].ImgHundle[hundleIndex];

						DrawRotaGraphF(x, y, 1.0f, 0.0f, imageHundle, true);
					}
				}
				else
				{
					//���g�p���Ȃ猻�݂̃A�j���ԍ��ŕ`�悷��
					if (effectInfo[effect_index].isUse)
					{
						float x = effectInfo[effect_index].x;
						float y = effectInfo[effect_index].y;
						int hundleIndex = effectInfo[effect_index].currentAnimeIndex;
						int imageHundle = effectInfo[effect_index].ImgHundle[hundleIndex];

						DrawRotaGraphF(x, y, 1.0f, 0.0f, imageHundle, true);
					}
				}
			}

			//���Z
			else
			{
				//���g�p���Ȃ猻�݂̃A�j���ԍ��ŕ`�悷��
				if (effectInfo[effect_index].isUse)
				{
					float x = effectInfo[effect_index].x;
					float y = effectInfo[effect_index].y;
					int hundleIndex = effectInfo[effect_index].currentAnimeIndex;
					int imageHundle = effectInfo[effect_index].ImgHundle[hundleIndex];

					//���[�h����Z�ɂ���
					SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

					DrawRotaGraphF(x, y, 1.0f, 0.0f, imageHundle, true);

					//���[�h��ʏ�ɖ߂�
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				}
			}

			break; }

		default: {
			break; }
		}
	}
}

//==============================================================================================

//�G�t�F�N�g�̌㏈��
void Effect::Fin()
{
	for (int effectindex = 0; effectindex < EFFECT_MAX_NUM; effectindex++)
	{
		//�����ׂẴG�t�F�N�g���폜����
		for (int imageindex = 0; imageindex < effectInfo[effectindex].animeUsedNum; imageindex++)
		{
			//�����ׂč폜����

				//���[���ȊO�Ȃ�폜����
			if (effectInfo[effectindex].ImgHundle[imageindex] != -1)
			{
				//���摜�폜������ݒ肷��
				DeleteGraph(effectInfo[effectindex].ImgHundle[imageindex]);

				//���폜������[�������Ă���
				effectInfo[effectindex].ImgHundle[imageindex] = -1;
			}
		}
	}
}

//==============================================================================================

//�G�t�F�N�g�̍Đ�
//����	�F�G�t�F�N�g�̎��, �w���W, �x���W, �P��������̕\������
void Effect::Play(EFFECT_TYPE type, float x, float y)
{
	for (int effectindex = 0; effectindex < EFFECT_MAX_NUM; effectindex++)
	{
		//�����g�p�G�t�F�N�g��T���čĐ�
		if (!effectInfo[effectindex].isUse)
		{
			//���g�p���Ȃ�ȉ��s��Ȃ�
			//���^�C�v����v����
			if (effectInfo[effectindex].type == type)
			{
				//�����W�ݒ�
				effectInfo[effectindex].x = x;
				effectInfo[effectindex].y = y;
				//���v���p�̕ϐ����N���A
				effectInfo[effectindex].currentAnimeIndex = 0;		//���݂̃A�j���ԍ�
				effectInfo[effectindex].currentAnimeTime = 0.0f;	//���݂̃A�j������
				//���g�p���ɂ���
				effectInfo[effectindex].isUse = true;

				//��������
				break;
			}
		}
	}
}
