#pragma once
#include "cScene.h"

class cScroolMap;
class cIntroScene : public cScene
{
private:
	cTexture* m_bg = nullptr;
	cImage* m_player = nullptr;
	cImage* m_black = nullptr;
	cImage* m_white = nullptr;
	cImage* m_redCircle = nullptr;

	double wait;

	bool isCharge;
	bool isReady;
public:
	cIntroScene();
	virtual ~cIntroScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	void Intro();
};

