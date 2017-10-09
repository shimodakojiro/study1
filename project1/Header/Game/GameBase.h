
#ifndef __GAMEBASE_H__
#define __GAMEBASE_H__

#define PI 3.141592653589793

class Vector2
{
private:
public:
	float x;
	float y;

	Vector2(){}

	Vector2(float x,float y){
		this->x = x;
		this->y = y;
	}

	Vector2 operator +(Vector2 vec){
		Vector2 ret;
		ret.x = this->x + vec.x;
		ret.y = this->y + vec.y;
		return ret;
	}
};

class CGameBase
{
private:

protected:
	Vector2 pos;
	Vector2 velocity;
	float angle;
	int texid;

public:
	CGameBase(){}
	virtual ~CGameBase(){}

	virtual void Initialize(){}
	virtual void Update(){}
	virtual void Render(){}
	virtual void Delete(){}

	virtual void SetTextureId(const int &idx){}

	virtual Vector2 GetPos(){ return pos; }
	virtual Vector2 GetVelocity(){ return velocity; }
	virtual float GetAngle(){ return angle; }

public:
};

#endif
