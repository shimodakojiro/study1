
#include<memory>

#include"../../Header/Scene/SceneBase.h"
#include"../../Header/Scene/SceneMain.h"

CSceneMain::CSceneMain()
{
	m_Player = std::make_unique<CPlayer>();
	m_BulletManager = std::make_unique<CBulletManager>();
	m_Graphic = std::make_unique<CGraphic>();
}

CSceneMain::~CSceneMain()
{

}

void CSceneMain::Load()
{
	m_Graphic->Load();
}

void CSceneMain::SetTextureId()
{
	m_Player->SetTextureId(m_Graphic->GetPlayerTextureId());
	m_BulletManager->SetTextureId(m_Graphic->GetBulletTextureId());
}

void CSceneMain::Initialize()
{
	SetTextureId();

	m_Player->Initialize();
	m_BulletManager->SetPlayerPos(m_Player->GetPos());
	m_BulletManager->Initialize();
}

void CSceneMain::Update()
{
	m_Player->Update();
	m_BulletManager->SetPlayerPos(m_Player->GetPos());
	m_BulletManager->Update();
}

void CSceneMain::Render()
{
	m_Player->Render();
	m_BulletManager->Render();
}

void CSceneMain::Delete()
{
	m_Player->Delete();
	m_BulletManager->Delete();
}
