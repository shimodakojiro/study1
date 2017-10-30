
#include<memory>

#include"main.h"
#include"lib/Input.h"
#include"lib/Texture.h"
#include"Game/GameBase.h"
#include"Game/Bullet/BulletManager.h"

/**
* @brief :コンストラクタ
*/
CBulletManager::CBulletManager()
{
	m_Bullet.push_back(CBullet());
	itr = m_Bullet.begin();
//	m_Bullet = std::make_unique<CBullet>();
}

/**
* @brief :デストラクタ
*/
CBulletManager::~CBulletManager()
{
	m_Bullet.clear();
//	m_Bullet->Delete();
}

/**
* @brief :読み込んだテクスチャIDの取得
*/
void CBulletManager::SetTextureId(const int &idx)
{
	texid = idx;
	itr->SetTextureId(texid);
}

/**
* @brief	:初期化
*/
void CBulletManager::Initialize()
{
	itr->SetPlayerPos(m_PlayerPos);

	itr->Initialize();

}

/**
* @brief		:更新
* @param key	:キー情報
*/
void CBulletManager::Update(std::unique_ptr<CInput>&key)
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

/**
* @brief		:読み込んだ画像表示
* @param tex	:テクスチャクラス
*/
void CBulletManager::Render(std::unique_ptr<CTexture> &tex)
{
	for (itr = m_Bullet.begin(); itr != m_Bullet.end();){
		itr->Render(tex);
		itr++;
	}
}

/**
* @brief :削除,解放
*/
void CBulletManager::Delete()
{
	for (itr = m_Bullet.begin(); itr != m_Bullet.end();){
		itr->Delete();
		itr++;
	}
}


