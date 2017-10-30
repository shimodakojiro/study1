
#include"../../Header/main.h"
#include"../../Header/lib/Texture.h"
#include"../../Header/Game/Graphic.h"

/**
* @brief :コンストラクタ
*/
CGraphic::CGraphic()
{

}

/**
* @brief :デストラクタ
*/
CGraphic::~CGraphic()
{

}

/**
* @brief :画像読み込み
* @param tex	:テクスチャクラス
*/
void CGraphic::Load(const std::unique_ptr<CTexture> &tex)
{
	m_Player = tex->LoadTex("../Resource/Player/player.png");
	m_Bullet = tex->LoadTex("../Resource/Bullet/bullet.png");
	m_Enemy = tex->LoadTex("../Resource/Bullet/bullet.png");
//	m_Player = LoadGraph("../Resource/Player/player.png");
//	m_Enemy = LoadGraph();
//	m_Bullet = LoadGraph("../Resource/Bullet/bullet.png");
}

