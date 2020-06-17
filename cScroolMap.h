#pragma once
class cScroolMap
{
private:
	cTexture* text = nullptr;
	cImage* m_img1, *m_img2;
	cImage* m_gas;
	cTimer* m_createGas;
public:
	double m_mapSpd;
	double m_gasSpd;
public:
	cScroolMap(cTexture* text);
	~cScroolMap();

	void Init();
	void Update();
	void Render();
	void Release();
};

