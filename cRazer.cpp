#include "DXUT.h"
#include "cRazer.h"

cRazer::cRazer(VEC2 pos, bool isBehind)
	: cEnemy(60 + 50 * GAME->m_level, 10 * GAME->m_nowStage), m_isBehind(isBehind)
{
	//레이저 애니메이션 정보
	m_chargeEffect = new cAnimation(0.03, 24, true);
	m_pos = pos;
	m_size = VEC2(0.5, 0.5);

	m_path = new cPath(m_pos);

	if (isBehind) {
		m_path->AddPoint(VEC2(m_pos.x, GAMESIZE + 100), 5, 0);
		m_path->AddPoint(VEC2(m_pos.x, GAMESIZE + 100), 0, 2);
	}
	else {
		m_path->AddPoint(VEC2(m_pos.x, 200), 5, 0);
		m_path->AddPoint(VEC2(m_pos.x, 200), 0, 2);
	}

	if (pos.x < GX(GAMESIZE / 2))
		m_path->AddPoint(GXY(-250, pos.y), 3, 0);
	else
		m_path->AddPoint(GXY(GAMESIZE + 250, pos.y), 3, 0);

	char str[256];
	sprintf(str, "EnemyRazer%dIMG", GAME->m_nowStage - 1);
	m_img = IMAGE->FindTexture(str);
	m_objName = "EnemyRazer";
}

cRazer::~cRazer()
{
	SAFE_DELETE(m_path);
	SAFE_DELETE(m_chargeEffect);
}

void cRazer::Update()
{
	Move();
	if (CanFire() && m_isChargeTime)
		Fire();

	if(OutMapChk(200)) SetLive(false);
}

void cRazer::Move()
{
	cPointInfo nowPath = m_path->m_endPoint[m_path->m_nowPos];

	//가만히 있기 시작할 때 레이저 로드를 해줘야함
	if (nowPath.m_delay != 0) {
		if (!m_isChargeTime) {
			SOUND->Copy("RazerChargeSND");
			SOUND->Copy("RazerChargeSND");
			SOUND->Copy("RazerChargeSND");
			m_isChargeTime = true;
		}
	}
	//다른 상태일 땐 레이저 취소
	else m_isChargeTime = false;

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

void cRazer::Render()
{
	if (!m_isBehind) {
		IMAGE->Render(m_img, m_pos, m_size, m_rot, true);
		if (m_isChargeTime)
			IMAGE->Render(IMAGE->FindTexture("ChargeRazerIMG", m_chargeEffect->m_nowFrame), VEC2(m_pos.x, m_pos.y + 50), VEC2(3, 3), 0.f, true);
	}
	else {
		if (m_isChargeTime)
			IMAGE->DrawFont("!!!", VEC2(m_pos.x, GAMESIZE - 100), "HY견고딕", 50, D3DCOLOR_XRGB(255, 255, 0));
	}
}


void cRazer::Fire()
{
	m_chargeEffect->Update();

	if (m_chargeEffect->m_nowFrame == m_chargeEffect->m_endFrame - 2) {
		CAMERA->SetShake(0.1, 10);
		SOUND->Copy("RazerFireSND");
	}

	if (m_chargeEffect->m_nowFrame == m_chargeEffect->m_endFrame - 1) {
		VEC2 dir;
		if (m_isBehind) dir = VEC2(0, -1);
		else dir = VEC2(0, 1);
		char str[256];
		sprintf(str, "EnemyBulletRazer%dIMG", GAME->m_nowStage - 1);
		N_Straight_Tan(str, 1, 0, VEC2(m_pos.x, m_pos.y + 600), dir, VEC2(5, 20), 3000, m_atk);
	}
}
