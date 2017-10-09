
#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__

class CGraphic
{
private:
	int m_Player;
	int m_Enemy;
	int m_Bullet;
public:
	CGraphic();
	~CGraphic();
	void Load();

	int GetPlayerTextureId(){ return m_Player; }
	int GetEnemyTextureId(){ return m_Enemy; }
	int GetBulletTextureId(){ return m_Bullet; }
};

#endif
