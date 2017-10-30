
#include<math.h>

#include"main.h"
#include"lib/Input.h"
#include"lib/Texture.h"
#include"Game/Enemy/EnemyManager.h"

/**
* @brief :コンストラクタ
*/
CEnemyManager::CEnemyManager()
{
	m_Enemy = std::make_unique<CEnemy>();
}

/**
* @brief :デストラクタ
*/
CEnemyManager::~CEnemyManager()
{

}

/**
* @brief		:読み込んだテクスチャIDの取得
* @param idx	:テクスチャID
*/
void CEnemyManager::SetTextureId(const int &idx)
{
	texid = idx;
	m_Enemy->SetTextureId(texid);
}

/**
* @brief :初期化
*/
void CEnemyManager::Initialize()
{
	m_Enemy->Initialize();
}

/**
* @brief :更新
*/
void CEnemyManager::Update()
{
	m_Enemy->Update();
}

/**
* @brief		:読み込んだ画像表示
* @param tex	:テクスチャクラス
*/
void CEnemyManager::Render(const std::unique_ptr<CTexture> &tex)
{
	m_Enemy->Render(tex);
//	tex->RenderTex(pos, texid);
}

/**
* @brief :削除
*/
void CEnemyManager::Delete()
{

}

