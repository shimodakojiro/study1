
#ifndef __SCENEBASE_H__
#define __SCENEBASE_H__

class CSceneBase
{
public:
	//	生成・解放
	CSceneBase(){}
	virtual ~CSceneBase(){}
	//	初期化
	virtual void Load(){}
	virtual void Initialize(){}
	//	更新・描画
	virtual bool KeyState(){ return true; }
	virtual bool Update(){ return true; }
	virtual void Render(){}
	virtual void Delete(){}
};

#endif
