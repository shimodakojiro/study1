
#include"../../Header/lib/Input.h"

/**
* @brief :�R���X�g���N�^
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

	//��ʂ̒��S�Ƀ}�E�X���Z�b�g
	SetCursorPos(CApplication::GetScreenCenx(), CApplication::GetScreenCeny());
	//�}�E�X�\��
	ShowCursor(1);
}

/**
* @brief :�f�X�g���N�^
*/
CInput::~CInput()
{
}

/**
* @brief :���͂��ꂽ���擾
*/
void CInput::CheackInputState()
{
	BYTE			cKeyBuf[256];

	int nKeyState = 0;
	old = now;					//��ԕۑ�
	GetKeyboardState(cKeyBuf);	//�L�[�{�[�h���͏��擾

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

	// �}�E�X
	if (mMouseActive) {
		if ((cKeyBuf[VK_LBUTTON] & 0x80)) nKeyState |= InputMouseLeft;
		if ((cKeyBuf[VK_RBUTTON] & 0x80)) nKeyState |= InputMouseRight;
		if ((cKeyBuf[VK_MBUTTON] & 0x80)) nKeyState |= InputMouseMiddle;
	}
	now = nKeyState;
}

/**
* @brief :���݂̓���
* @param snKeyState	:�L�[���
* @return :����or���s
*/
bool CInput::GetInputNow(const int &nKeyState)
{
	if (now & nKeyState)
		return true;
	else return false;
}

/**
* @brief :�L�[�𗣂����u��
* @param snKeyState	:�L�[���
* @return :����or���s
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
* @brief :�L�[���������u��
* @param snKeyState	:�L�[���
* @return :����or���s
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
* @brief :ESC�L�[�̓��͂�����ΏI��
* @return :����or���s
*/
bool CInput::GetEsckeystate()
{
	if (GetInputNow(InputEsc)){
		return false;
	}
	return true;
}

/**
* @brief :�}�E�X�ʒu�Œ�
*/
void CInput::SetMousePosition()
{
	if (!mMouseActive) return;					//�������`�F�b�N
	if (!GetCursorPos(&mOlpMousePnt)) return;	//�X�V�O��pos
	if (!GetCursorPos(&mMousePnt)) return;		//�X�V���pos

	float x, y;
	//��ʂ̒��S�擾
	x = CApplication::GetScreenCenx();
	y = CApplication::GetScreenCeny();

	mMousePnt.x = x;
	mMousePnt.y = y;

	SetCursorPos(x, y);
}

/**
* @brief :�}�E�X�ړ��ʒu
* @param mVec	:�}�E�X�ړ��ʒu
* @return :����or���s
*/
bool CInput::GetMouseMove(const int &mVec)
{
	bool result = false;
	switch (mVec){
	case nLeft://��
		if (mOlpMousePnt.x > mMousePnt.x){
			result = true;
		}
		break;
	case nRight://�E
		if (mOlpMousePnt.x < mMousePnt.x){
			result = true;
		}
		break;
	case nUp://��
		if (mOlpMousePnt.y < mMousePnt.y){
			result = true;
		}
		break;
	case nDown://��
		if (mOlpMousePnt.y > mMousePnt.y){
			result = true;
		}
		break;
	}
	return result;
}

/**
* @brief :�����̈ʒu�Ƀ}�E�X�����邩�ǂ���
* @param minX	:�}�E�X�w��ʒu��
* @param minY	:�}�E�X�w��ʒu��
* @param maxX	:�}�E�X�w��ʒu�E
* @param maxY	:�}�E�X�w��ʒu��
* @return :����or���s
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
* @brief :�}�E�X��X���̈ړ��ʎ擾
* @return :�}�E�X��X���̈ړ���
*/
float CInput::GetMouseXVec()
{
	return (mOlpMousePnt.x - mMousePnt.x) / 680.0f;
}

/**
* @brief :�}�E�X��Y���̈ړ��ʎ擾
* @return :�}�E�X��Y���̈ړ���
*/
float CInput::GetMouseYVec()
{
	return (mOlpMousePnt.y - mMousePnt.y) / 740.0f;
}

/**
* @brief :�}�E�X�ʒu�擾
* @return :�}�E�X�̍��W
*/
POINT CInput::GetMousePosition()
{
	POINT		MousePnt;
	GetCursorPos(&MousePnt);
	ScreenToClient(CApplication::GetHWnd(), &MousePnt);

	return MousePnt;
}





