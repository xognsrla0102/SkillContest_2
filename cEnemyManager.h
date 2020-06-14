#pragma once
#include "cObject.h"

class cEnemy;
class cEnemyManager : public cObject
{
private:
	vector<cEnemy*> m_enemy;
public:
	cEnemyManager();
	~cEnemyManager();

	virtual void Update() override;
	virtual void Render() override;
	virtual void OnCollision(cObject* other) override {}
	void Release();

	vector<cEnemy*>& GetEnemy() { return m_enemy; }
};

