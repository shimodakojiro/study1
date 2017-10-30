
#include"../../Header/lib/Texture.h"

/**
* @brief :コンストラクタ
*/
CTexture::CTexture()
{
	for (int i = 0; i < MAX_TEX; i++){
		pTex[i].used = false;
	}
}

/**
* @brief :デストラクタ
*/
CTexture::~CTexture()
{

}

/**
* @brief :テクスチャ読み込み
* @param szFilename	:ファイル名
* @return			:読み込んだファイルの番号
*/
int CTexture::LoadTex(LPCTSTR filename)
{
	// 未使用の要素を検索
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
		//マウス表示
		ShowCursor(true);
		MessageBox(NULL, "maxtex(150)を超えています", "D2dObj.cpp", NULL);
		return -1;
	}

	D3DXIMAGE_INFO iiImageInfo;
	//「テクスチャオブジェクト」の作成
	if (FAILED(D3DXCreateTextureFromFileEx(CApplication::GetDevice(), filename, D3DX_DEFAULT, D3DX_DEFAULT, 1, 0,
		D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT,
		0xff00ff00, &iiImageInfo, NULL, &pTex[idx].pDxTex)))
	{
		//マウス表示
		ShowCursor(true);
		MessageBox(0, "テクスチャの作成に失敗しました", "D2dObj.h", MB_OK);
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
* @brief	:テクスチャの横幅を取得
* @param	:ファイルを指定するID
* @return	:テクスチャの縦幅
*/
int CTexture::GetTextureWidth(int idx)
{
	return pTex[idx].nWidth;
}

/**
* @brief	:テクスチャの縦幅を取得
* @param	:ファイルを指定するID
* @return	:テクスチャの横幅
*/
int CTexture::GetTextureHeight(int idx)
{
	return pTex[idx].nHeight;
}

/**
* @brief :四角形を色指定ありで描画
* @param x1	:左上のx座標
* @param y1	:左上のy座標
* @param x2	:左上のx座標
* @param y2	:右上のy座標
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
	//右上
	vPnt[0].x = x2;
	vPnt[0].y = y1;
	vPnt[0].z = 0.0f;
	//右下
	vPnt[1] = vPnt[0];
	vPnt[1].y = y2;
	//左上
	vPnt[2] = vPnt[0];
	vPnt[2].x = x1;
	//左下
	vPnt[3] = vPnt[1];
	vPnt[3].x = x1;
	CUSTOM_FVF vertex[4];
	for (int i = 0; i < 4; i++){
		//座標コピー
		vertex[i].pos = vPnt[i];
		vertex[i].rhw = 1.0f;
		vertex[i].color = color;
	}
	//レンダリング
	CApplication::GetDevice()->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	//テクスチャなし
	CApplication::GetDevice()->SetTexture(0, NULL);
	//レンダリング
	CApplication::GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertex, sizeof(CUSTOM_FVF));
}

/**
* @brief :テクスチャ描画
* @param posX	:左上x座標
* @param posY	:左上y座標
* @param index	:ファイルを指定するID
*/
void CTexture::RenderTex(int posX, int posY, int index)
{
	if (index == -1){
		//マウス表示
		ShowCursor(true);
		MessageBox(NULL, "RenderTexで-1の値が渡されました", "D2dObj.cpp", IDOK);
		return;
	}
	if (!pTex[index].used){//読み込んでいない
		return;
	};
	//scale削除済
	float x = pTex[index].nWidth * 0.5f;//(CApplication::GetScreenSizex() / 1280.0f)
	float y = pTex[index].nHeight * 0.5f;

	DWORD vColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	D2D_TEXTURE vPoint[] = {
		{ -x, -y, 0, 1, vColor, pTex[index].uv1[0], pTex[index].uv2[0] }
		, { x, -y, 0, 1, vColor, pTex[index].uv1[1], pTex[index].uv2[0] }
		, { -x, y, 0, 1, vColor, pTex[index].uv1[0], pTex[index].uv2[1] }
		, { x, y, 0, 1, vColor, pTex[index].uv1[1], pTex[index].uv2[1] }
	};
	//angel削除済
	float RotX = sinf(0 * D3DX_PI / 180.0f);
	float RotY = cosf(0 * D3DX_PI / 180.0f);
	for (int i = 0; i < 4; i++){
		D2D_TEXTURE *pv = &vPoint[i];
		float fX = pv->x;
		float fY = pv->y;
		pv->x = ((fX*RotY) - (fY*RotX) + posX + pTex[index].nWidth / 2) * (CApplication::GetScreenSizex() / 1280.0f);
		pv->y = ((fX*RotX) + (fY*RotY) + posY + pTex[index].nHeight / 2) * (CApplication::GetScreenSizey() / 720.0f);
	}
	//透過処理
	CApplication::GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	CApplication::GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	CApplication::GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//描画
	CApplication::GetDevice()->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	CApplication::GetDevice()->SetTexture(0, pTex[index].pDxTex);
	CApplication::GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vPoint, sizeof(D2D_TEXTURE));

}

