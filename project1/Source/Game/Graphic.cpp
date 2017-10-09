
#include"DxLib.h"
#include"../../Header/Game/Graphic.h"

CGraphic::CGraphic()
{

}

CGraphic::~CGraphic()
{

}

void CGraphic::Load()
{
	m_Player = LoadGraph("../Resource/Player/player.png");
//	m_Enemy = LoadGraph();
	m_Bullet = LoadGraph("../Resource/Bullet/bullet.png");
}

