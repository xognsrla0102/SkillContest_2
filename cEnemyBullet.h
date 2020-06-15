#pragma once
#include "cBullet.h"
class cEnemyBullet : public cBullet
{
public:
	cEnemyBullet(string imageName, VEC2 pos, VEC2 dir, double rot, double bulletSpd, bool isFaccel = false, bool isSaccel = false, VEC2 size = VEC2(1, 1));
	virtual ~cEnemyBullet();

	virtual void Update() override;
	virtual void Dead() override;
	virtual void OnCollision(cObject* other) override {}
};

