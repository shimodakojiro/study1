
#include<math.h>

#include"main.h"
#include"Game/GameBase.h"
#include"lib/Texture.h"
#include"lib/Input.h"
#include"Game/Player/Player.h"

CPlayer::CPlayer()
{

}

CPlayer::~CPlayer()
{

}

void CPlayer::SetTextureId(const int &idx)
{
	texid = idx;
	int y = 0;
}

void CPlayer::Initialize()
{
	pos = Vector2(m_StartX, m_StartY);
	angle = 0.0f;
	velocity.x = 0.0f;
	velocity.y = 0.0f;
	angle = 0.0f;

}

void CPlayer::Update(const std::shared_ptr<CInput> &key)
{
	velocity = Vector2(0.0f,0.0f);

	if (key->GetInputNow(key->InputW)){
		velocity.y = -m_Speed;
	}
	if (key->GetInputNow(key->InputS)){
		velocity.y = m_Speed;
	}
	if (key->GetInputNow(key->InputA)){
		velocity.x = -m_Speed;
	}
	if (key->GetInputNow(key->InputD)){
		velocity.x = m_Speed;
	}

	pos.x += velocity.x;
	pos.y += velocity.y;

	pos = pos + velocity;

	if (pos.x <= 0)pos.x = 0;
	if (pos.x >= 600)pos.x = 600;
	if (pos.y <= 0)pos.y = 0;
	if (pos.y >= 600)pos.y = 600;
}

void CPlayer::Render(const std::shared_ptr<CTexture> &tex)
{
	tex->RenderTex(pos.x, pos.y, texid);
//	DrawRotaGraph(pos.x, pos.y, 1.0f, angle, texid, TRUE);
}

void CPlayer::Delete()
{

}

