
#include"../../Header/lib/Texture.h"

/**
* @brief :�R���X�g���N�^
*/
CTexture::CTexture()
{
	for (int i = 0; i < MAX_TEX; i++){
		pTex[i].used = false;
	}
}

/**
* @brief :�f�X�g���N�^
*/
CTexture::~CTexture()
{

}

/**
* @brief :�e�N�X�`���ǂݍ���
* @param szFilename	:�t�@�C����
* @return			:�ǂݍ��񂾃t�@�C���̔ԍ�
*/
int CTexture::LoadTex(LPCTSTR filename)
{
	// ���g�p�̗v�f������
	int idx = -1;
	for (int i = 0; i < MAX_TEX; i++){
		if (pTex[i].used == false){
			idx = i;
			break;
		}
		else if (i >= MAX_TEX){
			idx = -1;
			break;
		}
	}
	if (idx < 0){
		//�}�E�X�\��
		ShowCursor(true);
		MessageBox(NULL, "maxtex(150)�𒴂��Ă��܂�", "D2dObj.cpp", NULL);
		return -1;
	}

	D3DXIMAGE_INFO iiImageInfo;
	//�u�e�N�X�`���I�u�W�F�N�g�v�̍쐬
	if (FAILED(D3DXCreateTextureFromFileEx(CApplication::GetDevice(), filename, D3DX_DEFAULT, D3DX_DEFAULT, 1, 0,
		D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT,
		0xff00ff00, &iiImageInfo, NULL, &pTex[idx].pDxTex)))
	{
		//�}�E�X�\��
		ShowCursor(true);
		MessageBox(0, "�e�N�X�`���̍쐬�Ɏ��s���܂���", "D2dObj.h", MB_OK);
		return -1;
	}

	pTex[idx].nWidth = iiImageInfo.Width;
	pTex[idx].nHeight = iiImageInfo.Height;

	DWORD x = 1;
	while ((x = x * 2) < pTex[idx].nWidth);
	pTex[idx].uv1[0] = 0;
	pTex[idx].uv1[1] = (float)pTex[idx].nWidth / (float)x;
	DWORD y = 1;
	while ((y = y * 2) < pTex[idx].nHeight);
	pTex[idx].uv2[0] = 0;
	pTex[idx].uv2[1] = (float)pTex[idx].nHeight / (float)y;

	pTex[idx].used = true;

	return idx;
}

/**
* @brief	:�e�N�X�`���̉������擾
* @param	:�t�@�C�����w�肷��ID
* @return	:�e�N�X�`���̏c��
*/
int CTexture::GetTextureWidth(int idx)
{
	return pTex[idx].nWidth;
}

/**
* @brief	:�e�N�X�`���̏c�����擾
* @param	:�t�@�C�����w�肷��ID
* @return	:�e�N�X�`���̉���
*/
int CTexture::GetTextureHeight(int idx)
{
	return pTex[idx].nHeight;
}

/**
* @brief :�l�p�`��F�w�肠��ŕ`��
* @param x1	:�����x���W
* @param y1	:�����y���W
* @param x2	:�����x���W
* @param y2	:�E���y���W
*/
void CTexture::DrawBox(float x1, float y1, float x2, float y2, D3DCOLOR color)
{
	float tmp;
	if (x1 > x2){
		tmp = x1;
		x1 = x2;
		x2 = tmp;
	}
	if (y1 > y2){
		tmp = y1;
		y1 = y2;
		y2 = tmp;
	}
	D3DXVECTOR3 vPnt[4];
	//�E��
	vPnt[0].x = x2;
	vPnt[0].y = y1;
	vPnt[0].z = 0.0f;
	//�E��
	vPnt[1] = vPnt[0];
	vPnt[1].y = y2;
	//����
	vPnt[2] = vPnt[0];
	vPnt[2].x = x1;
	//����
	vPnt[3] = vPnt[1];
	vPnt[3].x = x1;
	CUSTOM_FVF vertex[4];
	for (int i = 0; i < 4; i++){
		//���W�R�s�[
		vertex[i].pos = vPnt[i];
		vertex[i].rhw = 1.0f;
		vertex[i].color = color;
	}
	//�����_�����O
	CApplication::GetDevice()->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	//�e�N�X�`���Ȃ�
	CApplication::GetDevice()->SetTexture(0, NULL);
	//�����_�����O
	CApplication::GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertex, sizeof(CUSTOM_FVF));
}

