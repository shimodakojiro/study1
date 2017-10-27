
#include<memory>

#include"../../Header/Scene/SceneBase.h"
#include"../../Header/Scene/SceneMain.h"

CSceneMain::CSceneMain()
{
	m_Key = std::make_shared<CInput>();
	m_Tex = std::make_shared<CTexture>();

	m_Player = std::make_unique<CPlayer>();
	m_BulletManager = std::make_unique<CBulletManager>();
	m_Graphic = std::make_unique<CGraphic>();
}

CSceneMain::~CSceneMain()
{

}

void CSceneMain::Load()
{
	m_Graphic->Load(m_Tex);
//	m_Tex->LoadTex("../Resource/Player/player.png");
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

/**
* @brief :“ü—Íî•ñŽæ“¾
*/
bool CSceneMain::KeyState()
{
	return m_Key->GetEsckeystate();
}

bool CSceneMain::Update()
{
	bool endflag = KeyState();

	m_Player->Update(m_Key);
	m_BulletManager->SetPlayerPos(m_Player->GetPos());
	m_BulletManager->Update(m_Key);

	return endflag;
}

void CSceneMain::Render()
{
	m_Player->Render(m_Tex);
	m_BulletManager->Render(m_Tex);
}

void CSceneMain::Delete()
{
	m_Player->Delete();
	m_BulletManager->Delete();
}
