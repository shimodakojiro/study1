
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include"../GameBase.h"

class CPlayer : public CGameBase
{
private:
	const float m_Speed = 0.005f;
	const float m_StartX = 100.0f;
	const float m_StartY = 200.0f;

public:
	CPlayer();
	~CPlayer();

	void Initialize();
	void Update();
	void Render();
	void Delete();
	
	void SetTextureId(const int &idx);

};

#endif
