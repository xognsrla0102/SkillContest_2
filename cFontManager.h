#pragma once
#include "cSingleton.hpp"

class cTimer;
class cFontInfo {
private:
	cTimer* m_timer = nullptr;
	string m_text;
	VEC2 m_pos;
	D3DCOLOR m_color;
	BOOL m_isScoreText;
	int m_size;
public:
	BOOL m_isDone = FALSE;
public:
	cFontInfo(string text, VEC2 pos, int size, INT printTime, BOOL isScoreText = FALSE, D3DCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255));
	~cFontInfo();

	void Update();
	void Render();
};

class cFontManager : public cSingleton<cFontManager>
{
public:
	vector<cFontInfo*> m_fonts;
public:
	cFontManager() {}
	virtual ~cFontManager();

	void Update();
	void Render();
	void Release();

	void AddFont(string text, VEC2 pos, int size, INT printTime, BOOL isScoreText = FALSE, D3DCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255));
};

#define FONT cFontManager::GetInst()