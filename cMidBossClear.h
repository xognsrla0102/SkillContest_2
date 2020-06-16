#pragma once
#include "cScene.h"
class cMidBossClear : public cScene
{
public:
	cAnimation* m_ani = nullptr;
	cTexture* m_white = nullptr;
	cTexture* m_bg = nullptr;
	cTexture* m_bg2 = nullptr;
	cTexture* m_razer = nullptr;
	cTexture* m_shield = nullptr;
	cImage* m_player = nullptr;
	bool isEnter;
	bool isWhite;
	double whiteAlpha;
public:
	cMidBossClear();
	virtual ~cMidBossClear();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

