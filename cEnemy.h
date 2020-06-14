#pragma once
#include "cCharacter.h"

class cPath;
class cEnemy : public cCharacter
{
public:
	cPath* m_path = nullptr;

	int m_atk;
	int m_divDelta = 2;

	double m_bulletTime = 0;
	double m_bulletDelay = 0;
	double m_dirRot = 0;
	double m_accelCurve = 0;

	bool m_isAccelCurve = false;
public:
	cEnemy(int hp, int atk);
	virtual ~cEnemy();

	virtual void Update() override;
	virtual void Render() override;
	virtual void OnCollision(cObject* other) override;

	virtual void N_Way_Tan(string imageName, int n, int theta, VEC2 pos, VEC2 dir, VEC2 size, float bulletSpd, float atk, bool isRandShot = false, bool isHoming = false, bool isFaccel = false, bool isSaccel = false) override;
	virtual void N_Straight_Tan(string imageName, int n, int length, VEC2 pos, VEC2 dir, VEC2 size, float bulletSpd, float atk, bool isFaccel = false, bool isSaccel = false) override;

	virtual void Dead() override;
	virtual void Move() override;
	virtual void Fire() override;
};

