#pragma once
#include "cEnemy.h"
class cTurret : public cEnemy
{
private:
	double m_downSpd;
public:
	cTurret(VEC2 pos, double downSpd);
	virtual ~cTurret();

	virtual void Update() override;
	virtual void Move() override;
	virtual void Fire() override;
};

