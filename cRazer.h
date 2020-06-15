#pragma once
#include "cEnemy.h"
class cRazer : public cEnemy
{
private:
	cAnimation* m_chargeEffect = nullptr;
	bool m_isChargeTime = false;
	bool m_isBehind = false;
public:
	cRazer(VEC2 pos, bool isBehind);
	virtual ~cRazer();

	virtual void Update() override;
	virtual void Render() override;
	virtual void Move() override;
	virtual void Fire() override;
};

