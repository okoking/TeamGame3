#include "Player.h"
#include "../Input/Input.h"
#include "../Scene/Scene.h"

//�v���C���[�̏�����
void Player::Init()
{
	//�v���C���[�̍��W�̏�����
	HeartposX = HEART_INIT_POS_X;		//X���W
	HeartposY = HEART_INIT_POS_Y;		//Y���W

	ShieldposX = HEART_INIT_POS_X;		//X���W
	ShieldposY = HEART_INIT_POS_Y - HEART_SIZE;		//Y���W

	// �V�[���h�̊p�x������
	Shieldangle = 270.0f;
	CurrentShieldangle = SHIELD_ANGLE_UP;

	//�v���C���[�̉摜�n���h���̏�����
	HeartImageHundle = -1;
	ShieldImageHundle = -1;
	HpHundle = -1;

	// HP
	Hp = PLAYER_HP;

	// �K�[�h������
	GuardCnt = 0;

	isActive = true;							// �v���C���[�������Ă��邩
	invincibletimeCnt = PLAYER_INVINCIBLE_TIME; // ���G���ԃJ�E���g�p
	isDraw = true;								// �`�悳��Ă��邩
	Cr= GetColor(0, 255, 0);					// �ΐF���Z�b�g
}

//�v���C���[�̓ǂݍ��ݏ���
void Player::Load()
{
	HeartImageHundle = LoadGraph(HEART_PATH);
	ShieldImageHundle = LoadGraph(SHIELD_PATH);
	HpHundle = LoadGraph(HP_PATH);
}

//�v���C���[�̒ʏ폈��
void Player::Step()
{
	//�v���C���[�̑��쏈��
	Operation();

	// ���G���ԏ���
	Invincible();

	if (Input::Key::Push(KEY_INPUT_RETURN)) {
		//�v���C�V�[���̏I�������ɑJ��
		g_CurrentSceneID = SCENE_ID_FIN_PLAY;
	}
	if (Input::Key::Push(KEY_INPUT_Q)) {
		// �v���C���[�_���[�W����
		Damaged();
	}

}

//�v���C���[�̕`�揈��
void Player::Draw()
{
	if (isDraw) { // �`�悳��Ă��锻��Ȃ�
		DrawRotaGraph((int)HeartposX, (int)HeartposY, 1.0f, 0.0f, HeartImageHundle, true); // �n�[�g
	}
	
	DrawRotaGraph((int)ShieldposX, (int)ShieldposY, 1.0f, Shieldangle / 180 * 3.14, ShieldImageHundle, true); // ��

	DrawGraph(0, 0, HpHundle, true); // HP

	DrawBox(15, 30, Hp * 62, 84, Cr, TRUE);    // �l�p�`��`��
}

//�v���C���[�̏I������
void Player::Fin()
{
	// �n�[�g�摜�폜
	DeleteGraph(HeartImageHundle);

	// �V�[���h�摜�폜
	DeleteGraph(ShieldImageHundle);
}

//�v���C���[�̑��쏈��
void Player::Operation()
{
	// ������͂��������Ɍ�����
	if (Input::Key::Push(KEY_INPUT_LEFT)) {
		ShieldposX = HeartposX - HEART_SIZE;
		ShieldposY = HeartposY;
		CurrentShieldangle = SHIELD_ANGLE_LEFT;
		Shieldangle = 180.0f;
	}
	if (Input::Key::Push(KEY_INPUT_RIGHT)) {
		ShieldposX = HeartposX + HEART_SIZE;
		ShieldposY = HeartposY;
		CurrentShieldangle = SHIELD_ANGLE_RIGHT;
		Shieldangle = 0.0f;
	}
	if (Input::Key::Push(KEY_INPUT_UP)) {
		ShieldposX = HeartposX;
		ShieldposY = HeartposY - HEART_SIZE;
		CurrentShieldangle = SHIELD_ANGLE_UP;
		Shieldangle = 270.0f;
	}
	if (Input::Key::Push(KEY_INPUT_DOWN)) {
		ShieldposX = HeartposX;
		ShieldposY = HeartposY + HEART_SIZE;
		CurrentShieldangle = SHIELD_ANGLE_DOWN;
		Shieldangle = 90.0f;
	}
}

// �v���C���[�_���[�W����
void Player::Damaged()
{
	// ���G���łȂ��Ȃ�
	if (invincibletimeCnt == PLAYER_INVINCIBLE_TIME) {
		//se
		Sound::Se::Play(SE_DAMAGE);

		// ���G���Ԃ����Z�b�g
		invincibletimeCnt = 0;
		// HP�����炷
		Hp--;

		if (Hp <= 1) { // HP��1�ȉ��Ȃ�
			Cr = GetColor(255, 0, 0); // �ԐF���Z�b�g
		}
		else if (Hp <= 3) { // HP��3�ȉ��Ȃ�
			Cr = GetColor(255, 255, 0); // ���F���Z�b�g
		}

		// HP��0����������Ȃ�
		if (Hp < 0) {
			Hp = 0;
		}

		// �̗͂�0�ɂȂ����Ƃ�
		if (Hp == 0) {
			// �E����
			isActive = false;

			//�v���C�V�[���̏I�������ɑJ��
			g_CurrentSceneID = SCENE_ID_FIN_PLAY;
		}
	}
}

// ���G���ԏ���
void Player::Invincible()
{
	isDraw = false; // ��x�`�悳��Ȃ�

	//���G���Ȃ�J�E���g��i�߂�
	invincibletimeCnt++;

	// ����𒴂��Ă���Ȃ�������
	if (invincibletimeCnt > PLAYER_INVINCIBLE_TIME) {
		invincibletimeCnt = PLAYER_INVINCIBLE_TIME;
	}

	if (invincibletimeCnt % 9 < 4) {
		isDraw = true; // �`�悳��Ă���ɂ���
	}
}
