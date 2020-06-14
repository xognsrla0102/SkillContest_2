#pragma once
#include "cObject.h"
class cCharacter abstract : public cObject
{
public:
	int m_hp;
	int m_hpMax;
	double m_a = 255;
public:
	cCharacter(int hp) : m_hp(hp), m_hpMax(hp) {}
	virtual ~cCharacter() {}

	virtual void Update() PURE;
	virtual void Render() PURE;
	virtual void OnCollision(cObject* other) PURE;

	virtual void N_Way_Tan(string imageName, int n, int theta, VEC2 pos, VEC2 dir, VEC2 size, float bulletSpd, float atk, bool isRandShot = false, bool isHoming = false, bool isFaccel = false, bool isSaccel = false) PURE;
	virtual void N_Straight_Tan(string imageName, int n, int length, VEC2 pos, VEC2 dir, VEC2 size, float bulletSpd, float atk, bool isFaccel = false, bool isSaccel = false) PURE;

	virtual void Dead() PURE;
	virtual void Move() PURE;
	virtual void Fire() PURE;
};

