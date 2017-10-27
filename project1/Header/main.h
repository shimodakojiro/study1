/*
#ifndef __MAIN_H__
#define __MAIN_H__

//assert()

#endif


*/

#ifndef __WORK_H__
#define __WORK_H__

#include<d3d9.h>
#include<d3dx9.h>
#include <dinput.h>
#include <tchar.h>
#include <memory>


#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

#include"../Header/Scene/SceneBase.h"

class CApplication
{
private:
	//	シーン
	static CSceneBase *scene;

	//
	LPDIRECT3D9					pD3D;			//Direct3D9
	LPDIRECTINPUT8				pDI;			//DirectInput
	LPDIRECTINPUTDEVICE8		pDIDevice;		//InputDevice

	static HWND hWnd;
	static LPDIRECT3DDEVICE9	pd3dDevice;		//DirectDevice
	static float aspect;
	static bool endflag;
	//幅
	static float screen_x;
	static float screen_y;
	//左上の座標
	static float window_x;
	static float window_y;
	//フルスクリーンか
	static bool full_flag;

public:
	CApplication();
	~CApplication();

	bool ProcessEvent(MSG*);
	HRESULT InitD3DWindow(LPCTSTR, float w = 1280.0f, float h = 720.0f);

	void Initialize();
	bool Update();
	void Render();

	//(0)title(1)main(2)clear(3)gameover(4)end
	static enum class nSCENE
	{
		TITLE,
		MAIN,
		END,
		NONE,//初期化用
	};

	static void ChangeScene(CSceneBase* newScene)
	{
		//	現在のシーン解放
		if (scene != NULL) delete scene;
		//	シーンの切り替え＆初期化
		scene = newScene;
		scene->Load();
		scene->Initialize();
	}

	static LPDIRECT3DDEVICE9 GetDevice(){ return pd3dDevice; }
	static HWND GetHWnd(){ return hWnd; }
	static bool GetEndflag(){ return endflag; }
	static float GetAspect(){ return aspect; }
	static float GetScreenCenx(){ return window_x + screen_x / 2; }
	static float GetScreenCeny(){ return window_y + screen_y / 2; }
	static float GetScreenPosx(){ return window_x; }
	static float GetScreenPosy(){ return window_y; }
	static float GetScreenSizex(){ return screen_x; }
	static float GetScreenSizey(){ return screen_y; }
	static bool GetFullScreen(){ return full_flag; }
};


#endif