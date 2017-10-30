
#include<memory>

#include"main.h"
#include"lib/Input.h"
#include"lib/Texture.h"
#include"Game/GameBase.h"
#include"Game/Bullet/BulletManager.h"

/**
* @brief :�R���X�g���N�^
*/
CBulletManager::CBulletManager()
{
	m_Bullet.push_back(CBullet());
	itr = m_Bullet.begin();
//	m_Bullet = std::make_unique<CBullet>();
}

/**
* @brief :�f�X�g���N�^
*/
CBulletManager::~CBulletManager()
{
	m_Bullet.clear();
//	m_Bullet->Delete();
}

/**
* @brief :�ǂݍ��񂾃e�N�X�`��ID�̎擾
*/
void CBulletManager::SetTextureId(const int &idx)
{
	texid = idx;
	itr->SetTextureId(texid);
}

/**
* @brief	:������
*/
void CBulletManager::Initialize()
{
	itr->SetPlayerPos(m_PlayerPos);

	itr->Initialize();

}

/**
* @brief		:�X�V
* @param key	:�L�[���
*/
void CBulletManager::Update(std::unique_ptr<CInput>&key)
{
	for (itr = m_Bullet.begin(); itr != m_Bullet.end();){
	itr->SetPlayerPos(m_PlayerPos);
		itr->Update();
		if (!itr->GetFlag()){
			//�C�e���[�^�[�̎w��ɂ������v�f���폜
//			itr = m_Bullet.erase(itr);
//			m_Bullet.erase(itr);
		}
		itr++;
	}
	
	if (key->GetInputDown(key->InputMouseLeft)){
			m_Bullet.push_back(CBullet());
			itr = m_Bullet.end();
			itr--;
			itr->SetTextureId(texid);
			itr->SetPlayerPos(m_PlayerPos);
			itr->Initialize();
	}
	
}

/**
* @brief		:�ǂݍ��񂾉摜�\��
* @param tex	:�e�N�X�`���N���X
*/
void CBulletManager::Render(std::unique_ptr<CTexture> &tex)
{
	for (itr = m_Bullet.begin(); itr != m_Bullet.end();){
		itr->Render(tex);
		itr++;
	}
}

/**
* @brief :�폜,���
*/
void CBulletManager::Delete()
{
	for (itr = m_Bullet.begin(); itr != m_Bullet.end();){
		itr->Delete();
		itr++;
	}
}


