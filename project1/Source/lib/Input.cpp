
#include"../../Header/lib/Input.h"

/**
* @brief :コンストラクタ
*/
CInput::CInput()
{
	now = 0;
	old = 0;
	down = 0;
	up = 0;
	mMouseActive = true;
	mMousePnt.x = 0;
	mMousePnt.y = 0;
	mOlpMousePnt.x = 0;
	mOlpMousePnt.y = 0;

	//画面の中心にマウスをセット
	SetCursorPos(CApplication::GetScreenCenx(), CApplication::GetScreenCeny());
	//マウス表示
	ShowCursor(1);
}

/**
* @brief :デストラクタ
*/
CInput::~CInput()
{
}

/**
* @brief :入力された情報取得
*/
void CInput::CheackInputState()
{
	BYTE			cKeyBuf[256];

	int nKeyState = 0;
	old = now;					//状態保存
	GetKeyboardState(cKeyBuf);	//キーボード入力情報取得

	if ((cKeyBuf[VK_NUMPAD2] & 0x80) || (cKeyBuf[VK_DOWN] & 0x80)) nKeyState |= InputDown;
	if ((cKeyBuf[VK_NUMPAD4] & 0x80) || (cKeyBuf[VK_LEFT] & 0x80)) nKeyState |= InputLeft;
	if ((cKeyBuf[VK_NUMPAD6] & 0x80) || (cKeyBuf[VK_RIGHT] & 0x80)) nKeyState |= InputRight;
	if ((cKeyBuf[VK_NUMPAD8] & 0x80) || (cKeyBuf[VK_UP] & 0x80)) nKeyState |= InputUp;

	if ((cKeyBuf[VK_SPACE] & 0x80)) nKeyState |= InputSpc;
	if ((cKeyBuf[VK_ESCAPE] & 0x80)) nKeyState |= InputEsc;
	if ((cKeyBuf[VK_RETURN] & 0x80)) nKeyState |= InputRet;
	if ((cKeyBuf[VK_SHIFT] & 0x80)) nKeyState |= InputSft;

	if ((cKeyBuf['Z'] & 0x80)) nKeyState |= InputZ;
	if ((cKeyBuf['X'] & 0x80)) nKeyState |= InputX;
	if ((cKeyBuf['C'] & 0x80)) nKeyState |= InputC;
	if ((cKeyBuf['A'] & 0x80)) nKeyState |= InputA;
	if ((cKeyBuf['S'] & 0x80)) nKeyState |= InputS;
	if ((cKeyBuf['D'] & 0x80)) nKeyState |= InputD;
	if ((cKeyBuf['R'] & 0x80)) nKeyState |= InputR;
	if ((cKeyBuf['W'] & 0x80)) nKeyState |= InputW;

	// マウス
	if (mMouseActive) {
		if ((cKeyBuf[VK_LBUTTON] & 0x80)) nKeyState |= InputMouseLeft;
		if ((cKeyBuf[VK_RBUTTON] & 0x80)) nKeyState |= InputMouseRight;
		if ((cKeyBuf[VK_MBUTTON] & 0x80)) nKeyState |= InputMouseMiddle;
	}
	now = nKeyState;
}

/**
* @brief :現在の入力
* @param snKeyState	:キー情報
* @return :成功or失敗
*/
bool CInput::GetInputNow(const int &nKeyState)
{
	if (now & nKeyState)
		return true;
	else return false;
}

/**
* @brief :キーを離した瞬間
* @param snKeyState	:キー情報
* @return :成功or失敗
*/
bool CInput::GetInputUp(const int &nKeyState)
{
	down = (now^old)&old;
	if (down & nKeyState){
		return true;
	}
	return false;
}

/**
* @brief :キーを押した瞬間
* @param snKeyState	:キー情報
* @return :成功or失敗
*/
bool CInput::GetInputDown(const int &nKeyState)
{
	up = (now^old)&now;
	if (up & nKeyState){
		return true;
	}
	return false;
}

/**
* @brief :ESCキーの入力があれば終了
* @return :成功or失敗
*/
bool CInput::GetEsckeystate()
{
	if (GetInputNow(InputEsc)){
		return false;
	}
	return true;
}

/**
* @brief :マウス位置固定
*/
void CInput::SetMousePosition()
{
	if (!mMouseActive) return;					//初期化チェック
	if (!GetCursorPos(&mOlpMousePnt)) return;	//更新前のpos
	if (!GetCursorPos(&mMousePnt)) return;		//更新後のpos

	float x, y;
	//画面の中心取得
	x = CApplication::GetScreenCenx();
	y = CApplication::GetScreenCeny();

	mMousePnt.x = x;
	mMousePnt.y = y;

	SetCursorPos(x, y);
}

/**
* @brief :マウス移動位置
* @param mVec	:マウス移動位置
* @return :成功or失敗
*/
bool CInput::GetMouseMove(const int &mVec)
{
	bool result = false;
	switch (mVec){
	case nLeft://左
		if (mOlpMousePnt.x > mMousePnt.x){
			result = true;
		}
		break;
	case nRight://右
		if (mOlpMousePnt.x < mMousePnt.x){
			result = true;
		}
		break;
	case nUp://上
		if (mOlpMousePnt.y < mMousePnt.y){
			result = true;
		}
		break;
	case nDown://下
		if (mOlpMousePnt.y > mMousePnt.y){
			result = true;
		}
		break;
	}
	return result;
}

/**
* @brief :引数の位置にマウスがあるかどうか
* @param minX	:マウス指定位置左
* @param minY	:マウス指定位置上
* @param maxX	:マウス指定位置右
* @param maxY	:マウス指定位置下
* @return :成功or失敗
*/
bool CInput::CheackMousePosition(float minX, float minY, float maxX, float maxY)
{
	POINT mousePos;
	mousePos = GetMousePosition();
	minX *= CApplication::GetScreenSizex() / 1280.0f;	minY *= CApplication::GetScreenSizey() / 720.0f;
	maxX *= CApplication::GetScreenSizex() / 1280.0f;	maxY *= CApplication::GetScreenSizey() / 720.0f;
	if (mousePos.x >= minX && mousePos.y >= minY && mousePos.x <= maxX && mousePos.y <= maxY){
		return true;
	}
	return false;
}

/**
* @brief :マウスのX軸の移動量取得
* @return :マウスのX軸の移動量
*/
float CInput::GetMouseXVec()
{
	return (mOlpMousePnt.x - mMousePnt.x) / 680.0f;
}

/**
* @brief :マウスのY軸の移動量取得
* @return :マウスのY軸の移動量
*/
float CInput::GetMouseYVec()
{
	return (mOlpMousePnt.y - mMousePnt.y) / 740.0f;
}

/**
* @brief :マウス位置取得
* @return :マウスの座標
*/
POINT CInput::GetMousePosition()
{
	POINT		MousePnt;
	GetCursorPos(&MousePnt);
	ScreenToClient(CApplication::GetHWnd(), &MousePnt);

	return MousePnt;
}





