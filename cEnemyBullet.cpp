#include "DXUT.h"
#include "cEnemyBullet.h"

cEnemyBullet::cEnemyBullet(string imageName, VEC2 pos, VEC2 dir, double rot, double bulletSpd, bool isFaccel, bool isSaccel, VEC2 size)
	: cBullet(imageName, pos, dir, rot, size)
{
	m_bulletSpd = bulletSpd;

	if (isFaccel) {
		m_isFaccel = isFaccel;
		m_bulletSpd /= 2;
		m_accel = 1;
	}
	else if (isSaccel) {
		m_isSaccel = isSaccel;
		m_bulletSpd *= 2;
		m_accel = 4;
	}
	else {
		m_accel = 1;
	}
}

cEnemyBullet::~cEnemyBullet()
{
}

void cEnemyBullet::Update()
{
	if (m_isFaccel) {
		if (m_accel > 4.f) m_accel = 4.f;
		else m_accel += D_TIME * 10;
	}
	else if (m_isSaccel) {
		if (m_accel < 1.f) m_accel = 1.f;
		else m_accel -= D_TIME * 10;
	}
	m_pos += m_dir * m_bulletSpd * D_TIME * m_accel;
}

void cEnemyBullet::OnCollision(cObject* other)
{
}

void cEnemyBullet::Dead()
{
}
