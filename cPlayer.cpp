#include "DXUT.h"
#include "cPlayer.h"

cPlayer::cPlayer() : cCharacter(100)
{
	Init();
	m_charge = new cAnimation(0.01, 24, false);
	m_fire = new cTimer(m_fireDelay[m_radialTan]);
	m_img = IMAGE->FindTexture("IngamePlayerIMG");
	m_black = IMAGE->FindTexture("BlackIMG");
	m_shield = IMAGE->FindTexture("ShieldIMG");
	m_objName = "Player";
}

cPlayer::~cPlayer()
{
	SAFE_DELETE(m_fire);
	SAFE_DELETE(m_charge);
}

void cPlayer::Init()
{
	m_aTime = 10;
	m_bTime = 20;

	m_isAon = true;
	m_isAon = true;
	m_isAdown = false;
	m_isReflect = false;

	m_blackAlpha = 0;

	GAME->m_level = 1;

	m_a = 255;

	m_originSpd = m_moveSpd = 1000.f;

	m_pos = GXY(GAMESIZE / 2, GAMESIZE / 2);

	m_radialTan = true;

	//초기 무기 딜레이
	m_fireDelay[0] = 0.1;
	m_fireDelay[1] = 0.2;
	if (m_fire) m_fire->m_delay = m_fireDelay[m_radialTan];

	//초기 무기 공격력
	m_atk[0] = 10;
	m_atk[1] = 15;

	m_isDamaged = false;
	m_isLive = true;
	m_waitFire = false;
	m_canMove = true;
	m_isNoOutMap = true;

	m_hp = 100;
	m_hpMax = 100;
}

void cPlayer::Release()
{
}

void cPlayer::Update()
{
	if (!m_isLive) { Dead(); return; }
	else if (!m_isActive || SCENE->m_isSceneChange) return;

	Move();
	ChangeWeapon();
	Skill();

	if (m_isDamaged) {
		m_damageTime -= D_TIME;
		if (m_damageTime < 0.f) {
			m_a = 255.f;
			m_isDamaged = false;
		}
	}

	if (m_waitFire) { if (m_fire->Update()) m_waitFire = false; }
	else Fire();

	for (auto iter : ((cEnemyManager*)OBJFIND(ENEMY))->GetEnemy())
		if(iter->GetLive())
			OnCollision(iter);
	for (auto iter : ((cBulletManager*)OBJFIND(BULLET))->GetEnemyBullets())
		if (iter->GetLive())
			OnCollision(iter);
}

void cPlayer::Render()
{
	if (!m_isActive) return;
	IMAGE->Render(m_img, m_pos, m_size, m_rot, true, D3DCOLOR_ARGB((int)m_a, 255, 255, 255));
	if (GAME->m_level > 2 && !m_isAon && m_aTime >= 6) IMAGE->Render(m_shield, m_pos, VEC2(1.f, 1.f), 0, true);
	if (GAME->m_level > 4) IMAGE->Render(m_black, VEC2(WINSIZEX / 2, WINSIZEY / 2), VEC2(1.5, 1.5), 0, true, D3DCOLOR_ARGB((int)m_blackAlpha, 255, 255, 255));
	if (m_isAdown) IMAGE->Render(IMAGE->FindTexture("ChargeEFFECT", m_charge->m_nowFrame), m_pos, VEC2(3, 3), 0, true);
}

void cPlayer::OnCollision(cObject* other)
{
	if (!m_isAon && m_aTime >= 6) {
		if (AABB(GetObjCollider(), other->GetObjCollider())) {
			if (other->GetName() == "EnemyBullet") {
				SOUND->Copy("GetItemSND");
				SOUND->Copy("GetItemSND");
				SOUND->Copy("GetItemSND");
				other->SetLive(false);
			}
		}
		return;
	}

	if (GAME->m_isNotDead || m_isDamaged) return;

	if (AABB(GetCustomCollider(1), other->GetObjCollider())) {
		CAMERA->SetShake(0.2, 30);
		if (other->GetName() != "EnemyBullet") m_hp -= ((cEnemy*)other)->m_atk;
		else m_hp -= ((cBullet*)other)->m_atk;
		SOUND->Copy("PlayerDamageSND");
		auto ingameUI = ((cIngameUI*)UI->FindUI("IngameSceneUI"));
		ingameUI->m_damage->m_a = 255;
		((cBulletManager*)OBJFIND(BULLET))->EnemyBulletReset();

		if (m_hp < 0) m_hp = 0;
		m_isDamaged = true;
		m_damageTime = 1;
		m_a = 128;
	}

	if (m_isLive && m_hp <= 0) {
		m_hp = 0;
		m_isLive = false;
	}
}

