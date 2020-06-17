#pragma once
#include "cObject.h"

class cEnemy;
class cEnemyManager : public cObject
{
private:
	vector<cEnemy*> m_enemy;
public:
	cMidBoss* m_midBoss = nullptr;
	cBoss* m_boss = nullptr;
public:
	cEnemyManager();
	virtual ~cEnemyManager();

	virtual void Update() override;
	virtual void Render() override;
	virtual void OnCollision(cObject* other) override {}
	void Release();

	vector<cEnemy*>& GetEnemy() { return m_enemy; }
};

