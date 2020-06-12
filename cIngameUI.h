#pragma once
#include "cUI.h"
class cIngameUI : public cUI
{
public:
	cIngameUI();
	virtual ~cIngameUI();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

