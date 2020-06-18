#include "DXUT.h"
#include "cIngameUI.h"

cIngameUI::cIngameUI()
{
	m_bg = IMAGE->FindTexture("IngameBGUI");
	m_life = IMAGE->FindTexture("IngameHPUI");
	m_exp = IMAGE->FindTexture("IngameEXPUI");
	m_bossHP = IMAGE->FindTexture("IngameBossHPUI");

	m_skillaon = IMAGE->FindTexture("SkillAOnIMG");
	m_skillaoff = IMAGE->FindTexture("SkillAOffIMG");
	m_skillbon = IMAGE->FindTexture("SkillBOnIMG");
	m_skillboff = IMAGE->FindTexture("SkillBOffIMG");

	m_damage = new cImage;
	m_damage->m_text = IMAGE->FindTexture("IngameDamageUI");
}

cIngameUI::~cIngameUI()
{
	SAFE_DELETE(m_damage);
}

void cIngameUI::Init()
{
	m_damage->m_a = 0;
}

void cIngameUI::Update()
{
	if (((cPlayer*)OBJFIND(PLAYER))->m_isDamaged)
		Lerp(m_damage->m_a, 0.0, 1);
	else m_damage->m_a = 0;
}

void cIngameUI::Render()
{
	IMAGE->Render(m_damage->m_text, GXY(-3, -3), VEC2(1, 1), 0, false, m_damage->m_color);

	IMAGE->Render(m_bg, VEC2(0, 0));
	if(((cPlayer*)OBJFIND(PLAYER))->m_radialTan) IMAGE->DrawFont(": RADIATION", VEC2(1650, 430), "HY견고딕", 30);
	else IMAGE->DrawFont(": STRAIGHT", VEC2(1650, 430), "HY견고딕", 30);

	auto player = (cPlayer*)OBJFIND(PLAYER);
	if (player->m_isAon) IMAGE->Render(m_skillaon, GXY(1180, 830), VEC2(1, 1), 0, true);
	else {
		IMAGE->Render(m_skillaoff, GXY(1180, 830), VEC2(1, 1), 0, true);
		 if (GAME->m_level < 3) IMAGE->DrawFont("필요레벨 3", GXY(1130, 820), "HY견고딕");
		 else IMAGE->DrawFont(to_string((int)player->m_aTime), GXY(1170, 820), "HY견고딕");
	}
	if (player->m_isBon) IMAGE->Render(m_skillbon, GXY(1350, 830), VEC2(1, 1), 0, true);
	else {
		IMAGE->Render(m_skillboff, GXY(1350, 830), VEC2(1, 1), 0, true);
		if(GAME->m_level < 5) IMAGE->DrawFont("필요레벨 5", GXY(1300, 820), "HY견고딕");
		else IMAGE->DrawFont(to_string((int)player->m_bTime), GXY(1330, 820), "HY견고딕");
	}

	char str[3][256] = {
		": AVOID ENEMY BULLET",
		": DESTROY THE PLANET",
		": DESTROY THE BOSS"
	};
	IMAGE->DrawFont(str[GAME->m_story], VEC2(50, 200), "HY견고딕", 25);

	char tmp[256];
	sprintf(tmp, "%07d", GAME->m_score);
	IMAGE->DrawFont(tmp, VEC2(1550, 130), "HY견고딕", 70);

	RECT rt = {
		0, 0,
		player->m_hp / (double)player->m_hpMax * m_life->m_info.Width,
		m_life->m_info.Height
	};

	double result;
	result = player->m_hp / (double)player->m_hpMax * 100;
	string str2 = to_string(result);
	str2[5] = '%';
	str2[6] = '\0';
	IMAGE->CropRender(m_life, VEC2(10, 450), rt);
	IMAGE->DrawFont("잔여 체력 : " + str2, VEC2(150, 380), "HY견고딕", 25);

	auto midBoss = ((cEnemyManager*)OBJFIND(ENEMY))->m_midBoss;
	auto boss = ((cEnemyManager*)OBJFIND(ENEMY))->m_boss;

	if (midBoss) {
		rt = {
			0, 0,
			(LONG)(midBoss->m_hp / (double)midBoss->m_hpMax * m_bossHP->m_info.Width),
			(LONG)m_bossHP->m_info.Height
		};
		IMAGE->CropRender(m_bossHP, GXY(30, 30), rt);
	}
	if (boss) {
		rt = {
			0, 0,
			(LONG)(boss->m_hp / (double)boss->m_hpMax * m_bossHP->m_info.Width),
			(LONG)m_bossHP->m_info.Height
		};
		IMAGE->CropRender(m_bossHP, GXY(30, 30), rt);
	}

	rt = {
		0, 0,
		(LONG)(GAME->m_nowExp / (double)GAME->m_expMax * m_exp->m_info.Width),
		(LONG)m_exp->m_info.Height
	};
	result = GAME->m_nowExp / (double)GAME->m_expMax * 100;
	str2 = to_string(result);
	str2[5] = '%';
	str2[6] = '\0';

	IMAGE->CropRender(m_exp, VEC2(16, 778), rt);
	IMAGE->DrawFont("현재 경험치 : " + str2, VEC2(200, 720), "HY견고딕", 20);
	IMAGE->DrawFont(to_string(GAME->m_level), VEC2(110, 830), "HY견고딕", 20);

	if (GAME->m_isDebugInfo) {
		IMAGE->DrawFont("플레이어 레벨 : " + to_string(GAME->m_level), VEC2(1150, 40), "HY견고딕", 25);
		IMAGE->DrawFont("누적 경험치  : " + to_string(GAME->m_score), VEC2(1150, 80), "HY견고딕", 25);
		for (int i = 2; i <= 4; ++i)
			IMAGE->DrawFont(to_string(i) + "레벨 필요한 경험치 : " + to_string(4000 + 1500 * (i - 2)), VEC2(1150, 100 + 40 * (i - 1)), "HY견고딕", 25);
	}
}

void cIngameUI::Release()
{
}
