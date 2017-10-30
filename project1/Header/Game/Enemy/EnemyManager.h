#ifndef __ENEMYMANAGER_H__
#define __ENEMYMANAGER_H__

#include"../GameBase.h"
#include"Enemy.h"

class CEnemyManager : public CGameBase
{
private:
	std::unique_ptr<CEnemy>m_Enemy;
public:
	CEnemyManager();
	~CEnemyManager();

	void Initialize();
	void Update();
	void Render(const std::unique_ptr<CTexture>&);
	//	void Render();
	void Delete();

	void SetTextureId(const int &idx);

};

#endif
