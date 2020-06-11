#include "DXUT.h"
#include "cPlayer.h"

cPlayer::cPlayer()
{
	Init();
	m_fire = new cTimer(m_fireDelay[m_radialTan]);
	m_img = new cImage;
	m_objName = "Player";
}

cPlayer::~cPlayer()
{
	SAFE_DELETE(m_fire);
	SAFE_DELETE(m_img);
}

void cPlayer::Init()
{
	GAME->m_level = 1;

	m_originSpd = m_moveSpd = 500.f;

	m_damageTime = 0.f;

	m_pos = VEC2(GAMESIZE / 2, 700);

	m_radialTan = true;

	//초기 무기 딜레이
	m_fireDelay[0] = 1;
	m_fireDelay[1] = 0.3;
	if (m_fire) m_fire->m_delay = m_fireDelay[m_radialTan];

	//초기 무기 공격력
	m_atk[0] = 2;
	m_atk[1] = 1;

	m_isDamaged = false;
	m_isLive = true;
	m_waitFire = false;

	m_hp = 20;
	m_hpMax = 20;
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
		m_damageTime += D_TIME;
		if (m_damageTime > 2.f) {
			m_img->m_a = 255.f;
			m_damageTime = 0.f;
			m_isDamaged = false;
		}
	}

	if (m_waitFire) { if (m_fire->Update()) m_waitFire = false; }
	else Fire();
}

void cPlayer::Render()
{
	if (!m_isActive) return;
	IMAGE->Render(m_img->m_text, m_pos, m_size, m_rot, true, m_img->m_color);
}

void cPlayer::OnCollision(cObject* other)
{
	if (GAME->m_isNotDead || m_isDamaged) return;

	if (m_isLive && m_hp <= 0) {
		m_hp = 0;
		m_isLive = false;
	}
}

void cPlayer::Dead()
{
	
}

void cPlayer::ChangeWeapon()
{
	//if (KEYDOWN(i)) {
	//	m_nowWeapon = ;
	//	m_fire->m_start = 0.f;
	//	m_fire->m_delay = m_fireDelay[m_nowWeapon];
	//}
}

void cPlayer::Move()
{
	if (KEYPRESS(VK_SHIFT)) m_moveSpd = m_originSpd * 0.5;
	else m_moveSpd = m_originSpd;

	if (KEYPRESS(VK_LEFT)) {
		m_pos.x -= m_moveSpd * D_TIME;
	}
	if (KEYPRESS(VK_RIGHT)) {
		m_pos.x += m_moveSpd * D_TIME;
	}
	if (KEYPRESS(VK_UP)) {
		m_pos.y -= m_moveSpd * D_TIME;
	}
	if (KEYPRESS(VK_DOWN)) {
		m_pos.y += m_moveSpd * D_TIME;
	}
}

void cPlayer::Fire()
{
	if (KEYPRESS(VK_SPACE)) {
		char str[256] = "";
		if (m_radialTan) sprintf(str, "Weapon0SND");
		else  sprintf(str, "Weapon1SND");
		SOUND->Copy(str);

		m_waitFire = true;

		//auto bullet = (cBulletManager*)OBJFIND(BULLET);
		//
		//if (m_radialTan) {
		//	switch (GAME->m_level) {
		//	case 1:
		//	case 2:
		//		bullet->N_Way_Tan("PlayerBullet", "PlayerBullet0IMG", 3, 10, m_pos, VEC2(0, -1), VEC2(1.5, 1.5), 150.f, 0, false, false, false, true);
		//		break;
		//	case 3:
		//		bullet->N_Way_Tan("PlayerBullet", "PlayerBullet0IMG", 5, 10, m_pos, VEC2(0, -1), VEC2(1.5, 1.5), 200.f, 0, false, false, false, true);
		//		break;
		//	case 4:
		//		bullet->N_Way_Tan("PlayerBullet", "PlayerBullet0IMG", 8, 10, m_pos, VEC2(0, -1), VEC2(1.5, 1.5), 200.f, 0, false, false, false, true);
		//		break;
		//	case 5:
		//		bullet->N_Way_Tan("PlayerBullet", "PlayerBullet0IMG", 8, 10, m_pos, VEC2(0, -1), VEC2(1.5, 1.5), 250.f, 0, false, false, false, true);
		//		break;
		//	}
		//}
		//else {
		//	switch (GAME->m_level) {
		//	case 1:
		//		bullet->N_Straight_Tan("PlayerBullet", "PlayerBullet1IMG", 1, 10, m_pos, VEC2(0, -1), VEC2(1.5, 1.5), 500.f, 0, true);
		//		break;
		//	case 2:
		//		bullet->N_Straight_Tan("PlayerBullet", "PlayerBullet1IMG", 2, 15, m_pos, VEC2(0, -1), VEC2(1.5, 1.5), 500.f, 0, true);
		//		break;
		//	case 3:
		//		bullet->N_Straight_Tan("PlayerBullet", "PlayerBullet1IMG", 3, 20, m_pos, VEC2(0, -1), VEC2(1.5, 1.5), 800.f, 0, true);
		//		break;
		//	case 4:
		//		bullet->N_Straight_Tan("PlayerBullet", "PlayerBullet1IMG", 3, 20, m_pos, VEC2(0, -1), VEC2(1.5, 1.5), 1000.f, 0, true);
		//		break;
		//	case 5:
		//		bullet->N_Straight_Tan("PlayerBullet", "PlayerBullet1IMG", 4, 20, m_pos, VEC2(0, -1), VEC2(1.5, 1.5), 1000.f, 0, true);
		//		break;
		//	}
		//}
	}
}

