#pragma once
#include "cScene.h"
class cHowtoScene : public cScene
{
private:
	cTexture* m_bg = nullptr;
	cTexture* m_enter = nullptr;
	cTexture* m_howto = nullptr;
	vector<cImage*> m_imgs;
	int m_imgCnt;
	int howtoAlpha;
public:
	cHowtoScene();
	virtual ~cHowtoScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