void cPlayer::N_Way_Tan(string imageName, int n, int theta, VEC2 pos, VEC2 dir, VEC2 size, float bulletSpd, float atk, bool isRandShot, bool isHoming, bool isFaccel, bool isSaccel)
{
	float rot = D3DXToDegree(atan2(dir.y, dir.x));
	float newRot;
	int randShotX = 0, randShotY = 0;

	if (n % 2) newRot = rot + (n / 2) * theta;
	else newRot = rot + (n / 2) * theta - theta / 2;

	for (size_t i = 0; i < n; ++i) {
		if (isRandShot) {
			randShotX = rand() % 50;
			randShotY = rand() % 50;
			dir.x = cos(D3DXToRadian(newRot + randShotX));
			dir.y = sin(D3DXToRadian(newRot + randShotY));
		}
		else {
			dir.x = cos(D3DXToRadian(newRot));
			dir.y = sin(D3DXToRadian(newRot));
		}
		auto bullet = new cPlayerBullet(imageName, pos, dir, D3DXToDegree(atan2(dir.y, dir.x)) + 90, bulletSpd, size);
		bullet->SetName("PlayerBullet");
		bullet->m_atk = atk;
		((cBulletManager*)OBJFIND(BULLET))->GetPlayerBullets().push_back(bullet);
		newRot -= theta;
	}
}

void cPlayer::N_Straight_Tan(string imageName, int n, int length, VEC2 pos, VEC2 dir, VEC2 size, float bulletSpd, float atk, bool isFaccel, bool isSaccel)
{
	float rot = D3DXToDegree(atan2(dir.y, dir.x));

	if (n % 2) pos.x -= n / 2 * length;
	else pos.x -= n / 2 * length - length / 2;

	for (size_t i = 0; i < n; ++i) {
		auto bullet = new cPlayerBullet(imageName, VEC2(pos.x + i * length, pos.y), dir, rot + 90, bulletSpd, size);
		bullet->SetName("PlayerBullet");
		bullet->m_atk = atk;
		((cBulletManager*)OBJFIND(BULLET))->GetPlayerBullets().push_back(bullet);
	}
}

void cPlayer::Dead()
{
	static double deadTime = 2;

	if (SCENE->GetNowSceneKey() == "IngameScene")
		SOUND->Stop("StageSND");
	else if (SCENE->GetNowSceneKey() == "MidBossScene")
		SOUND->Stop("MidBossSND");
	else if (SCENE->GetNowSceneKey() == "BossScene")
		SOUND->Stop("BossSND");

	if ((int)(deadTime * 10) % 5 == 0) {
		CAMERA->SetShake(0.3, 30);
		SOUND->Copy("PlayerDamageSND");
		SOUND->Copy("PlayerDamageSND");
		SOUND->Copy("PlayerDamageSND");
		EFFECT->AddEffect(new cEffect("ExplosionEFFECT", 32, 0.02, VEC2(m_pos + RandomInsideSquare() * 50), VEC2(0, 0)));
	}

	deadTime -= D_TIME;
	if (deadTime < 0) {
		deadTime = 2;
		m_isLive = true;
		SOUND->Copy("ExplosionSND");
		SOUND->Copy("ExplosionSND");
		SOUND->Copy("ExplosionSND");
		SOUND->Copy("ExplosionSND");
		SOUND->Copy("ExplosionSND");
		SCENE->ChangeScene("TitleScene", "WhiteFade", 3);
	}
}

