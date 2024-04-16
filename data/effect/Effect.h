
#ifndef __EFFECT_H__
#define __EFFECT_H__

//��x�ɕ\���ł���G�t�F�N�g�ő吔
const int EFFECT_MAX_NUM = 200;

//�G�t�F�N�g�̃A�j���ő吔
const int EFFECT_ANIME_MAX_NUM = 10;

//==============================================================================================

//�G�t�F�N�g�̎��
enum EFFECT_TYPE
{
	EFFECT_TYPE_RIPPLE = 0,		//�g��

	//=============�ް�=============

	EFFECT_TYPE_SLASH,			//�a��
	EFFECT_TYPE_GUN_HOLES,		//�e��
	EFFECT_TYPE_LIGHTNING,		//�d��
	EFFECT_TYPE_FEATHER_BREAK,	//�H���j��

	EFFECT_TYPE_ENEDAMAGE,		//�G�̃_���[�W

	//=============���Z=============

	EFFECT_TYPE_BLESSING,		//�񕜁F���Z

	EFFECT_TYPE_NUM,
};

//==============================================================================================

//�G�t�F�N�g���
struct EffectInfo
{
	//���G�t�F�N�g�̎��
	int type;

	//���摜�n���h��
	int ImgHundle[EFFECT_ANIME_MAX_NUM];

	//�����W
	float x, y;
	//���g�p�t���O
	bool isUse;

	//���A�j����
	int animeUsedNum;
	//�����݂̃A�j���ԍ�
	int currentAnimeIndex;

	//���P��������̕\������
	float changeTime;
	//�����݂̃A�j������
	float currentAnimeTime;
};

//�G�t�F�N�g���
class Effect
{
private:

	//�G�t�F�N�g���
	static EffectInfo effectInfo[EFFECT_MAX_NUM];

public:

	//�G�t�F�N�g�̓ǂݍ���
//����	�F�G�t�F�N�g�̎�ށA�쐬��
	static void Load(EFFECT_TYPE type, int create_num);

	//�G�t�F�N�g�̏�����
	static void Init();

	//�G�t�F�N�g�ʏ폈��
	static void Step();

	//�G�t�F�N�g�`�揈���F�O�V�X�e�� �P�Q�[��
	static void Draw(int type=0);

	//�G�t�F�N�g�̌㏈��
	static void Fin();

	//�G�t�F�N�g�̍Đ�
	//����	�F�G�t�F�N�g�̎��, �w���W, �x���W, �P��������̕\������
	static void Play(EFFECT_TYPE type, float x, float y);

};

#endif
