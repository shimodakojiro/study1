
#include"DxLib.h"
#include"../../Header/Game/GameBase.h"
#include"../../Header/Game/Bullet/Bullet.h"

CBullet::CBullet()
{

}

CBullet::~CBullet()
{
	DeleteGraph(texid);
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

void CBullet::Render()
{
	DrawRotaGraph(pos.x, pos.y, 1.0f, angle, texid, TRUE);
}

void CBullet::Delete()
{
	DeleteGraph(texid);
}


void CBullet::BulletCreate()
{
	pos = m_PlayerPos;
	angle = 0.0f;
	m_Flag = true;
	m_Frame = 0;
}


