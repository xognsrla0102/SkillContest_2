#pragma once
#include "cScene.h"
class cResultScene : public cScene
{
private:
	cTexture* m_bg = nullptr;
	string m_scorePrint;
	string m_initial;
	float m_nowYourScore;
	bool m_isEnterInitial;
public:
	cResultScene();
	virtual ~cResultScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

