#pragma once
#include "cEnemy.h"
class cMeteor : public cEnemy
{
private:
	double m_downSpd;
public:
	cMeteor(string name, VEC2 pos, VEC2 size, double rot, double downSpd);
	virtual ~cMeteor();

	virtual void Update() override;
	virtual void Move() override;
	virtual void Fire() override {}
};

