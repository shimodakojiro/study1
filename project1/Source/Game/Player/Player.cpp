
#include<math.h>

#include"main.h"
#include"Game/GameBase.h"
#include"lib/Texture.h"
#include"lib/Input.h"
#include"Game/Player/Player.h"

/**
* @brief :�R���X�g���N�^
*/
CPlayer::CPlayer()
{

}

/**
* @brief :�f�X�g���N�^
*/
CPlayer::~CPlayer()
{

}

/**
* @brief :�ǂݍ��񂾃e�N�X�`��ID�̎擾
*/
void CPlayer::SetTextureId(const int &idx)
{
	texid = idx;
	int y = 0;
}

/**
* @brief :������
*/
void CPlayer::Initialize()
{
	pos = Vector2(m_StartX, m_StartY);
	angle = 0.0f;
	velocity.x = 0.0f;
	velocity.y = 0.0f;
	angle = 0.0f;

}

/**
* @brief		:�X�V
* @param key	:���̓N���X
*/
void CPlayer::Update(const std::unique_ptr<CInput> &key)
{
	velocity = Vector2(0.0f,0.0f);

	if (key->GetInputNow(key->InputW)){
		velocity.y = -m_Speed;
	}
	if (key->GetInputNow(key->InputS)){
		velocity.y = m_Speed;
	}
	if (key->GetInputNow(key->InputA)){
		velocity.x = -m_Speed;
	}
	if (key->GetInputNow(key->InputD)){
		velocity.x = m_Speed;
	}

	pos = pos + velocity;

	if (pos.x <= 0)pos.x = 0;
	if (pos.x >= 600)pos.x = 600;
	if (pos.y <= 0)pos.y = 0;
	if (pos.y >= 600)pos.y = 600;
}

/**
* @brief		:�ǂݍ��񂾉摜�\��
* @param tex	:�e�N�X�`���N���X
*/
void CPlayer::Render(const std::unique_ptr<CTexture> &tex)
{
	tex->RenderTex(pos, texid);
//	DrawRotaGraph(pos.x, pos.y, 1.0f, angle, texid, TRUE);
}

/**
* @brief :�폜
*/
void CPlayer::Delete()
{

}

