#pragma once
#include "cUI.h"

class cTitleUI : public cUI
{
private:
	vector<cButton*> m_but;
	int m_nowBut;
public:
	cTitleUI();
	virtual ~cTitleUI();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

