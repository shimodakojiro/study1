
#include<math.h>

#include"main.h"
#include"Game/GameBase.h"
#include"lib/Texture.h"
#include"lib/Input.h"
#include"Game/Enemy/Enemy.h"

/**
* @brief :�R���X�g���N�^
*/
CEnemy::CEnemy()
{

}

/**
* @brief :�f�X�g���N�^
*/
CEnemy::~CEnemy()
{

}

/**
* @brief :�ǂݍ��񂾃e�N�X�`��ID�̎擾
*/
void CEnemy::SetTextureId(const int &idx)
{
	texid = idx;
}

/**
* @brief		:���W�Z�b�g
* @param pos	:�w��̍��W
*/
void CEnemy::SetPosition(const Vector2 &pos)
{
	this->pos = pos;
}

/**
* @brief :������
*/
void CEnemy::Initialize()
{
	pos = Vector2(100, 100);
	velocity = Vector2(0.0f, 0.0f);
	angle = 0.0;

}

/**
* @brief :�X�V
*/
void CEnemy::Update()
{

}

/**
* @brief :�ǂݍ��񂾉摜�\��
* @param tex	:�e�N�X�`���N���X
*/
void CEnemy::Render(const std::unique_ptr<CTexture> &tex)
{
	tex->RenderTex(pos, texid);
}

/**
* @brief :�폜
*/
void CEnemy::Delete()
{

}

