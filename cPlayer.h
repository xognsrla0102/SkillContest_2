#pragma once
#include "cObject.h"

class cPlayer : public cObject
{
private:
	FLOAT m_originSpd;
	FLOAT m_moveSpd;

	FLOAT m_damageTime;
public:
	cTimer* m_fire = nullptr;

	float m_fireDelay[2] = { 0 };
	float m_atk[2] = { 0 };

	bool m_isDamaged;
	bool m_radialTan;

	int m_hp;
	int m_hpMax;


	bool m_waitFire;
public:
	cPlayer();
	virtual ~cPlayer();

	void Init();
	void Release();

	virtual void Update() override;
	virtual void Render() override;
	virtual void OnCollision(cObject* other) override;

	void Dead();
	void ChangeWeapon();
	void Move();
	void Fire();
};

