#include "DXUT.h"
#include "cMidBoss.h"

cMidBoss::cMidBoss() : cEnemy(1000, 10)
{
	m_t = new cTimer(0.1);
	m_pos = GXY(GAMESIZE / 2, 200); 
	m_size = VEC2(2.5, 2.5);
	m_motion = new cMotionBlur(5, m_pos);
	char str[256];
	sprintf(str, "EnemyMidBoss%dIMG", GAME->m_nowStage - 1);
	m_img = IMAGE->FindTexture(str);
	m_objName = "EnemyMidBoss";
}

cMidBoss::~cMidBoss()
{
	SAFE_DELETE(m_t);
	SAFE_DELETE(m_motion);
}

void cMidBoss::Update()
{
	if (m_isDead) Dead();

	if (m_t->Update()) {
		m_time++;
		if (m_isDead) {
			if (m_time % 3 == 0) {
				SOUND->Copy("EnemyHitSND");
				SOUND->Copy("EnemyHitSND");
			}
			return;
		}
		Fire();
	}
	if (m_isDead) return;
	Move();
	m_motion->Update(m_pos);
}

void cMidBoss::Render()
{
	for (auto iter : m_motion->m_motionInfo)
		IMAGE->Render(m_img, iter->m_motionPos, m_size, m_rot, true, iter->m_color);
	IMAGE->Render(m_img, m_pos, m_size, m_rot, true);
}

void cMidBoss::Move()
{
	//보스가 플레이어 꼬라보게
	auto player = (cPlayer*)OBJFIND(PLAYER);
	VEC2 dir = player->GetPos() - m_pos;

	//보간하면서 꼬라보게
	Lerp(m_rot, D3DXToDegree(atan2(dir.y, dir.x)) - 90.0, 2);

	if (m_time <= 200) {
		if (m_isMoveDone) {
			m_nextPos = GXY(rand() % GAMESIZE, rand() % 30 * 10);
			m_isMoveDone = false;
		}
		else {
			Lerp(m_pos, m_nextPos, 2);
			if (DistPoint(m_pos, m_nextPos) < 5.f)
				m_isMoveDone = true;
		}
	}
	else Lerp(m_pos, GXY(GAMESIZE / 2, 300), 3);
}

void cMidBoss::Fire()
{
	if (m_time <= 20) return;

	if (m_time <= 200) {
		static double rot = 0;
		static int dRot = 10;
		VEC2 dir;
		dir.x = cos(D3DXToRadian(rot));
		dir.y = sin(D3DXToRadian(rot));
		D3DXVec2Normalize(&dir, &dir);

		char str[256];
		sprintf(str, "EnemyBullet%dIMG", rand() % 4);
		N_Way_Tan(str, 4, 90, m_pos, dir, VEC2(1, 1), 600, m_atk);
		rot += dRot;
		if (rot > 180) {
			rot = 180;
			dRot = -dRot;
		}
		else if (rot < 0) {
			rot = 0;
			dRot = -dRot;
		}

		if (m_time % 10 == 0) {
			VEC2 dir = OBJFIND(PLAYER)->GetPos() - m_pos;
			D3DXVec2Normalize(&dir, &dir);
			char str[256];
			sprintf(str, "EnemyBullet%dIMG", rand() % 4);
			N_Way_Tan(str, 36, 10, m_pos, dir, VEC2(1, 1), 600, m_atk);
		}
	}
	else {
		char str[256];
		sprintf(str, "EnemyBullet%dIMG", rand() % 4);
		N_Way_Tan(str, 10, 36, m_pos, VEC2(0, 1), VEC2(3, 3), 200, m_atk, true, false, false, true);
	}
}

void cMidBoss::Dead()
{
	static double deadTime = 4;
	deadTime -= D_TIME;
	if (deadTime < 0.f) {
		deadTime = 4;
		m_isDead = false;
		m_isLive = false;
	}
	else EFFECT->AddEffect(new cEffect("ExplosionEFFECT", 32, 0.02, VEC2(m_pos + RandomInsideSquare() * 300), VEC2(0, 0)));
}
