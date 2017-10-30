
#include<memory>

#include"../../Header/Scene/SceneBase.h"
#include"../../Header/Scene/SceneMain.h"

/**
* @brief :コンストラクタ
*/
CSceneMain::CSceneMain()
{
	m_Key = std::make_unique<CInput>();
	m_Tex = std::make_unique<CTexture>();

	m_Player = std::make_unique<CPlayer>();
	m_BulletManager = std::make_unique<CBulletManager>();
	m_EnemyManager = std::make_unique<CEnemyManager>();

	m_Graphic = std::make_unique<CGraphic>();
}

/**
* @brief :コンストラクタ
*/
CSceneMain::~CSceneMain()
{

}

/**
* @brief :データ読み込み
*/
void CSceneMain::Load()
{
	m_Graphic->Load(m_Tex);
//	m_Tex->LoadTex("../Resource/Player/player.png");
}

/**
* @brief :読み込んだテクスチャIDの割り振り
*/
void CSceneMain::SetTextureId()
{
	m_Player->SetTextureId(m_Graphic->GetPlayerTextureId());
	m_BulletManager->SetTextureId(m_Graphic->GetBulletTextureId());
	m_EnemyManager->SetTextureId(m_Graphic->GetBulletTextureId());
}

/**
* @brief :初期化
*/
void CSceneMain::Initialize()
{
	SetTextureId();

	m_Player->Initialize();
	m_BulletManager->SetPlayerPos(m_Player->GetPos());
	m_BulletManager->Initialize();
	m_EnemyManager->Initialize();
}

/**
* @brief	:入力情報取得
* @return	:Escキーの入力有無
*/
bool CSceneMain::KeyState()
{
	m_Key->CheackInputState();
	return m_Key->GetEsckeystate();
}

/**
* @brief :ゲームメイン更新
*/
bool CSceneMain::Update()
{
	bool endflag = KeyState();

	m_Player->Update(m_Key);
	m_BulletManager->SetPlayerPos(m_Player->GetPos());
	m_BulletManager->Update(m_Key);
	m_EnemyManager->Update();

	return endflag;
}

/**
* @brief :読み込んだ画像表示
*/
void CSceneMain::Render()
{
	m_Player->Render(m_Tex);
	m_BulletManager->Render(m_Tex);
	m_EnemyManager->Render(m_Tex);
}

/**
* @brief :削除,解放
*/
void CSceneMain::Delete()
{
	m_Player->Delete();
	m_BulletManager->Delete();
	m_EnemyManager->Delete();
}