/**
* @brief :�e�N�X�`���`��
* @param posX	:����x���W
* @param posY	:����y���W
* @param index	:�t�@�C�����w�肷��ID
*/
void CTexture::RenderTex(int posX, int posY, int index)
{
	if (index == -1){
		//�}�E�X�\��
		ShowCursor(true);
		MessageBox(NULL, "RenderTex��-1�̒l���n����܂���", "D2dObj.cpp", IDOK);
		return;
	}
	if (!pTex[index].used){//�ǂݍ���ł��Ȃ�
		return;
	};
	//scale�폜��
	float x = pTex[index].nWidth * 0.5f;//(CApplication::GetScreenSizex() / 1280.0f)
	float y = pTex[index].nHeight * 0.5f;

	DWORD vColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	D2D_TEXTURE vPoint[] = {
		{ -x, -y, 0, 1, vColor, pTex[index].uv1[0], pTex[index].uv2[0] }
		, { x, -y, 0, 1, vColor, pTex[index].uv1[1], pTex[index].uv2[0] }
		, { -x, y, 0, 1, vColor, pTex[index].uv1[0], pTex[index].uv2[1] }
		, { x, y, 0, 1, vColor, pTex[index].uv1[1], pTex[index].uv2[1] }
	};
	//angel�폜��
	float RotX = sinf(0 * D3DX_PI / 180.0f);
	float RotY = cosf(0 * D3DX_PI / 180.0f);
	for (int i = 0; i < 4; i++){
		D2D_TEXTURE *pv = &vPoint[i];
		float fX = pv->x;
		float fY = pv->y;
		pv->x = ((fX*RotY) - (fY*RotX) + posX + pTex[index].nWidth / 2) * (CApplication::GetScreenSizex() / 1280.0f);
		pv->y = ((fX*RotX) + (fY*RotY) + posY + pTex[index].nHeight / 2) * (CApplication::GetScreenSizey() / 720.0f);
	}
	//���ߏ���
	CApplication::GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	CApplication::GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	CApplication::GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//�`��
	CApplication::GetDevice()->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	CApplication::GetDevice()->SetTexture(0, pTex[index].pDxTex);
	CApplication::GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vPoint, sizeof(D2D_TEXTURE));

}

/**
* @brief :�e�N�X�`���`��
* @param posX	:����x���W
* @param posY	:����y���W
* @param index	:�t�@�C�����w�肷��ID
*/
void CTexture::RenderTex(Vector2 pos, int index)
{
	int posX = pos.x;
	int posY = pos.y;

	if (index == -1){
		//�}�E�X�\��
		ShowCursor(true);
		MessageBox(NULL, "RenderTex��-1�̒l���n����܂���", "D2dObj.cpp", IDOK);
		return;
	}
	if (!pTex[index].used){//�ǂݍ���ł��Ȃ�
		return;
	};
	//scale�폜��
	float x = pTex[index].nWidth * 0.5f;//(CApplication::GetScreenSizex() / 1280.0f)
	float y = pTex[index].nHeight * 0.5f;

	DWORD vColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	D2D_TEXTURE vPoint[] = {
		{ -x, -y, 0, 1, vColor, pTex[index].uv1[0], pTex[index].uv2[0] }
		, { x, -y, 0, 1, vColor, pTex[index].uv1[1], pTex[index].uv2[0] }
		, { -x, y, 0, 1, vColor, pTex[index].uv1[0], pTex[index].uv2[1] }
		, { x, y, 0, 1, vColor, pTex[index].uv1[1], pTex[index].uv2[1] }
	};
	//angel�폜��
	float RotX = sinf(0 * D3DX_PI / 180.0f);
	float RotY = cosf(0 * D3DX_PI / 180.0f);
	for (int i = 0; i < 4; i++){
		D2D_TEXTURE *pv = &vPoint[i];
		float fX = pv->x;
		float fY = pv->y;
		pv->x = ((fX*RotY) - (fY*RotX) + posX + pTex[index].nWidth / 2) * (CApplication::GetScreenSizex() / 1280.0f);
		pv->y = ((fX*RotX) + (fY*RotY) + posY + pTex[index].nHeight / 2) * (CApplication::GetScreenSizey() / 720.0f);
	}
	//���ߏ���
	CApplication::GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	CApplication::GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	CApplication::GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//�`��
	CApplication::GetDevice()->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	CApplication::GetDevice()->SetTexture(0, pTex[index].pDxTex);
	CApplication::GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vPoint, sizeof(D2D_TEXTURE));

}

