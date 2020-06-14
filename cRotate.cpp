#include "DXUT.h"
#include "cRotate.h"

cRotate::cRotate(string name, VEC2 pos, VEC2 size)
	: cEnemy(10 + 20 * GAME->m_level, 5)
{
	rotDir = rand() % 2 ? 1 : -1;

	//m_path = new cPath();

	m_img = IMAGE->FindTexture(name);

	m_objName = "EnemyRotate";
	m_pos = pos;
	m_size = size;
	m_rot = 0;

	m_bulletDelay = 1 + rand() % 10 / 10.f;
	m_bulletTime = m_bulletDelay + 1;
}

cRotate::~cRotate()
{
	SAFE_DELETE(m_path);
}

void cRotate::Update()
{
	m_rot += rotDir;
	if (m_rot > 360) m_rot -= 360;
	else if (m_rot < 0) m_rot += 360;

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

void cRotate::Move()
{
}

void cRotate::Fire()
{
	VEC2 dir = OBJFIND(PLAYER)->GetPos() - m_pos;
	D3DXVec2Normalize(&dir, &dir);
	N_Way_Tan("EnemyBullet1IMG", 3, 2, m_pos, dir, VEC2(1, 1), 500, m_atk);
}
