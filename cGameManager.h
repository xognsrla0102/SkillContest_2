#pragma once
#include "cSingleton.hpp";


class cGameManager : public cSingleton<cGameManager>
{
public:
	double OLD_TIME_SCALE;
	double TIME_SCALE;

	int m_expMax;
	int m_nowExp;
	int m_score;

	int m_level;

	int m_nowStage = 1;

	bool m_isNotDead;
	bool m_isDebugInfo;

	bool m_isMidBoss;
	bool m_isBoss;
public:
	cGameManager();
	virtual ~cGameManager();

	void StageInit();
	void Init();
	void Update();
	void SortScore();
};

#define GAME cGameManager::GetInst()