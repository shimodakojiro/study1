#ifndef __INPUT_H__
#define __INPUT_H__

#include<Windows.h>
#include"../../Header/main.h"

class CInput
{
private:
	//*************
	//���͊֌W
	//*************
	int now;
	int old;
	int down;
	int up;

	//************
	//�}�E�X
	//************
	POINT mMousePnt;
	POINT mOlpMousePnt;
	bool mMouseActive;

public:
	CInput();
	~CInput();
	//************
	//���͊֌W
	//************
	void CheackInputState();
	bool GetInputNow(const int&);	//���݂̓���
	bool GetInputUp(const int&);	//������1�t���[��
	bool GetInputDown(const int&);	//������1�t���[��
	bool GetEsckeystate();
	POINT GetMousePosition();

	//�L�[�`�F�b�N
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

	// �}�E�X�{�^���萔
	const int InputMouseLeft = 0x00010000;	// �}�E�X���{�^��
	const int InputMouseRight = 0x00020000;	// �}�E�X�E�{�^��
	const int InputMouseMiddle = 0x00040000;// �}�E�X�����{�^��

	void SetMousePosition();	//�ʒu�w��
	//�w��͈͓̔��Ƀ}�E�X�������true��Ԃ�
	bool CheackMousePosition(float minX, float minY, float maxX, float maxY);
	bool GetMouseMove(const int&);	//�}�E�X�̈ړ���
	float GetMouseXVec();			//�}�E�X��x�ړ���
	float GetMouseYVec();			//�}�E�X��Y�ړ���

	enum MousePoint{
		nLeft,
		nRight,
		nUp,
		nDown
	};
};

#endif