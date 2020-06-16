#pragma once
#include "cUI.h"
class cMidBossClearUI : public cUI
{
public:
	cTimer* m_t = nullptr;
	int time;
	int enterHit;
	cTexture* m_but = nullptr;
	cTexture* m_gage = nullptr;
	cTexture* m_gageLine = nullptr;
	bool isEnter;
public:
	cMidBossClearUI();
	virtual ~cMidBossClearUI();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

