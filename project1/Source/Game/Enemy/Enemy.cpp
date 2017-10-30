
#include<math.h>

#include"main.h"
#include"Game/GameBase.h"
#include"lib/Texture.h"
#include"lib/Input.h"
#include"Game/Enemy/Enemy.h"

/**
* @brief :コンストラクタ
*/
CEnemy::CEnemy()
{

}

/**
* @brief :デストラクタ
*/
CEnemy::~CEnemy()
{

}

/**
* @brief :読み込んだテクスチャIDの取得
*/
void CEnemy::SetTextureId(const int &idx)
{
	texid = idx;
}

/**
* @brief		:座標セット
* @param pos	:指定の座標
*/
void CEnemy::SetPosition(const Vector2 &pos)
{
	this->pos = pos;
}

/**
* @brief :初期化
*/
void CEnemy::Initialize()
{
	pos = Vector2(100, 100);
	velocity = Vector2(0.0f, 0.0f);
	angle = 0.0;

}

/**
* @brief :更新
*/
void CEnemy::Update()
{

}

/**
* @brief :読み込んだ画像表示
* @param tex	:テクスチャクラス
*/
void CEnemy::Render(const std::unique_ptr<CTexture> &tex)
{
	tex->RenderTex(pos, texid);
}

/**
* @brief :削除
*/
void CEnemy::Delete()
{

}

