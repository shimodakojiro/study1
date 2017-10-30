
#include<memory>

#include"main.h"
#include"lib/Texture.h"
#include"Game/GameBase.h"
#include"Game/Bullet/Bullet.h"

/**
* @brief :コンストラクタ
*/
CBullet::CBullet()
{

}

/**
* @brief :デストラクタ
*/
CBullet::~CBullet()
{

}

/**
* @brief :読み込んだテクスチャIDの取得
*/
void CBullet::SetTextureId(const int &idx)
{
	texid = idx;
}

/**
* @brief :初期化
*/
void CBullet::Initialize()
{
	pos = m_PlayerPos;
	angle = 0.0f;
	velocity = Vector2(mSpeedX, mSpeedY);
	m_Frame = 0;
	m_Flag = false;
}

/**
* @brief :更新
*/
void CBullet::Update()
{
	m_Frame++;
	pos = pos + velocity;

	if (m_Frame >= m_MaxFrame){
		m_Flag = false;
	}
}

/**
* @brief		:読み込んだ画像表示
* @param tex	:テクスチャクラス
*/
void CBullet::Render(std::unique_ptr<CTexture> &tex)
{
	tex->RenderTex(pos, texid);
}

/**
* @brief :削除
*/
void CBullet::Delete()
{

}

/**
* @brief :発射時の弾初期化
*/
void CBullet::BulletCreate()
{
	pos = m_PlayerPos;
	angle = 0.0f;
	m_Flag = true;
	m_Frame = 0;
}