/**
* @brief :�e�N�X�`���`��
* @param posX	:����x���W
* @param posY	:����y���W
* @param index	:�t�@�C�����w�肷��ID
* @param color	:�F
*/
void CTexture::RenderTex(int posX, int posY, int index, DWORD color)
{
	if (index == -1){
		//�}�E�X�\��
		ShowCursor(true);
		MessageBox(NULL, "RenderTex(color)��-1�̒l���n����܂���", "D2dObj.cpp", IDOK);
		return;
	}
	if (!pTex[index].used){//�ǂݍ���ł��Ȃ�
		return;
	}
	//scale�폜��
	float x = pTex[index].nWidth * 0.5f;//(CApplication::GetScreenSizex() / 1280.0f)
	float y = pTex[index].nHeight * 0.5f;

	DWORD vColor = color;
	D2D_TEXTURE vPoint[] = {
		{ -x, -y, 0, 1, vColor, pTex[index].uv1[0], pTex[index].uv2[0] }
		, { x, -y, 0, 1, vColor, pTex[index].uv1[1], pTex[index].uv2[0] }
		, { -x, y, 0, 1, vColor, pTex[index].uv1[0], pTex[index].uv2[1] }
		, { x, y, 0, 1, vColor, pTex[index].uv1[1], pTex[index].uv2[1] }
	};
	//angel�폜��
	float RotX = sinf(0 * D3DX_PI / 180.0f);
	float RotY = cosf(0 * D3DX_PI / 180.0f);
	for (int i = 0; i < 4; i++){
		D2D_TEXTURE *pv = &vPoint[i];
		float fX = pv->x;
		float fY = pv->y;
		pv->x = ((fX*RotY) - (fY*RotX) + posX + pTex[index].nWidth / 2) * (CApplication::GetScreenSizex() / 1280.0f);
		pv->y = ((fX*RotX) + (fY*RotY) + posY + pTex[index].nHeight / 2) * (CApplication::GetScreenSizey() / 720.0f);
	}
	//���ߏ���
	CApplication::GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	CApplication::GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	CApplication::GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//�`��
	CApplication::GetDevice()->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	CApplication::GetDevice()->SetTexture(0, pTex[index].pDxTex);
	CApplication::GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vPoint, sizeof(D2D_TEXTURE));

}

/**
* @brief :�e�N�X�`���`��(�A���t�@�u�����f�B���O�L��)
* @param posX	:����x���W
* @param posY	:����y���W
* @param alpha	:�A���t�@�l
* @param index	:�t�@�C�����w�肷��ID
*/
void CTexture::RenderAlphaBrendingTex(int posX, int posY, int alpha, int index)
{
	if (index == -1){
		//�}�E�X�\��
		ShowCursor(true);
		MessageBox(NULL, "RenderAlphaBrendingTex��-1�̒l���n����܂���", "D2dObj.cpp", IDOK);
		return;
	}
	if (!pTex[index].used){//�ǂݍ���ł��Ȃ�
		return;
	}
	//scale�폜��
	float x = (pTex[index].nWidth * 0.5f) * (CApplication::GetScreenSizex() / 1280.0f);
	float y = (pTex[index].nHeight * 0.5f)  * (CApplication::GetScreenSizey() / 720.0f);

	DWORD vColor = D3DCOLOR_ARGB(alpha, 255, 255, 255);
	D2D_TEXTURE vPoint[] = {
		{ -x, -y, 0, 1, vColor, pTex[index].uv1[0], pTex[index].uv2[0] }
		, { x, -y, 0, 1, vColor, pTex[index].uv1[1], pTex[index].uv2[0] }
		, { -x, y, 0, 1, vColor, pTex[index].uv1[0], pTex[index].uv2[1] }
		, { x, y, 0, 1, vColor, pTex[index].uv1[1], pTex[index].uv2[1] }
	};
	//angel�폜��
	float RotX = sinf(0 * D3DX_PI / 180.0f);
	float RotY = cosf(0 * D3DX_PI / 180.0f);
	for (int i = 0; i < 4; i++){
		D2D_TEXTURE *pv = &vPoint[i];
		float fX = pv->x;
		float fY = pv->y;
		pv->x = ((fX*RotY) - (fY*RotX) + posX + pTex[index].nWidth / 2) * (CApplication::GetScreenSizex() / 1280.0f);
		pv->y = ((fX*RotX) + (fY*RotY) + posY + pTex[index].nHeight / 2) * (CApplication::GetScreenSizey() / 720.0f);
	}

	//���ߏ���
	CApplication::GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	CApplication::GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	CApplication::GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//�`��
	CApplication::GetDevice()->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	CApplication::GetDevice()->SetTexture(0, pTex[index].pDxTex);
	CApplication::GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vPoint, sizeof(D2D_TEXTURE));

}

