#include "DXUT.h"
#include "cTurret.h"

cTurret::cTurret(VEC2 pos, double downSpd)
	: cEnemy(20 + 20 * GAME->m_level, 5 * GAME->m_nowStage), m_downSpd(downSpd)
{
	char str[256];
	sprintf(str, "EnemyTurret%dIMG", GAME->m_nowStage - 1);
	m_img = IMAGE->FindTexture(str);

	m_objName = "EnemyTurret";
	m_pos = pos;
	m_size = VEC2(1.5, 1.5);
	m_rot = 0;

	m_bulletDelay = 1 + rand() % 20 / 10.f;
	m_bulletTime = m_bulletDelay + 1;
}

cTurret::~cTurret()
{
}

void cTurret::Update()
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

void cTurret::Move()
{
	VEC2 dir = OBJFIND(PLAYER)->GetPos() - m_pos;
	m_rot = D3DXToDegree(atan2f(dir.y, dir.x)) + 90;
	m_pos.y += m_downSpd * D_TIME;
}

void cTurret::Fire()
{
	SOUND->Copy("EnemyFireSND");
	VEC2 dir = OBJFIND(PLAYER)->GetPos() - m_pos;
	D3DXVec2Normalize(&dir, &dir);
	N_Straight_Tan("EnemyBullet0IMG", 1, 10, m_pos, dir, VEC2(1, 1), 800, m_atk);
}