/**
* @brief :テクスチャ描画
* @param posX	:左上x座標
* @param posY	:左上y座標
* @param index	:ファイルを指定するID
*/
void CTexture::RenderTex(Vector2 pos, int index)
{
	int posX = pos.x;
	int posY = pos.y;

	if (index == -1){
		//マウス表示
		ShowCursor(true);
		MessageBox(NULL, "RenderTexで-1の値が渡されました", "D2dObj.cpp", IDOK);
		return;
	}
	if (!pTex[index].used){//読み込んでいない
		return;
	};
	//scale削除済
	float x = pTex[index].nWidth * 0.5f;//(CApplication::GetScreenSizex() / 1280.0f)
	float y = pTex[index].nHeight * 0.5f;

	DWORD vColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	D2D_TEXTURE vPoint[] = {
		{ -x, -y, 0, 1, vColor, pTex[index].uv1[0], pTex[index].uv2[0] }
		, { x, -y, 0, 1, vColor, pTex[index].uv1[1], pTex[index].uv2[0] }
		, { -x, y, 0, 1, vColor, pTex[index].uv1[0], pTex[index].uv2[1] }
		, { x, y, 0, 1, vColor, pTex[index].uv1[1], pTex[index].uv2[1] }
	};
	//angel削除済
	float RotX = sinf(0 * D3DX_PI / 180.0f);
	float RotY = cosf(0 * D3DX_PI / 180.0f);
	for (int i = 0; i < 4; i++){
		D2D_TEXTURE *pv = &vPoint[i];
		float fX = pv->x;
		float fY = pv->y;
		pv->x = ((fX*RotY) - (fY*RotX) + posX + pTex[index].nWidth / 2) * (CApplication::GetScreenSizex() / 1280.0f);
		pv->y = ((fX*RotX) + (fY*RotY) + posY + pTex[index].nHeight / 2) * (CApplication::GetScreenSizey() / 720.0f);
	}
	//透過処理
	CApplication::GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	CApplication::GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	CApplication::GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//描画
	CApplication::GetDevice()->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	CApplication::GetDevice()->SetTexture(0, pTex[index].pDxTex);
	CApplication::GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vPoint, sizeof(D2D_TEXTURE));

}

