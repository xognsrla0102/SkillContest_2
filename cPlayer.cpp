#include "DXUT.h"
#include "cPlayer.h"

cPlayer::cPlayer() : cCharacter(100)
{
	//얘는 init에서 어차피 체력 설정해주므로 hp가 의미없음
	Init();
	m_fire = new cTimer(m_fireDelay[m_radialTan]);
	m_img = IMAGE->FindTexture("IngamePlayerIMG");
	m_objName = "Player";
}

cPlayer::~cPlayer()
{
	SAFE_DELETE(m_fire);
}

void cPlayer::Init()
{
	GAME->m_level = 1;

	m_a = 255;

	m_originSpd = m_moveSpd = 1000.f;

	m_damageTime = 2.f;

	m_pos = GXY(GAMESIZE / 2, GAMESIZE / 2);

	m_radialTan = true;

	//초기 무기 딜레이
	m_fireDelay[0] = 0.1;
	m_fireDelay[1] = 0.2;
	if (m_fire) m_fire->m_delay = m_fireDelay[m_radialTan];

	//초기 무기 공격력
	m_atk[0] = 30;
	m_atk[1] = 20;

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
	else if (!m_isActive || !m_isLive) return;

	Move();
	ChangeWeapon();

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
	NoOutMap();
	if (!m_isActive) return;
	IMAGE->Render(m_img, m_pos, m_size, m_rot, true, D3DCOLOR_ARGB((int)m_a, 255, 255, 255));
}

void cPlayer::OnCollision(cObject* other)
{
	if (GAME->m_isNotDead || m_isDamaged) return;

	if (AABB(GetCustomCollider(3), other->GetObjCollider())) {
		CAMERA->SetShake(0.2, 30);
		if (other->GetName() != "EnemyBullet") m_hp -= ((cEnemy*)other)->m_atk;
		else m_hp -= ((cBullet*)other)->m_atk;
		SOUND->Copy("PlayerDamageSND");
		auto ingameUI = ((cIngameUI*)UI->FindUI("IngameSceneUI"));
		ingameUI->m_damage->m_a = 255;
		((cBulletManager*)OBJFIND(BULLET))->Reset();

		if (m_hp < 0) m_hp = 0;
		m_isDamaged = true;
		m_damageTime = 2;
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
				N_Way_Tan("PlayerBulletIMG", 3, 10, m_pos, VEC2(0, -1), VEC2(3, 3), 3000.f, m_atk[m_radialTan]);
				break;
			case 2:
				N_Way_Tan("PlayerBulletIMG", 5, 10, m_pos, VEC2(0, -1), VEC2(3, 3), 3000.f, m_atk[m_radialTan]);
				break;
			case 3:
				N_Way_Tan("PlayerBulletIMG", 8, 10, m_pos, VEC2(0, -1), VEC2(3, 3), 3000.f, m_atk[m_radialTan]);
				break;
			case 4:
				N_Way_Tan("PlayerBulletIMG", 8, 7, m_pos, VEC2(0, -1), VEC2(3, 3), 3000.f, m_atk[m_radialTan]);
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

