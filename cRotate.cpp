#include "DXUT.h"
#include "cRotate.h"

cRotate::cRotate(VEC2 pos)
	: cEnemy(10 + 20 * GAME->m_level, 5)
{
	rotDir = rand() % 2 ? 1 : -1;

	char str[256];
	sprintf(str, "EnemyRotate%dIMG", GAME->m_nowStage);
	m_img = IMAGE->FindTexture(str);

	m_objName = "EnemyRotate";
	m_pos = pos;
	m_size = VEC2(1, 1);
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
	cPointInfo nowPath = m_path->m_endPoint[m_path->m_nowPos];
	VEC2 dir = nowPath.m_pos - m_pos;
	D3DXVec2Normalize(&dir, &dir);
	float moveDist = D3DXVec2Length(&(dir * nowPath.m_speed * D_TIME));
	moveDist *= m_isAccelCurve ? m_accelCurve : 1;

	bool cngNextPoint = m_path->Update(m_pos, moveDist);
	if (m_path->m_isDone) {
		m_isLive = false;
		return;
	}
	if (cngNextPoint) {
		if (m_path->m_nowPos != 0) m_pos = m_path->m_endPoint[m_path->m_nowPos - 1].m_pos;
		else m_pos = m_path->m_endPoint[0].m_pos;
	}

	nowPath = m_path->m_endPoint[m_path->m_nowPos];
	if (nowPath.m_isCurve == false) Lerp(m_pos, nowPath.m_pos, nowPath.m_speed);
	else {
		VEC2 dir = nowPath.m_pos - m_pos;
		D3DXVec2Normalize(&dir, &dir);
		if (m_isAccelCurve == TRUE) {
			if (m_accelCurve < 1.f) m_accelCurve += D_TIME / m_divDelta;
			else m_accelCurve = 1.f;
			m_pos += dir * nowPath.m_speed * D_TIME * m_accelCurve;
		}
		else {
			m_pos += dir * nowPath.m_speed * D_TIME;
		}
	}
}

void cRotate::Fire()
{
	VEC2 dir = OBJFIND(PLAYER)->GetPos() - m_pos;
	D3DXVec2Normalize(&dir, &dir);
	N_Way_Tan("EnemyBullet1IMG", 3, 2, m_pos, dir, VEC2(1, 1), 500, m_atk);
}
