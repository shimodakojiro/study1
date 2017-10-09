
#include<memory>

#include"DxLib.h"
#include"../../Header/Game/GameBase.h"
#include"../../Header/Game/Bullet/BulletManager.h"

CBulletManager::CBulletManager()
{
//	itr = m_Bullet.begin();
	m_Bullet = std::make_unique<CBullet>();
}

CBulletManager::~CBulletManager()
{
//	m_Bullet.clear();
}

void CBulletManager::SetTextureId(const int &idx)
{
	texid = idx;
	m_Bullet->SetTextureId(texid);
}

void CBulletManager::Initialize()
{
	m_Bullet->SetPlayerPos(m_PlayerPos);

	m_Bullet->Initialize();

//	m_RepCounter = m_MaxRepCounter;
//	m_RepOn = false;
//	m_NowInput = false;
//	m_OldInput = false;
}

void CBulletManager::Update()
{
	m_Bullet->SetPlayerPos(m_PlayerPos);

//	m_OldInput = m_NowInput;

	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0){
		m_Bullet->BulletCreate();
	}
//	if (m_Bullet->GetFlag()){
		m_Bullet->Update();
//	}
}

void CBulletManager::Render()
{
	m_Bullet->Render();
}

void CBulletManager::Delete()
{

}


