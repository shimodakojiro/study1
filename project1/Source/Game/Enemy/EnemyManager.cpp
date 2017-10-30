
#include<math.h>

#include"main.h"
#include"lib/Input.h"
#include"lib/Texture.h"
#include"Game/Enemy/EnemyManager.h"

/**
* @brief :�R���X�g���N�^
*/
CEnemyManager::CEnemyManager()
{
	m_Enemy = std::make_unique<CEnemy>();
}

/**
* @brief :�f�X�g���N�^
*/
CEnemyManager::~CEnemyManager()
{

}

/**
* @brief		:�ǂݍ��񂾃e�N�X�`��ID�̎擾
* @param idx	:�e�N�X�`��ID
*/
void CEnemyManager::SetTextureId(const int &idx)
{
	texid = idx;
	m_Enemy->SetTextureId(texid);
}

/**
* @brief :������
*/
void CEnemyManager::Initialize()
{
	m_Enemy->Initialize();
}

/**
* @brief :�X�V
*/
void CEnemyManager::Update()
{
	m_Enemy->Update();
}

/**
* @brief		:�ǂݍ��񂾉摜�\��
* @param tex	:�e�N�X�`���N���X
*/
void CEnemyManager::Render(const std::unique_ptr<CTexture> &tex)
{
	m_Enemy->Render(tex);
//	tex->RenderTex(pos, texid);
}

/**
* @brief :�폜
*/
void CEnemyManager::Delete()
{

}