/**
* @brief :テクスチャ描画
* @param posX	:左上x座標
* @param posY	:左上y座標
* @param index	:ファイルを指定するID
* @param color	:色
*/
void CTexture::RenderTex(int posX, int posY, int index, DWORD color)
{
	if (index == -1){
		//マウス表示
		ShowCursor(true);
		MessageBox(NULL, "RenderTex(color)で-1の値が渡されました", "D2dObj.cpp", IDOK);
		return;
	}
	if (!pTex[index].used){//読み込んでいない
		return;
	}
	//scale削除済
	float x = pTex[index].nWidth * 0.5f;//(CApplication::GetScreenSizex() / 1280.0f)
	float y = pTex[index].nHeight * 0.5f;

	DWORD vColor = color;
	D2D_TEXTURE vPoint[] = {
		{ -x, -y, 0, 1, vColor, pTex[index].uv1[0], pTex[index].uv2[0] }
		, { x, -y, 0, 1, vColor, pTex[index].uv1[1], pTex[index].uv2[0] }
		, { -x, y, 0, 1, vColor, pTex[index].uv1[0], pTex[index].uv2[1] }
		, { x, y, 0, 1, vColor, pTex[index].uv1[1], pTex[index].uv2[1] }
	};
	//angel削除済
	float RotX = sinf(0 * D3DX_PI / 180.0f);
	float RotY = cosf(0 * D3DX_PI / 180.0f);
	for (int i = 0; i < 4; i++){
		D2D_TEXTURE *pv = &vPoint[i];
		float fX = pv->x;
		float fY = pv->y;
		pv->x = ((fX*RotY) - (fY*RotX) + posX + pTex[index].nWidth / 2) * (CApplication::GetScreenSizex() / 1280.0f);
		pv->y = ((fX*RotX) + (fY*RotY) + posY + pTex[index].nHeight / 2) * (CApplication::GetScreenSizey() / 720.0f);
	}
	//透過処理
	CApplication::GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	CApplication::GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	CApplication::GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//描画
	CApplication::GetDevice()->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	CApplication::GetDevice()->SetTexture(0, pTex[index].pDxTex);
	CApplication::GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vPoint, sizeof(D2D_TEXTURE));

}

/**
* @brief :テクスチャ描画(アルファブレンディング有り)
* @param posX	:左上x座標
* @param posY	:左上y座標
* @param alpha	:アルファ値
* @param index	:ファイルを指定するID
*/
void CTexture::RenderAlphaBrendingTex(int posX, int posY, int alpha, int index)
{
	if (index == -1){
		//マウス表示
		ShowCursor(true);
		MessageBox(NULL, "RenderAlphaBrendingTexで-1の値が渡されました", "D2dObj.cpp", IDOK);
		return;
	}
	if (!pTex[index].used){//読み込んでいない
		return;
	}
	//scale削除済
	float x = (pTex[index].nWidth * 0.5f) * (CApplication::GetScreenSizex() / 1280.0f);
	float y = (pTex[index].nHeight * 0.5f)  * (CApplication::GetScreenSizey() / 720.0f);

	DWORD vColor = D3DCOLOR_ARGB(alpha, 255, 255, 255);
	D2D_TEXTURE vPoint[] = {
		{ -x, -y, 0, 1, vColor, pTex[index].uv1[0], pTex[index].uv2[0] }
		, { x, -y, 0, 1, vColor, pTex[index].uv1[1], pTex[index].uv2[0] }
		, { -x, y, 0, 1, vColor, pTex[index].uv1[0], pTex[index].uv2[1] }
		, { x, y, 0, 1, vColor, pTex[index].uv1[1], pTex[index].uv2[1] }
	};
	//angel削除済
	float RotX = sinf(0 * D3DX_PI / 180.0f);
	float RotY = cosf(0 * D3DX_PI / 180.0f);
	for (int i = 0; i < 4; i++){
		D2D_TEXTURE *pv = &vPoint[i];
		float fX = pv->x;
		float fY = pv->y;
		pv->x = ((fX*RotY) - (fY*RotX) + posX + pTex[index].nWidth / 2) * (CApplication::GetScreenSizex() / 1280.0f);
		pv->y = ((fX*RotX) + (fY*RotY) + posY + pTex[index].nHeight / 2) * (CApplication::GetScreenSizey() / 720.0f);
	}

	//透過処理
	CApplication::GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	CApplication::GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	CApplication::GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//描画
	CApplication::GetDevice()->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	CApplication::GetDevice()->SetTexture(0, pTex[index].pDxTex);
	CApplication::GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vPoint, sizeof(D2D_TEXTURE));

}

