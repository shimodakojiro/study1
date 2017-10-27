
#include<memory>

#include"main.h"
#include"lib/Texture.h"
#include"Game/GameBase.h"
#include"Game/Bullet/Bullet.h"

CBullet::CBullet()
{

}

CBullet::~CBullet()
{

}

void CBullet::SetTextureId(const int &idx)
{
	texid = idx;
}

void CBullet::Initialize()
{
	pos = m_PlayerPos;
	angle = 0.0f;
	velocity = Vector2(mSpeedX, mSpeedY);
	m_Frame = 0;
	m_Flag = false;
}

void CBullet::Update()
{
	m_Frame++;
	pos = pos + velocity;

	if (m_Frame >= m_MaxFrame){
		m_Flag = false;
	}
}

void CBullet::Render(std::shared_ptr<CTexture> &tex)
{
	tex->RenderTex(pos.x, pos.y, texid);
//	DrawRotaGraph(pos.x, pos.y, 1.0f, angle, texid, TRUE);
}

void CBullet::Delete()
{

}

void CBullet::BulletCreate()
{
	pos = m_PlayerPos;
	angle = 0.0f;
	m_Flag = true;
	m_Frame = 0;
}


