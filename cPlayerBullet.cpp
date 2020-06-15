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

	auto boss = ((cEnemyManager*)OBJFIND(ENEMY))->m_midBoss;
	if (boss && boss->GetLive())
		OnCollision(boss);

	if (OutMapChk()) SetLive(false);
}

void cPlayerBullet::OnCollision(cObject* other)
{
	if (other->GetName() == "EnemyMeteor") return;

	if (AABB(GetObjCollider(), other->GetObjCollider())) {
		SetLive(false);
		SOUND->Copy("EnemyHitSND");
		VEC2 pos = other->GetPos();
		EFFECT->AddEffect(new cEffect("DieEFFECT", 1, 0, pos, VEC2(0, 0), VEC2(1, 1), VEC2(1, 1), 1000));
		((cEnemy*)other)->m_hp -= m_atk;
		if (((cEnemy*)other)->m_hp <= 0) {
			if (other->GetName() == "EnemyMidBoss") {
				((cEnemy*)other)->m_hp = 0;
				((cMidBoss*)other)->m_isDead = true;
				return;
			}
			else if (other->GetName() == "EnemyBoss") {
				((cEnemy*)other)->m_hp = 0;
				//((cBoss*)other)->m_isDead = true;
				return;
			}
			EFFECT->AddEffect(new cEffect("ExplosionEFFECT", 32, 0.02, pos, VEC2(0, 0)));
			((cEnemy*)other)->SetLive(false);
			CAMERA->SetShake(0.1, 10);
			SOUND->Copy("EnemyDeadSND");
			for (size_t j = 0; j < ((cEnemy*)other)->GetItemName().size(); j++) {
				string nowItemName = ((cEnemy*)other)->GetItemName()[j];
				((cItemManager*)OBJFIND(ITEM))->m_items.push_back(
					new cItem(nowItemName, pos, VEC2(pos.x, pos.y - (40 + rand() % 30)))
				);
			}
			GAME->m_nowExp += 50 + rand() % 3 * 30;
		}
	}
}

void cPlayerBullet::Dead()
{
}
