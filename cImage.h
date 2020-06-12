#pragma once
class cImage
{
public:
	cTexture* m_text = nullptr;
	D3DXCOLOR m_color = 0xffffffff;
	VEC2 m_pos = VEC2(0, 0);
	VEC2 m_size = VEC2(1, 1);

	double a = 255.0;
public:
	__declspec(property(get = GetAlpha, put = SetAlpha)) double m_a;
public:
	cImage() {}
	~cImage() {}

	void SetNowRGB() { m_color = D3DCOLOR_ARGB((int)a, 255, 255, 255); }

	double& GetAlpha() { 
		SetNowRGB();
		return a;
	}

	void SetAlpha(double a) { 
		this->a = a;
		SetNowRGB();
	}
};