/**
* @brief :テクスチャ描画(スケーリングあり)
* @param posX	:左上x座標
* @param posY	:左上y座標
* @param scale	:サイズ
* @param index	:ファイルを指定するID
*/
void CTexture::RenderTex(int posX, int posY, float scale, int index)
{
	if (index == -1){
		//マウス表示
		ShowCursor(true);
		MessageBox(NULL, "Render_Texで-1の値が渡されました", "D2dObj.cpp", IDOK);
		return;
	}
	if (!pTex[index].used){//読み込んでいない
		return;
	}
	//scale削除済
	float x = pTex[index].nWidth * 0.5f * scale;
	float y = pTex[index].nHeight * 0.5f * scale;

	DWORD vColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	D2D_TEXTURE vPoint[] = {
		{ -x, -y, 0, 1, vColor, pTex[index].uv1[0], pTex[index].uv2[0] }
		, { x, -y, 0, 1, vColor, pTex[index].uv1[1], pTex[index].uv2[0] }
		, { -x, y, 0, 1, vColor, pTex[index].uv1[0], pTex[index].uv2[1] }
		, { x, y, 0, 1, vColor, pTex[index].uv1[1], pTex[index].uv2[1] }
	};
	//angel削除済
	float RotX = sinf(0 * D3DX_PI / 180.0f);
	float RotY = cosf(0 * D3DX_PI / 180.0f);
	for (int i = 0; i < 4; i++){
		D2D_TEXTURE *pv = &vPoint[i];
		float fX = pv->x;
		float fY = pv->y;
		pv->x = ((fX*RotY) - (fY*RotX) + posX + pTex[index].nWidth / 2) * (CApplication::GetScreenSizex() / 1280.0f);
		pv->y = ((fX*RotX) + (fY*RotY) + posY + pTex[index].nHeight / 2) * (CApplication::GetScreenSizey() / 720.0f);
	}
	//透過処理
	CApplication::GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	CApplication::GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	CApplication::GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//描画
	CApplication::GetDevice()->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	CApplication::GetDevice()->SetTexture(0, pTex[index].pDxTex);
	CApplication::GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vPoint, sizeof(D2D_TEXTURE));

}

/**
* @brief :テクスチャ描画(スケーリングあり)
* @param posX	:左上x座標
* @param posY	:左上y座標
* @param scale	:スケール
* @param color	:色
* @param index	:ファイルを指定するID
*/
void CTexture::RenderTex(int posX, int posY, float scale, int index, DWORD color)
{
	if (index == -1){
		//マウス表示
		ShowCursor(true);
		MessageBox(NULL, "Render_Texで-1の値が渡されました", "D2dObj.cpp", IDOK);
		return;
	}
	if (!pTex[index].used){//読み込んでいない
		return;
	}
	//scale削除済
	float x = pTex[index].nWidth * 0.5f * scale;
	float y = pTex[index].nHeight * 0.5f * scale;

	DWORD vColor = color;
	D2D_TEXTURE vPoint[] = {
		{ -x, -y, 0, 1, vColor, pTex[index].uv1[0], pTex[index].uv2[0] }
		, { x, -y, 0, 1, vColor, pTex[index].uv1[1], pTex[index].uv2[0] }
		, { -x, y, 0, 1, vColor, pTex[index].uv1[0], pTex[index].uv2[1] }
		, { x, y, 0, 1, vColor, pTex[index].uv1[1], pTex[index].uv2[1] }
	};
	//angel削除済
	float RotX = sinf(0 * D3DX_PI / 180.0f);
	float RotY = cosf(0 * D3DX_PI / 180.0f);
	for (int i = 0; i < 4; i++){
		D2D_TEXTURE *pv = &vPoint[i];
		float fX = pv->x;
		float fY = pv->y;
		pv->x = ((fX*RotY) - (fY*RotX) + posX + pTex[index].nWidth / 2) * (CApplication::GetScreenSizex() / 1280.0f);
		pv->y = ((fX*RotX) + (fY*RotY) + posY + pTex[index].nHeight / 2) * (CApplication::GetScreenSizey() / 720.0f);
	}
	//透過処理
	CApplication::GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	CApplication::GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	CApplication::GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//描画
	CApplication::GetDevice()->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	CApplication::GetDevice()->SetTexture(0, pTex[index].pDxTex);
	CApplication::GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vPoint, sizeof(D2D_TEXTURE));

}

