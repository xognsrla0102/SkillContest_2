#pragma once
#include "cBullet.h"
class cPlayerBullet : public cBullet
{
public:
	cPlayerBullet(string imageName, VEC2 pos, VEC2 dir, double rot, double bulletSpd, VEC2 size = VEC2(1, 1));
	virtual ~cPlayerBullet();

	virtual void Update() override;
	virtual void OnCollision(cObject* other) override;
	virtual void Dead() override;
};

