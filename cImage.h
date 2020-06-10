#pragma once
class cImage
{
public:
	cTexture* m_text = nullptr;
	D3DXCOLOR m_color = D3DCOLOR_ARGB(255, 255, 255, 255);
	VEC2 m_pos = VEC2(0, 0);

	double m_a = 255.0;
	double m_r = 255.0;
	double m_g = 255.0;
	double m_b = 255.0;
public:
	cImage() {}
	~cImage() {}

	void SetNowRGB() { m_color = D3DCOLOR_ARGB((int)m_a, (int)m_r, (int)m_g, (int)m_b); }
};

