
#include<memory>

#include"DxLib.h"
#include"../../Header/Game/GameBase.h"
#include"../../Header/Game/Bullet/BulletManager.h"

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

	i = 0;

//	m_RepCounter = m_MaxRepCounter;
//	m_RepOn = false;
//	m_NowInput = false;
//	m_OldInput = false;
}

void CBulletManager::Update()
{
	for (itr = m_Bullet.begin(); itr != m_Bullet.end();){
	itr->SetPlayerPos(m_PlayerPos);
		itr->Update();
		itr++;
	}
	
/*	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0){
		i++;
		if (i >= 60){
			m_Bullet.push_back(CBullet());
			itr = m_Bullet.end();
			itr--;
			itr->SetTextureId(texid);
			itr->SetPlayerPos(m_PlayerPos);
			itr->Initialize();
			i = 0;
		}
	}
	*/

//	if (!itr->GetFlag()){
		//イテレーターの指定にあった要素を削除
//		itr = m_Bullet.erase(itr);
//		}
}

void CBulletManager::Render()
{
	for (itr = m_Bullet.begin(); itr != m_Bullet.end();){
		itr->Render();
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


