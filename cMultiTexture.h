#pragma once
#include "cTexture.h"
class cMultiTexture : public cTexture
{
private:
	vector<cTexture*> m_multiImgs;
public:
	cMultiTexture();
	virtual ~cMultiTexture();

	void AddTexture(string path, int cnt = 1);
	cTexture* FindTexture(int cnt = 0);

	size_t GetImgSize() { return m_multiImgs.size(); }
};

