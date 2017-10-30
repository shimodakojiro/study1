#ifndef __D2DOBJ_H__
#define __D2DOBJ_H__

#include"../../Header/main.h"
#include"Game/GameBase.h"

class CTexture
{
private:
	//テクスチャデータ
	typedef struct{
		LPDIRECT3DTEXTURE9		pDxTex;
		DWORD					nWidth;
		DWORD					nHeight;
		float					uv1[2], uv2[2];
		bool					used;
	}TEX;

	typedef struct{
		float					x, y, z;
		float					rhw;
		DWORD					uDiffuse;
		float					tu, tv;
	}D2D_TEXTURE;

	static const int MAX_TEX = 150;
	TEX		pTex[MAX_TEX];

	struct CUSTOM_FVF { //<< 射影変換済みとして扱われる頂点情報
		D3DXVECTOR3 pos;		//<<位置
		float		rhw;		//<<1.0fを入れる	除算数？
		D3DCOLOR	color;		//<<色
	};

public:
	CTexture();
	~CTexture();
	int LoadTex(LPCTSTR filename);
	int GetTextureWidth(int idx);
	int GetTextureHeight(int idx);
	void DrawBox(float x1, float y1, float x2, float y2, D3DCOLOR color);
	void RenderTex(int posX, int posY, int index);
	void RenderTex(Vector2 pos, int index);
	void RenderTex(int posX, int posY, float scale, int index);
	void RenderTex(int posX, int posY, float scale, int index, DWORD color);
	void RenderTex(int posX, int posY, int index, DWORD color);
	void RenderNormTex(int posX, int posY, int index);
	void RenderNormTex(int posX, int posY, float scale, int index);
	void RenderAlphaBrendingTex(int posX, int posY, int alpha, int index);

};





#endif