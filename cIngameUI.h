#pragma once
#include "cUI.h"
class cIngameUI : public cUI
{
private:
	cTexture* m_bg = nullptr;
	cTexture* m_life = nullptr;
	cTexture* m_exp = nullptr;
	cTexture* m_bossHP = nullptr;
public:
	cImage* m_damage = nullptr;
public:
	cIngameUI();
	virtual ~cIngameUI();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

