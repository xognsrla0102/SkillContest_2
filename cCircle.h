#pragma once
#include "cEnemy.h"
class cCircle : public cEnemy
{
private:
	double m_bulDir = 0;
	double m_downSpd;
public:
	cCircle(VEC2 pos, double downSpd);
	virtual ~cCircle();

	virtual void Update() override;
	virtual void Move() override;
	virtual void Fire() override;
};

