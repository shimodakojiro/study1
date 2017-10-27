
#ifndef __BULLET_H__
#define __BULLET_H__

class CBullet :public CGameBase
{
private:
	Vector2 m_PlayerPos;
	bool m_Flag;
	int m_Frame;
	const float mSpeedX = 20.0f;
	const float mSpeedY = 0.0f;
	const int m_MaxFrame = 3;

public:
	CBullet();
	CBullet(Vector2);
	~CBullet();
	void Initialize();
	void Update();
	void Render(std::shared_ptr<CTexture>&);
	void Delete();


	void BulletCreate();

	bool GetFlag(){ return m_Flag; }

	void SetTextureId(const int &idx);
	void SetPlayerPos(const Vector2 &playerPos){ m_PlayerPos = playerPos; }
};

#endif

