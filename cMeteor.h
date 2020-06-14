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
	virtual void Render() override;
	virtual void OnCollision(cObject* other) override;

	virtual void N_Way_Tan(string imageName, int n, int theta, VEC2 pos, VEC2 dir, VEC2 size, float bulletSpd, float atk, bool isRandShot = false, bool isHoming = false, bool isFaccel = false, bool isSaccel = false) override {}
	virtual void N_Straight_Tan(string imageName, int n, int length, VEC2 pos, VEC2 dir, VEC2 size, float bulletSpd, float atk, bool isFaccel = false, bool isSaccel = false) override {}

	virtual void Dead() override;
	virtual void Move() override;
	virtual void Fire() override {}
};