/**
* @brief :テクスチャ描画(元のサイズ)
* @param posX	:左上x座標
* @param posY	:左上y座標
* @param index	:ファイルを指定するID
*/
void CTexture::RenderNormTex(int posX, int posY, int index)
{
	if (index == -1){
		//マウス表示
		ShowCursor(true);
		MessageBox(NULL, "RenderNormTexで-1の値が渡されました", "D2dObj.cpp", IDOK);
		return;
	}
	if (!pTex[index].used){//読み込んでいない
		return;
	}
	//scale削除済
	float x = pTex[index].nWidth * 0.5f;//(CApplication::GetScreenSizex() / 1280.0f)
	float y = pTex[index].nHeight * 0.5f;

	DWORD vColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	D2D_TEXTURE vPoint[] = {
		{ -x, -y, 0, 1, vColor, pTex[index].uv1[0], pTex[index].uv2[0] }
		, { x, -y, 0, 1, vColor, pTex[index].uv1[1], pTex[index].uv2[0] }
		, { -x, y, 0, 1, vColor, pTex[index].uv1[0], pTex[index].uv2[1] }
		, { x, y, 0, 1, vColor, pTex[index].uv1[1], pTex[index].uv2[1] }
	};
	//angel削除済
	float RotX = sinf(0 * D3DX_PI / 180.0f);
	float RotY = cosf(0 * D3DX_PI / 180.0f);
	for (int i = 0; i < 4; i++){
		D2D_TEXTURE *pv = &vPoint[i];
		float fX = pv->x;
		float fY = pv->y;
		pv->x = ((fX*RotY) - (fY*RotX) + posX + pTex[index].nWidth / 2) * (CApplication::GetScreenSizex() / 1280.0f);
		pv->y = ((fX*RotX) + (fY*RotY) + posY + pTex[index].nHeight / 2) * (CApplication::GetScreenSizey() / 720.0f);
	}
	//透過処理
	CApplication::GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	CApplication::GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	CApplication::GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//描画
	CApplication::GetDevice()->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	CApplication::GetDevice()->SetTexture(0, pTex[index].pDxTex);
	CApplication::GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vPoint, sizeof(D2D_TEXTURE));

}

/**
* @brief :テクスチャ描画(元のサイズ,スケーリングあり)
* @param posX	:左上x座標
* @param posY	:左上y座標
* @param scale	:スケール
* @param index	:ファイルを指定するID
*/
void CTexture::RenderNormTex(int posX, int posY, float scale, int index)
{
	if (index == -1){
		//マウス表示
		ShowCursor(true);
		MessageBox(NULL, "Render_Texで-1の値が渡されました", "D2dObj.cpp", IDOK);
		return;
	}
	if (!pTex[index].used){//読み込んでいない
		return;
	}
	//scale削除済
	float x = pTex[index].nWidth * 0.5f * scale;
	float y = pTex[index].nHeight * 0.5f * scale;

	DWORD vColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	D2D_TEXTURE vPoint[] = {
		{ -x, -y, 0, 1, vColor, pTex[index].uv1[0], pTex[index].uv2[0] }
		, { x, -y, 0, 1, vColor, pTex[index].uv1[1], pTex[index].uv2[0] }
		, { -x, y, 0, 1, vColor, pTex[index].uv1[0], pTex[index].uv2[1] }
		, { x, y, 0, 1, vColor, pTex[index].uv1[1], pTex[index].uv2[1] }
	};
	//angel削除済
	float RotX = sinf(0 * D3DX_PI / 180.0f);
	float RotY = cosf(0 * D3DX_PI / 180.0f);
	for (int i = 0; i < 4; i++){
		D2D_TEXTURE *pv = &vPoint[i];
		float fX = pv->x;
		float fY = pv->y;
		pv->x = (fX*RotY) - (fY*RotX) + posX + pTex[index].nWidth / 2;
		pv->y = (fX*RotX) + (fY*RotY) + posY + pTex[index].nHeight / 2;
	}
	//透過処理
	CApplication::GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	CApplication::GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	CApplication::GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//描画
	CApplication::GetDevice()->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	CApplication::GetDevice()->SetTexture(0, pTex[index].pDxTex);
	CApplication::GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vPoint, sizeof(D2D_TEXTURE));

}
