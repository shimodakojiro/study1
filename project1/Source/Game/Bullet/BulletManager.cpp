
#include<memory>

#include"main.h"
#include"lib/Input.h"
#include"lib/Texture.h"
#include"Game/GameBase.h"
#include"Game/Bullet/BulletManager.h"

CBulletManager::CBulletManager()
{
	m_Bullet.push_back(CBullet());
	itr = m_Bullet.begin();
//	m_Bullet = std::make_unique<CBullet>();
}

CBulletManager::~CBulletManager()
{
	m_Bullet.clear();
//	m_Bullet->Delete();
}

void CBulletManager::SetTextureId(const int &idx)
{
	texid = idx;
	itr->SetTextureId(texid);
}

void CBulletManager::Initialize()
{
	itr->SetPlayerPos(m_PlayerPos);

	itr->Initialize();

}

void CBulletManager::Update(std::shared_ptr<CInput>&key)
{
	for (itr = m_Bullet.begin(); itr != m_Bullet.end();){
	itr->SetPlayerPos(m_PlayerPos);
		itr->Update();
		if (!itr->GetFlag()){
			//イテレーターの指定にあった要素を削除
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

void CBulletManager::Render(std::shared_ptr<CTexture> &tex)
{
	for (itr = m_Bullet.begin(); itr != m_Bullet.end();){
		itr->Render(tex);
		itr++;
	}
}

void CBulletManager::Delete()
{
	for (itr = m_Bullet.begin(); itr != m_Bullet.end();){
		itr->Delete();
		itr++;
	}
}


