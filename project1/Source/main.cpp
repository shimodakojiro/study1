/*
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

	std::unique_ptr<CSceneBase>scene;
//	scene = std::make_unique<CSceneTitle>();
	scene = std::make_unique<CSceneMain>();

	scene->Load();
	scene->Initialize();

	do{
		ClearDrawScreen();
		scene->Update();
		scene->Render();
	} while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE));

	scene->Delete();

	DxLib_End();

	return 0; 
}


*/


#include"../Header/main.h"
#include"../Header/Scene/SceneMain.h"

LPDIRECT3DDEVICE9 CApplication::pd3dDevice = nullptr;
HWND CApplication::hWnd = nullptr;
bool CApplication::endflag = true;
float CApplication::aspect = 0;
float CApplication::screen_x = 0;
float CApplication::screen_y = 0;
float CApplication::window_x = 0;
float CApplication::window_y = 0;
bool CApplication::full_flag = false;
CSceneBase *CApplication::scene = nullptr;


//WinMain関数
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, INT)
{
	MSG msg = { 0 };
//	CApplication *app = new CApplication();

	std::unique_ptr<CApplication>app;
	app = std::make_unique<CApplication>();

	HRESULT hr_ = E_FAIL;
//	hr_ = app->InitD3DWindow("2017");
	hr_ = app->InitD3DWindow("2017", 620, 480);

	if (hr_ == E_FAIL)goto ERROR_;

	app->Initialize();

	//メッセージループ
	while (app->ProcessEvent(&msg) && app->GetEndflag()){
		//更新,描画
		if(app->Update())app->Render();
	}
ERROR_:
	//ウィンドウクラスを削除し、そのクラスのために使われていたメモリを解放
	UnregisterClass("D3D Window Class", GetModuleHandle(NULL));
	return 0;
}

//ウィンドウプロシージャ
LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam){
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

bool CApplication::ProcessEvent(MSG *msg)
{
	while (PeekMessage(msg, NULL, 0, 0, PM_NOREMOVE)){
		if (!GetMessage(msg, NULL, 0, 0)) {
			return false;
		}
		TranslateMessage(msg);
		DispatchMessage(msg);
	}
	return true;
}


//ウィンドウモードでD3D初期化
HRESULT CApplication::InitD3DWindow(LPCTSTR wintitle, float w, float h)
{
	aspect = (float)w / (float)h;
	endflag = true;
	//サイズ
	screen_x = w;
	screen_y = h;
	//座標
	window_x = (GetSystemMetrics(SM_CXSCREEN) - screen_x) / 2;
	window_y = (GetSystemMetrics(SM_CYSCREEN) - screen_y) / 2;

	//ウィンドウクラス作成
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		_T("D3D Window Class"), NULL };
	RegisterClassEx(&wc);

	//ウィンドウ作成
	hWnd = CreateWindow(_T("D3D Window Class"), wintitle,
		WS_OVERLAPPED | WS_SYSMENU, window_x, window_y, w, h,
		NULL, NULL, wc.hInstance, NULL);

	// D3D9の作成
	if ((pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)return E_FAIL;

	// D3Dデバイスの作成（可能ならハードウェアT&Lを使用）
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

#if 0
	if (MessageBox(NULL, "フルスクリーンモードで起動しますか?", "", MB_YESNO) == IDYES){
		full_flg = true;
		screen_x = GetSystemMetrics(SM_CXSCREEN);
		screen_y = GetSystemMetrics(SM_CYSCREEN);
		D3DDISPLAYMODE dispmode;
		//ディスプレイの情報を取得
		pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &dispmode);
		d3dpp.Windowed = false;
		d3dpp.BackBufferWidth = GetSystemMetrics(SM_CXSCREEN);
		d3dpp.BackBufferHeight = GetSystemMetrics(SM_CYSCREEN);
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.BackBufferFormat = dispmode.Format;
		d3dpp.FullScreen_RefreshRateInHz = dispmode.RefreshRate;
	}
#endif

	if (FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
		hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &pd3dDevice))) {
		if (FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
			hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &pd3dDevice))) {
			return E_FAIL;
		}
	}
	//Zバッファをオン
	pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	ShowWindow(hWnd, SW_SHOWDEFAULT);

	//DirectInputの初期化
	if (FAILED(DirectInput8Create(wc.hInstance, DIRECTINPUT_VERSION,
		IID_IDirectInput8, (void**)&pDI, NULL)))
		return E_FAIL;
	if (FAILED(pDI->CreateDevice(GUID_SysKeyboard, &pDIDevice, NULL)))
		return E_FAIL;
	pDIDevice->SetDataFormat(&c_dfDIKeyboard);
	pDIDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	return S_OK;
}

CApplication::CApplication()
{
	pD3D = nullptr;
	pd3dDevice = nullptr;
	pDI = nullptr;
	pDIDevice = nullptr;

	scene = new CSceneBase();
}

void CApplication::Initialize()
{
//	ChangeScene(new CSceneTitle());
	ChangeScene(new CSceneMain());
}

bool CApplication::Update()
{
	endflag = scene->Update();
	return true;
}

void CApplication::Render()
{
	if (SUCCEEDED(pd3dDevice->BeginScene())){
		pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);
		scene->Render();
	}
	pd3dDevice->EndScene();
	pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

/**
* @brief :解放
*/
CApplication::~CApplication()
{
	delete scene;

	if (pd3dDevice != nullptr) pd3dDevice->Release();
	if (pD3D != nullptr) pD3D->Release();

	if (pDIDevice != nullptr) {
		pDIDevice->Unacquire();
		pDIDevice->Release();
	}
	if (pDI != nullptr) pDI->Release();
}


