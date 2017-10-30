#ifndef __INPUT_H__
#define __INPUT_H__

#include<Windows.h>
#include"../../Header/main.h"

class CInput
{
private:
	//*************
	//入力関係
	//*************
	int now;
	int old;
	int down;
	int up;

	//************
	//マウス
	//************
	POINT mMousePnt;
	POINT mOlpMousePnt;
	bool mMouseActive;

public:
	CInput();
	~CInput();
	//************
	//入力関係
	//************
	void CheackInputState();
	bool GetInputNow(const int&);	//現在の入力
	bool GetInputUp(const int&);	//離した1フレーム
	bool GetInputDown(const int&);	//押した1フレーム
	bool GetEsckeystate();
	POINT GetMousePosition();

	//キーチェック
	const int InputUp = 0x0008;
	const int InputDown = 0x0001;
	const int InputLeft = 0x0002;
	const int InputRight = 0x0004;
	const int InputSpc = 0x0010;
	const int InputEsc = 0x0020;
	const int InputRet = 0x0080;
	const int InputSft = 0x0040;
	const int InputR = 0x4000;
	const int InputA = 0x0800;
	const int InputZ = 0x0100;
	const int InputW = 0x8000;
	const int InputS = 0x1000;
	const int InputX = 0x0200;
	const int InputD = 0x2000;
	const int InputC = 0x0400;

	// マウスボタン定数
	const int InputMouseLeft = 0x00010000;	// マウス左ボタン
	const int InputMouseRight = 0x00020000;	// マウス右ボタン
	const int InputMouseMiddle = 0x00040000;// マウス中央ボタン

	void SetMousePosition();	//位置指定
	//指定の範囲内にマウスがあればtrueを返す
	bool CheackMousePosition(float minX, float minY, float maxX, float maxY);
	bool GetMouseMove(const int&);	//マウスの移動量
	float GetMouseXVec();			//マウスのx移動量
	float GetMouseYVec();			//マウスのY移動量

	enum MousePoint{
		nLeft,
		nRight,
		nUp,
		nDown
	};
};

#endif