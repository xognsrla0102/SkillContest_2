#pragma once
#include "cCharacter.h"

class cPlayer : public cCharacter
{
private:
	double m_originSpd;
	double m_moveSpd;
	double m_damageTime;
public:
	cTimer* m_fire = nullptr;

	float m_fireDelay[2] = { 0 };
	float m_atk[2] = { 0 };

	bool m_isDamaged;
	bool m_radialTan;

	bool m_canMove;
	bool m_waitFire;
	bool m_isNoOutMap;
public:
	cPlayer();
	virtual ~cPlayer();

	void Init();
	void Release();

	virtual void Update() override;
	virtual void Render() override;
	virtual void OnCollision(cObject* other) override;

	virtual void N_Way_Tan(string imageName, int n, int theta, VEC2 pos, VEC2 dir, VEC2 size, float bulletSpd, float atk, bool isRandShot = false, bool isHoming = false, bool isFaccel = false, bool isSaccel = false) override;
	virtual void N_Straight_Tan(string imageName, int n, int length, VEC2 pos, VEC2 dir, VEC2 size, float bulletSpd, float atk, bool isFaccel = false, bool isSaccel = false) override;

	virtual void Dead() override;
	virtual void Move() override;
	virtual void Fire() override;
	void ChangeWeapon();
	void NoOutMap();
};

