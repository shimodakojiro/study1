
#include<memory>

#include"main.h"
#include"lib/Texture.h"
#include"Game/GameBase.h"
#include"Game/Bullet/Bullet.h"

/**
* @brief :�R���X�g���N�^
*/
CBullet::CBullet()
{

}

/**
* @brief :�f�X�g���N�^
*/
CBullet::~CBullet()
{

}

/**
* @brief :�ǂݍ��񂾃e�N�X�`��ID�̎擾
*/
void CBullet::SetTextureId(const int &idx)
{
	texid = idx;
}

/**
* @brief :������
*/
void CBullet::Initialize()
{
	pos = m_PlayerPos;
	angle = 0.0f;
	velocity = Vector2(mSpeedX, mSpeedY);
	m_Frame = 0;
	m_Flag = false;
}

/**
* @brief :�X�V
*/
void CBullet::Update()
{
	m_Frame++;
	pos = pos + velocity;

	if (m_Frame >= m_MaxFrame){
		m_Flag = false;
	}
}

/**
* @brief		:�ǂݍ��񂾉摜�\��
* @param tex	:�e�N�X�`���N���X
*/
void CBullet::Render(std::unique_ptr<CTexture> &tex)
{
	tex->RenderTex(pos, texid);
}

/**
* @brief :�폜
*/
void CBullet::Delete()
{

}

/**
* @brief :���ˎ��̒e������
*/
void CBullet::BulletCreate()
{
	pos = m_PlayerPos;
	angle = 0.0f;
	m_Flag = true;
	m_Frame = 0;
}


