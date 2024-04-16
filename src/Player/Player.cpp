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
	Shieldangle = 90.0f;

	//�v���C���[�̉摜�n���h���̏�����
	HeartImageHundle = -1;
	ShieldImageHundle = -1;

	// HP
	Hp = PLAYER_HP;

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

	DrawBox(0, 0, Hp * 64, 32, Cr, TRUE);    // �l�p�`��`��
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
		Shieldangle = 180.0f;
	}
	if (Input::Key::Push(KEY_INPUT_RIGHT)) {
		ShieldposX = HeartposX + HEART_SIZE;
		ShieldposY = HeartposY;
		Shieldangle = 0.0f;
	}
	if (Input::Key::Push(KEY_INPUT_UP)) {
		ShieldposX = HeartposX;
		ShieldposY = HeartposY - HEART_SIZE;
		Shieldangle = 90.0f;
	}
	if (Input::Key::Push(KEY_INPUT_DOWN)) {
		ShieldposX = HeartposX;
		ShieldposY = HeartposY + HEART_SIZE;
		Shieldangle = 270.0f;
	}
}

// �v���C���[�_���[�W����
void Player::Damaged()
{
	// ���G���łȂ��Ȃ�
	if (invincibletimeCnt == PLAYER_INVINCIBLE_TIME) {
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

	if (invincibletimeCnt % 12 < 6) {
		isDraw = true; // �`�悳��Ă���ɂ���
	}
}
