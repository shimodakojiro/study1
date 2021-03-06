
#ifndef __SCENEMAIN_H__
#define __SCENEMAIN_H__

#include"../lib/Input.h"
#include"../lib/Texture.h"
#include"../Game/Player/Player.h"
#include"../../Header/Game/Bullet/BulletManager.h"
#include"../../Header/Game/Graphic.h"
#include"Game/Enemy/EnemyManager.h"

class CSceneMain : public CSceneBase
{
private:
//	std::shared_ptr<CInput>m_Key;
	std::unique_ptr<CInput>m_Key;
	std::unique_ptr<CTexture>m_Tex;
	std::unique_ptr<CPlayer>m_Player;
	std::unique_ptr<CBulletManager>m_BulletManager;
	std::unique_ptr<CEnemyManager>m_EnemyManager;
	std::unique_ptr<CGraphic>m_Graphic;

public:
	CSceneMain();
	~CSceneMain();

	void Load();
	void Initialize();
	bool Update();
	void Render();
	void Delete();

	bool KeyState();

	void SetTextureId();

};

#endif