void cPlayer::Move()
{
	if (!m_canMove) return;

	if (KEYPRESS(VK_SHIFT)) m_moveSpd = m_originSpd * 0.3;
	else m_moveSpd = m_originSpd;

	if (KEYPRESS(VK_LEFT))  m_pos.x -= m_moveSpd * D_TIME;
	if (KEYPRESS(VK_RIGHT)) m_pos.x += m_moveSpd * D_TIME;
	if (KEYPRESS(VK_UP))	m_pos.y -= m_moveSpd * D_TIME;
	if (KEYPRESS(VK_DOWN))  m_pos.y += m_moveSpd * D_TIME;
	NoOutMap();
}

void cPlayer::Fire()
{
	if (KEYPRESS('Z')) {
		m_waitFire = true;
		SOUND->Play("PlayerBulletSND", false);
		if (m_radialTan) {
			switch (GAME->m_level) {
			case 1:
				N_Way_Tan("PlayerBulletIMG", 3, 10, m_pos, VEC2(0, -1), VEC2(3, 3), 2000.f, m_atk[m_radialTan]);
				break;
			case 2:
				N_Way_Tan("PlayerBulletIMG", 3, 10, m_pos, VEC2(0, -1), VEC2(3, 3), 3000.f, m_atk[m_radialTan]);
				break;
			case 3:
				N_Way_Tan("PlayerBulletIMG", 5, 10, m_pos, VEC2(0, -1), VEC2(3, 3), 3000.f, m_atk[m_radialTan]);
				break;
			case 4:
				N_Way_Tan("PlayerBulletIMG", 5, 7, m_pos, VEC2(0, -1), VEC2(3, 3), 3000.f, m_atk[m_radialTan]);
				break;
			case 5:
				N_Way_Tan("PlayerBulletIMG", 8, 5, m_pos, VEC2(0, -1), VEC2(3, 3), 3000.f, m_atk[m_radialTan]);
				break;
			}
		}
		else {
			switch (GAME->m_level) {
			case 1:
				N_Straight_Tan("PlayerBulletIMG", 1, 10, m_pos, VEC2(0, -1), VEC2(3, 3), 3000.f, m_atk[m_radialTan]);
				break;
			case 2:
				N_Straight_Tan("PlayerBulletIMG", 2, 20, m_pos, VEC2(0, -1), VEC2(3, 3), 3000.f, m_atk[m_radialTan]);
				break;
			case 3:
				N_Straight_Tan("PlayerBulletIMG", 3, 30, m_pos, VEC2(0, -1), VEC2(3, 3), 3000.f, m_atk[m_radialTan]);
				break;
			case 4:
				N_Straight_Tan("PlayerBulletIMG", 3, 30, m_pos, VEC2(0, -1), VEC2(3, 3), 3000.f, m_atk[m_radialTan]);
				break;
			case 5:
				N_Straight_Tan("PlayerBulletIMG", 5, 35, m_pos, VEC2(0, -1), VEC2(3, 3), 3000.f, m_atk[m_radialTan]);
				break;
			}
		}
	}
}

