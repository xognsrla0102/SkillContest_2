#pragma once
#include "cScene.h"
class cBossEnterScene : public cScene
{
public:
	cTimer*		m_t      = nullptr;
	cTexture*	m_white  = nullptr;
	cTexture*	m_black  = nullptr;
	cImage*		m_player = nullptr;
	cImage*		m_boss   = nullptr;
	cTexture*	m_bg     = nullptr;
	vector<cImage*> m_leftRazer;
	vector<cImage*> m_rightRazer;

	int time;
	double whiteAlpha;
	double blackAlpha;
public:
	cBossEnterScene();
	virtual ~cBossEnterScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

