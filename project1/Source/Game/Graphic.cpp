
#include"../../Header/main.h"
#include"../../Header/lib/Texture.h"
#include"../../Header/Game/Graphic.h"

/**
* @brief :�R���X�g���N�^
*/
CGraphic::CGraphic()
{

}

/**
* @brief :�f�X�g���N�^
*/
CGraphic::~CGraphic()
{

}

/**
* @brief :�摜�ǂݍ���
* @param tex	:�e�N�X�`���N���X
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

