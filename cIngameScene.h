#pragma once
#include "cScene.h"

class cScroolMap;
class cIngameScene : public cScene
{
private:
	cTexture* m_bg = nullptr;
	cImage* m_black = nullptr;
	cImage* m_white = nullptr;
	cImage* m_redCircle = nullptr;

	cScroolMap* map = nullptr;

	double late;

	bool isIntro;
	bool isCharge;
	bool isReady;
public:
	cIngameScene();
	virtual ~cIngameScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	void Intro();
};

