#ifndef __ENEMY_H__
#define __ENEMY_H__

#include"../GameBase.h"

class CEnemy : public CGameBase
{
private:
	const float m_Speed = 3.0f;
	const float m_StartX = 100.0f;
	const float m_StartY = 200.0f;

public:
	CEnemy();
	~CEnemy();

	void Initialize();
	void Update();
	void Render(const std::unique_ptr<CTexture>&);
	//	void Render();
	void Delete();

	void SetTextureId(const int &idx);
	void SetPosition(const Vector2 &pos);

};

#endif
