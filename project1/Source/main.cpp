
#include<memory>
#include<iostream>

#include"DxLib.h"
#include"../Header/main.h"
#include"../Header/Scene/SceneBase.h"
#include"../Header/Scene/SceneMain.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
#if 0
	if (MessageBox(NULL, "ウィンドウモードで起動しますか?", "", MB_YESNO) == IDYES)ChangeWindowMode(true);
	else ChangeWindowMode(false);
#endif
	ChangeWindowMode(true);

	//DXライブラリ初期化
	if (DxLib_Init() == -1){
		return -1;
	}

//	CSceneBase *m_scene = new CSceneTitle();
	CSceneBase *scene = new CSceneMain();

	scene->Load();
	scene->Initialize();

	do{
		ClearDrawScreen();
		scene->Update();
		scene->Render();
	} while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE));

	scene->Delete();

	delete scene;
	DxLib_End();

	return 0; 
}


