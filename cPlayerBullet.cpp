#include "DXUT.h"
#include "cPlayerBullet.h"

cPlayerBullet::cPlayerBullet(string imageName, VEC2 pos, VEC2 dir, double rot, double bulletSpd, VEC2 size)
	: cBullet(imageName, pos, dir, rot, size)
{
	m_bulletSpd = bulletSpd;
}

cPlayerBullet::~cPlayerBullet()
{
}

void cPlayerBullet::Update()
{
	m_pos += m_dir * m_bulletSpd * D_TIME;
	for (auto iter : ((cEnemyManager*)OBJFIND(ENEMY))->GetEnemy())
		if (iter->GetLive())
			OnCollision(iter);
	if (OutMapChk()) SetLive(false);
}

void cPlayerBullet::OnCollision(cObject* other)
{
	if (other->GetName() == "EnemyMeteor") return;

	if (AABB(GetObjCollider(), other->GetObjCollider())) {
		SetLive(false);
		((cEnemy*)other)->m_hp -= m_atk;
		if (((cEnemy*)other)->m_hp <= 0) ((cEnemy*)other)->SetLive(false);
	}
}

void cPlayerBullet::Dead()
{
}
