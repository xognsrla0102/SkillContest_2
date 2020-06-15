#pragma once
#include "cEnemy.h"
class cMidBoss : public cEnemy
{
private:
	cTimer* m_t = nullptr;
	int m_time = 0;
public:
	cMidBoss();
	virtual ~cMidBoss();

	virtual void Update() override;
	virtual void Move() override;
	virtual void Fire() override;
};

