#pragma once
#include "cEnemy.h"
class cTurret : public cEnemy
{
private:
	double m_downSpd;
public:
	cTurret(string name, VEC2 pos, VEC2 size, double rot, double downSpd);
	virtual ~cTurret();

	virtual void Update() override;
	virtual void OnCollision(cObject* other) override {}

	virtual void Dead() override;
	virtual void Move() override;
	virtual void Fire() override;
};