void cPlayer::Skill()
{
	static int cnt = 60;

	if (KEYDOWN('X')) {
		if(m_isAon && GAME->m_level > 2) {
			m_isAon = false;
			m_isAdown = true;
			m_charge->m_nowFrame = 0;
		}
		else {
			SOUND->Copy("NoSkillSND");
			FONT->AddFont("아직 사용할 수 없습니다.", GXY(GAMESIZE / 2 - 300, 300), 80, 3, true, D3DCOLOR_XRGB(255, 0, 0));
		}
	}

	if (m_isAdown)
		m_charge->Update();

	if (KEYDOWN(VK_SPACE)) {
		if (m_isBon && GAME->m_level > 4) {
			m_isBon = false;
			m_blackAlpha = 200;
			CAMERA->SetShake(0.2, 100);
			SOUND->Copy("RedCircleSND");
			SOUND->Copy("RedCircleSND");
			SOUND->Copy("RedCircleSND");
			EFFECT->AddEffect(new cEffect("RedCircleEFFECT", 1, 0.02, m_pos, VEC2(0, 0), VEC2(30, 30), VEC2(1, 1), 100));

			((cBulletManager*)OBJFIND(BULLET))->EnemyBulletReset();
			for (auto iter : ((cEnemyManager*)OBJFIND(ENEMY))->GetEnemy()) {
				if (iter->GetName() == "EnemyMeteor") continue;
				((cEnemy*)iter)->m_hp -= m_atk[m_radialTan] * 10;
				if (((cEnemy*)iter)->m_hp <= 0) {
					EFFECT->AddEffect(new cEffect("ExplosionEFFECT", 32, 0.02, VEC2(iter->GetPos() + RandomInsideSquare() * 50), VEC2(0, 0)));
					iter->SetLive(false);
				}
			}
			if (((cEnemyManager*)OBJFIND(ENEMY))->m_boss) {
				((cEnemyManager*)OBJFIND(ENEMY))->m_boss->m_hp -= m_atk[m_radialTan] * 200;
				if(((cEnemyManager*)OBJFIND(ENEMY))->m_boss->m_hp <= 0)
					((cEnemyManager*)OBJFIND(ENEMY))->m_boss->m_isDead = true;
			}
			if (((cEnemyManager*)OBJFIND(ENEMY))->m_midBoss) {
				((cEnemyManager*)OBJFIND(ENEMY))->m_midBoss->m_hp -= m_atk[m_radialTan] * 200;
				if (((cEnemyManager*)OBJFIND(ENEMY))->m_midBoss->m_hp <= 0)
					((cEnemyManager*)OBJFIND(ENEMY))->m_midBoss->m_isDead = true;
			}
		}
		else {
			SOUND->Copy("NoSkillSND");
			FONT->AddFont("아직 사용할 수 없습니다.", GXY(GAMESIZE / 2 - 300, 300), 80, 3, true, D3DCOLOR_XRGB(255, 0, 0));
		}
	}

	if (!m_isAon) {
		m_aTime -= D_TIME;
		if (m_aTime < 0) {
			m_aTime = 10;
			m_isAon = true;
			if (m_isReflect) m_isReflect = false;
		}
		if (m_aTime < 6) if (m_isAdown) m_isAdown = false;

		if (KEYUP('X') && m_isAdown) {
			if (6 <= m_aTime && m_aTime <= 7) {
				m_isReflect = true;
				cnt = 60;
			}
			m_isAdown = false;
		}

		if (m_isReflect) {
			if (cnt % 60 == 0) {
				char str[256];
				sprintf(str, "EnemyBullet%dIMG", rand() % 4);
				((cBulletManager*)OBJFIND(BULLET))->EnemyBulletReset();
				SOUND->Copy("EnemyFireSND");
				SOUND->Copy("EnemyFireSND");
				SOUND->Copy("EnemyFireSND");

				N_Way_Tan(str, 36, 10, m_pos, VEC2(0, 1), VEC2(3, 3), 2000, m_atk[m_radialTan]);
				cnt = 1;
			}
			cnt++;
		}
	}

	if (!m_isBon) {
		m_bTime -= D_TIME;
		if (m_bTime < 0) {
			m_bTime = 20;
			m_isBon = true;
			m_blackAlpha = 0;
		}

		if (m_bTime >= 17) ((cBulletManager*)OBJFIND(BULLET))->EnemyBulletReset();
		else Lerp(m_blackAlpha, 0.0);
	}
}

void cPlayer::ChangeWeapon()
{
	if (KEYDOWN('C')) {
		m_radialTan = !m_radialTan;
		m_fire->m_start = 0.f;
		m_fire->m_delay = m_fireDelay[m_radialTan];
	}
}

void cPlayer::NoOutMap()
{
	if (KEYPRESS(VK_UP)) {
		if(m_pos.y < 0)
			m_pos.y = 0;
	}
	if (KEYPRESS(VK_DOWN)) {
		if(m_pos.y > GAMESIZE)
			m_pos.y = GAMESIZE;
	}
	if (KEYPRESS(VK_LEFT)) {
		if(m_pos.x < GX(0))
			m_pos.x = GX(0);
	}
	if (KEYPRESS(VK_RIGHT)) {
		if(m_pos.x > GX(GAMESIZE))
			m_pos.x = GX(GAMESIZE);
	}
}