/**
* @brief :�e�N�X�`���`��(�X�P�[�����O����)
* @param posX	:����x���W
* @param posY	:����y���W
* @param scale	:�T�C�Y
* @param index	:�t�@�C�����w�肷��ID
*/
void CTexture::RenderTex(int posX, int posY, float scale, int index)
{
	if (index == -1){
		//�}�E�X�\��
		ShowCursor(true);
		MessageBox(NULL, "Render_Tex��-1�̒l���n����܂���", "D2dObj.cpp", IDOK);
		return;
	}
	if (!pTex[index].used){//�ǂݍ���ł��Ȃ�
		return;
	}
	//scale�폜��
	float x = pTex[index].nWidth * 0.5f * scale;
	float y = pTex[index].nHeight * 0.5f * scale;

	DWORD vColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	D2D_TEXTURE vPoint[] = {
		{ -x, -y, 0, 1, vColor, pTex[index].uv1[0], pTex[index].uv2[0] }
		, { x, -y, 0, 1, vColor, pTex[index].uv1[1], pTex[index].uv2[0] }
		, { -x, y, 0, 1, vColor, pTex[index].uv1[0], pTex[index].uv2[1] }
		, { x, y, 0, 1, vColor, pTex[index].uv1[1], pTex[index].uv2[1] }
	};
	//angel�폜��
	float RotX = sinf(0 * D3DX_PI / 180.0f);
	float RotY = cosf(0 * D3DX_PI / 180.0f);
	for (int i = 0; i < 4; i++){
		D2D_TEXTURE *pv = &vPoint[i];
		float fX = pv->x;
		float fY = pv->y;
		pv->x = ((fX*RotY) - (fY*RotX) + posX + pTex[index].nWidth / 2) * (CApplication::GetScreenSizex() / 1280.0f);
		pv->y = ((fX*RotX) + (fY*RotY) + posY + pTex[index].nHeight / 2) * (CApplication::GetScreenSizey() / 720.0f);
	}
	//���ߏ���
	CApplication::GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	CApplication::GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	CApplication::GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//�`��
	CApplication::GetDevice()->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	CApplication::GetDevice()->SetTexture(0, pTex[index].pDxTex);
	CApplication::GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vPoint, sizeof(D2D_TEXTURE));

}

/**
* @brief :�e�N�X�`���`��(�X�P�[�����O����)
* @param posX	:����x���W
* @param posY	:����y���W
* @param scale	:�X�P�[��
* @param color	:�F
* @param index	:�t�@�C�����w�肷��ID
*/
void CTexture::RenderTex(int posX, int posY, float scale, int index, DWORD color)
{
	if (index == -1){
		//�}�E�X�\��
		ShowCursor(true);
		MessageBox(NULL, "Render_Tex��-1�̒l���n����܂���", "D2dObj.cpp", IDOK);
		return;
	}
	if (!pTex[index].used){//�ǂݍ���ł��Ȃ�
		return;
	}
	//scale�폜��
	float x = pTex[index].nWidth * 0.5f * scale;
	float y = pTex[index].nHeight * 0.5f * scale;

	DWORD vColor = color;
	D2D_TEXTURE vPoint[] = {
		{ -x, -y, 0, 1, vColor, pTex[index].uv1[0], pTex[index].uv2[0] }
		, { x, -y, 0, 1, vColor, pTex[index].uv1[1], pTex[index].uv2[0] }
		, { -x, y, 0, 1, vColor, pTex[index].uv1[0], pTex[index].uv2[1] }
		, { x, y, 0, 1, vColor, pTex[index].uv1[1], pTex[index].uv2[1] }
	};
	//angel�폜��
	float RotX = sinf(0 * D3DX_PI / 180.0f);
	float RotY = cosf(0 * D3DX_PI / 180.0f);
	for (int i = 0; i < 4; i++){
		D2D_TEXTURE *pv = &vPoint[i];
		float fX = pv->x;
		float fY = pv->y;
		pv->x = ((fX*RotY) - (fY*RotX) + posX + pTex[index].nWidth / 2) * (CApplication::GetScreenSizex() / 1280.0f);
		pv->y = ((fX*RotX) + (fY*RotY) + posY + pTex[index].nHeight / 2) * (CApplication::GetScreenSizey() / 720.0f);
	}
	//���ߏ���
	CApplication::GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	CApplication::GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	CApplication::GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//�`��
	CApplication::GetDevice()->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	CApplication::GetDevice()->SetTexture(0, pTex[index].pDxTex);
	CApplication::GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vPoint, sizeof(D2D_TEXTURE));

}

