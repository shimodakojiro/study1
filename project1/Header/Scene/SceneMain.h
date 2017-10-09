
#ifndef __SCENEMAIN_H__
#define __SCENEMAIN_H__

#include"../Game/Player/Player.h"
#include"../../Header/Game/Bullet/BulletManager.h"
#include"../../Header/Game/Graphic.h"

class CSceneMain : public CSceneBase
{
private:
	std::unique_ptr<CPlayer>m_Player;
	std::unique_ptr<CBulletManager>m_BulletManager;
	std::unique_ptr<CGraphic>m_Graphic;

public:
	CSceneMain();
	~CSceneMain();

	void Load();
	void Initialize();
	void Update();
	void Render();
	void Delete();

	void SetTextureId();

};

#endif