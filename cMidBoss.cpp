#include "DXUT.h"
#include "cMidBoss.h"

cMidBoss::cMidBoss() : cEnemy(1000, 10)
{
	m_t = new cTimer(0.1);

	char str[256];
	sprintf(str, "EnemyMidBoss%dIMG", GAME->m_nowStage - 1);
	m_img = IMAGE->FindTexture(str);
}

cMidBoss::~cMidBoss()
{
	SAFE_DELETE(m_t);
}

void cMidBoss::Update()
{
	if (m_t->Update()) {
		m_time++;
		Fire();
	}
	Move();
}

void cMidBoss::Move()
{
}

void cMidBoss::Fire()
{
}
