#include "DXUT.h"
#include "cPlayerBullet.h"

cPlayerBullet::cPlayerBullet(string imageName, VEC2 pos, VEC2 dir, double rot, double bulletSpd, VEC2 size)
	: cBullet(imageName, pos, dir, rot, size)
{
	m_bulletSpd = bulletSpd;
}

cPlayerBullet::~cPlayerBullet()
{
	cBullet::~cBullet();
}

void cPlayerBullet::Update()
{
	m_pos += m_dir * m_bulletSpd * D_TIME;
}

void cPlayerBullet::OnCollision(cObject* other)
{
}

void cPlayerBullet::Dead()
{
}
