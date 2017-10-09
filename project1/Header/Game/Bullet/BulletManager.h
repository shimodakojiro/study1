
#ifndef __BULLETMANAGER_H__
#define __BULLETMANAGER_H__

#include<vector>
#include<iterator>

#include"../../Header/Game/Bullet/Bullet.h"

class CBulletManager :public CGameBase
{
private:
	std::unique_ptr<CBullet>m_Bullet;
//	std::vector<std::unique_ptr<CBullet>>m_Bullet;
//	std::vector<CBullet>::iterator itr;
	Vector2 m_PlayerPos;

	//長押し時のリピートカウンタ
	int m_RepCounter;
	const int m_MaxRepCounter = 30;
	bool m_RepOn;
	bool m_OldInput;
	bool m_NowInput;


public:
	CBulletManager();
	~CBulletManager();

	void SetTextureId(const int &idx);
	void Initialize();
	void Update();
	void Render();
	void Delete();

	void GetTextureId(const int &idx){ texid = idx; }

	void SetPlayerPos(const Vector2 &player_pos){ m_PlayerPos = player_pos; }
};


#endif
