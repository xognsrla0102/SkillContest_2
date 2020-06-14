#pragma once
#include "cObject.h"
class cBullet : public cObject
{
protected:
	double m_bulletSpd;
	double m_accel;
	bool m_isHoming;
public:
	//유도 전용
	VEC2 m_target;
	VEC2 m_dir;
	double m_atk;
	bool m_isFaccel;
	bool m_isSaccel;
public:
	cBullet(string imageName, VEC2 pos, VEC2 dir, double rot, VEC2 size = VEC2(1, 1));
	virtual ~cBullet();

	virtual void Update() PURE;
	void Render();
	virtual void OnCollision(cObject* other) PURE;

	virtual void Dead() PURE;
	void Homing();
};