/**
* @brief :�e�N�X�`���`��(���̃T�C�Y)
* @param posX	:����x���W
* @param posY	:����y���W
* @param index	:�t�@�C�����w�肷��ID
*/
void CTexture::RenderNormTex(int posX, int posY, int index)
{
	if (index == -1){
		//�}�E�X�\��
		ShowCursor(true);
		MessageBox(NULL, "RenderNormTex��-1�̒l���n����܂���", "D2dObj.cpp", IDOK);
		return;
	}
	if (!pTex[index].used){//�ǂݍ���ł��Ȃ�
		return;
	}
	//scale�폜��
	float x = pTex[index].nWidth * 0.5f;//(CApplication::GetScreenSizex() / 1280.0f)
	float y = pTex[index].nHeight * 0.5f;

	DWORD vColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	D2D_TEXTURE vPoint[] = {
		{ -x, -y, 0, 1, vColor, pTex[index].uv1[0], pTex[index].uv2[0] }
		, { x, -y, 0, 1, vColor, pTex[index].uv1[1], pTex[index].uv2[0] }
		, { -x, y, 0, 1, vColor, pTex[index].uv1[0], pTex[index].uv2[1] }
		, { x, y, 0, 1, vColor, pTex[index].uv1[1], pTex[index].uv2[1] }
	};
	//angel�폜��
	float RotX = sinf(0 * D3DX_PI / 180.0f);
	float RotY = cosf(0 * D3DX_PI / 180.0f);
	for (int i = 0; i < 4; i++){
		D2D_TEXTURE *pv = &vPoint[i];
		float fX = pv->x;
		float fY = pv->y;
		pv->x = ((fX*RotY) - (fY*RotX) + posX + pTex[index].nWidth / 2) * (CApplication::GetScreenSizex() / 1280.0f);
		pv->y = ((fX*RotX) + (fY*RotY) + posY + pTex[index].nHeight / 2) * (CApplication::GetScreenSizey() / 720.0f);
	}
	//���ߏ���
	CApplication::GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	CApplication::GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	CApplication::GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//�`��
	CApplication::GetDevice()->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	CApplication::GetDevice()->SetTexture(0, pTex[index].pDxTex);
	CApplication::GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vPoint, sizeof(D2D_TEXTURE));

}

/**
* @brief :�e�N�X�`���`��(���̃T�C�Y,�X�P�[�����O����)
* @param posX	:����x���W
* @param posY	:����y���W
* @param scale	:�X�P�[��
* @param index	:�t�@�C�����w�肷��ID
*/
void CTexture::RenderNormTex(int posX, int posY, float scale, int index)
{
	if (index == -1){
		//�}�E�X�\��
		ShowCursor(true);
		MessageBox(NULL, "Render_Tex��-1�̒l���n����܂���", "D2dObj.cpp", IDOK);
		return;
	}
	if (!pTex[index].used){//�ǂݍ���ł��Ȃ�
		return;
	}
	//scale�폜��
	float x = pTex[index].nWidth * 0.5f * scale;
	float y = pTex[index].nHeight * 0.5f * scale;

	DWORD vColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	D2D_TEXTURE vPoint[] = {
		{ -x, -y, 0, 1, vColor, pTex[index].uv1[0], pTex[index].uv2[0] }
		, { x, -y, 0, 1, vColor, pTex[index].uv1[1], pTex[index].uv2[0] }
		, { -x, y, 0, 1, vColor, pTex[index].uv1[0], pTex[index].uv2[1] }
		, { x, y, 0, 1, vColor, pTex[index].uv1[1], pTex[index].uv2[1] }
	};
	//angel�폜��
	float RotX = sinf(0 * D3DX_PI / 180.0f);
	float RotY = cosf(0 * D3DX_PI / 180.0f);
	for (int i = 0; i < 4; i++){
		D2D_TEXTURE *pv = &vPoint[i];
		float fX = pv->x;
		float fY = pv->y;
		pv->x = (fX*RotY) - (fY*RotX) + posX + pTex[index].nWidth / 2;
		pv->y = (fX*RotX) + (fY*RotY) + posY + pTex[index].nHeight / 2;
	}
	//���ߏ���
	CApplication::GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	CApplication::GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	CApplication::GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//�`��
	CApplication::GetDevice()->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	CApplication::GetDevice()->SetTexture(0, pTex[index].pDxTex);
	CApplication::GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vPoint, sizeof(D2D_TEXTURE));

}
