#pragma once
#include "cUI.h"
class cIngameUI : public cUI
{
private:
	cTexture* m_bg = nullptr;
	cTexture* m_exp = nullptr;
	cImage* m_life[5] = { NULL };
public:
	cIngameUI();
	virtual ~cIngameUI();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

