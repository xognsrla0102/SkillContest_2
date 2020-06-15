#pragma once
#include "cScene.h"
class cMidBossEnterScene : public cScene
{
public:
	cTimer* m_t = nullptr;
	int m_time;

	cTexture* m_midBoss = nullptr;
	cTexture* m_white = nullptr;
	int m_alpha;
	int m_bAlpha;
	int m_bossAlpha;
	cTexture* m_black = nullptr;
	VEC2 m_blackPos[2];

	cImage* m_planet = nullptr;
	cImage* m_player = nullptr;
	cScroolMap* m_map = nullptr;
public:
	cMidBossEnterScene();
	virtual ~cMidBossEnterScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	void EnterBoss();
};

