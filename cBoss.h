#pragma once
#include "cEnemy.h"
class cBoss : public cEnemy
{
private:
	cMotionBlur* m_motion = nullptr;
	cTimer* m_t = nullptr;
	int m_time = 0;
	bool m_isMoveDone = true;
	VEC2 m_nextPos;
public:
	bool m_isDead = false;
public:
	cBoss();
	virtual ~cBoss();

	virtual void Update() override;
	virtual void Render() override;
	virtual void Move() override;
	virtual void Fire() override;
	void Dead() override;
};

