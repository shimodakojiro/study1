
#include<math.h>

#include"DxLib.h"
#include"../../Header/Game/GameBase.h"
#include"../../Header/Game/Player/Player.h"

CPlayer::CPlayer()
{

}

CPlayer::~CPlayer()
{
	DeleteGraph(texid);
}

void CPlayer::SetTextureId(const int &idx)
{
	texid = idx;
}

void CPlayer::Initialize()
{
	pos = Vector2(m_StartX, m_StartY);
	angle = 0.0f;
	velocity.x = 0.0f;
	velocity.y = 0.0f;
	angle = 0.0f;

}

void CPlayer::Update()
{
	velocity = Vector2(0.0f,0.0f);

	if (CheckHitKey(KEY_INPUT_W)){
		velocity.y = -m_Speed;
	}
	else if (CheckHitKey(KEY_INPUT_S)){
		velocity.y = m_Speed;
	}
	if (CheckHitKey(KEY_INPUT_A)){
		velocity.x = -m_Speed;
	}
	else if (CheckHitKey(KEY_INPUT_D)){
		velocity.x = m_Speed;
	}

	pos.x += velocity.x;
	pos.y += velocity.y;

	if (pos.x <= 0)pos.x = 0;
	if (pos.x >= 600)pos.x = 600;
	if (pos.y <= 0)pos.y = 0;
	if (pos.y >= 600)pos.y = 600;
}

void CPlayer::Render()
{
	DrawRotaGraph(pos.x, pos.y, 1.0f, angle, texid, TRUE);
}

void CPlayer::Delete()
{
	DeleteGraph(texid);
}

