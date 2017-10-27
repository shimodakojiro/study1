
#ifndef __SCENEBASE_H__
#define __SCENEBASE_H__

class CSceneBase
{
public:
	//	�����E���
	CSceneBase(){}
	virtual ~CSceneBase(){}
	//	������
	virtual void Load(){}
	virtual void Initialize(){}
	//	�X�V�E�`��
	virtual bool KeyState(){ return true; }
	virtual bool Update(){ return true; }
	virtual void Render(){}
	virtual void Delete(){}
};

#endif
