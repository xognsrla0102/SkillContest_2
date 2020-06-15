#include "DXUT.h"
#include "cIngameUI.h"

cIngameUI::cIngameUI()
{
	m_bg = IMAGE->FindTexture("IngameBGUI");
	m_life = IMAGE->FindTexture("IngameHPUI");
	m_exp = IMAGE->FindTexture("IngameEXPUI");

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
	if(((cPlayer*)OBJFIND(PLAYER))->m_radialTan) IMAGE->DrawFont(": RADIATION", VEC2(1650, 430), "HY°ß°íµñ", 30);
	else IMAGE->DrawFont(": STRAIGHT", VEC2(1650, 430), "HY°ß°íµñ", 30);

	char str[3][256] = {
		": AVOID ENEMY BULLET",
		": DESTROY THE PLANET",
		": DESTROY THE BOSS"
	};
	IMAGE->DrawFont(str[GAME->m_story], VEC2(50, 200), "HY°ß°íµñ", 25);

	char tmp[256];
	sprintf(tmp, "%07d", GAME->m_score);
	IMAGE->DrawFont(tmp, VEC2(1550, 130), "HY°ß°íµñ", 70);

	auto player = (cPlayer*)OBJFIND(PLAYER);

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
	IMAGE->DrawFont("ÀÜ¿© Ã¼·Â : " + str2, VEC2(150, 380), "HY°ß°íµñ", 25);

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
	IMAGE->DrawFont("ÇöÀç °æÇèÄ¡ : " + str2, VEC2(200, 720), "HY°ß°íµñ", 20);
	IMAGE->DrawFont(to_string(GAME->m_level), VEC2(110, 830), "HY°ß°íµñ", 20);
}

void cIngameUI::Release()
{
}
