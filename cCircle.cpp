#include "DXUT.h"
#include "cCircle.h"

cCircle::cCircle(VEC2 pos, double downSpd)
	: cEnemy(50 + 20 * GAME->m_level, 5 * GAME->m_nowStage * GAME->m_level), m_downSpd(downSpd)
{
	char str[256];
	sprintf(str, "EnemyCircle%dIMG", GAME->m_nowStage - 1);
	m_img = IMAGE->FindTexture(str);

	m_objName = "EnemyCircle";
	m_pos = pos;
	m_size = VEC2(0.4, 0.4);
	m_rot = 0;

	m_bulletDelay = 0.5;
	m_bulletTime = m_bulletDelay + 1;
}

cCircle::~cCircle()
{
}

void cCircle::Update()
{
	if (CanFire()) {
		m_bulletTime += D_TIME;
		if (m_bulletTime > m_bulletDelay) {
			m_bulletTime = 0;
			Fire();
		}
	}
	Move();
	if (OutMapChk(200)) m_isLive = false;
}

void cCircle::Move()
{
	m_pos.y += m_downSpd * D_TIME;
}

void cCircle::Fire()
{
	SOUND->Copy("EnemyFireSND");
	N_Way_Tan("EnemyBullet2IMG", 3, 120, m_pos, VEC2(0, -1), VEC2(1, 1), 100, m_atk, false, false, false, true);
}
