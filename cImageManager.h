#pragma once
#include "cSingleton.hpp"

class cTexture;
class cMultiTexture;
class cImageManager : public cSingleton<cImageManager>
{
private:
	map<string, cMultiTexture*> m_imgs;
	LPD3DXSPRITE m_sprite;
public:
	cImageManager();
	virtual ~cImageManager();

	void Begin(bool isUI);
	void End();
	void ReBegin(bool isUI);

	void LostDevice();
	void ResetDevice();

	void AddTexture(string name, string path, int cnt = 1);
	cMultiTexture* FindMultiTexture(string name);
	cTexture* FindTexture(string name, int cnt = 0);

	void Render(cTexture* text, VEC2 pos, VEC2 size = VEC2(1, 1), double rot = 0.0, bool isCenter = false, D3DXCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255));
	void CropRender(cTexture* text, VEC2 pos, RECT rt, VEC2 size = VEC2(1, 1), bool isCenter = false);

	void DrawNum(string text, VEC2 pos, int numD, VEC2 size = VEC2(1, 1));

	//length '.' 포함 전체 숫자 갯수 dotD 점 텍스트 간격, numD 숫자 텍스트 간격
	void DrawFloat(string text, VEC2 pos, int length, int dotD, int numD, VEC2 size = VEC2(1, 1));
	void DrawFont(string text, VEC2 pos, string fontName = "Arial", int size = 20, D3DXCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255));
};

#define IMAGE cImageManager::GetInst()