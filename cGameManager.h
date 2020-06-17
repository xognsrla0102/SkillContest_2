#pragma once
#include "cSingleton.hpp";

class cScore {
public:
	string m_initial;
	int m_score = 0;
public:
	cScore() {}
	cScore(string initial, int score) : m_initial(initial), m_score(score) {}
};

class cGameManager : public cSingleton<cGameManager>
{
public:
	cScore* m_scoreList[4];

	double OLD_TIME_SCALE;
	double TIME_SCALE;

	int m_expMax;
	int m_nowExp;
	int m_score;
	int m_level;
	int m_life;
	int m_nowStage;
	int m_story;

	bool m_isNotDead;
	bool m_isDebugInfo;

	bool m_isBehind;
public:
	cGameManager();
	virtual ~cGameManager();

	void StageInit();
	void Init();
	void Update();
	void SortScore();
};

#define GAME cGameManager::GetInst()