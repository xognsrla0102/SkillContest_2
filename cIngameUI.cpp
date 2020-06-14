#include "DXUT.h"
#include "cIngameUI.h"

cIngameUI::cIngameUI()
{
	m_bg = IMAGE->FindTexture("IngameBGUI");
	m_exp = IMAGE->FindTexture("IngameEXPUI");

	for (int i = 0; i < 5; ++i) {
		char str[256];
		sprintf(str, "IngameHP%dUI", i);
		m_life[i] = new cImage;
		m_life[i]->m_text = IMAGE->FindTexture(str);
	}
	m_life[0]->m_pos = VEC2(50, 580);
	m_life[1]->m_pos = VEC2(90, 580);
	m_life[2]->m_pos = VEC2(145, 580);
	m_life[3]->m_pos = VEC2(215, 578);
	m_life[4]->m_pos = VEC2(325, 575);
}

cIngameUI::~cIngameUI()
{
	for (auto iter : m_life)
		SAFE_DELETE(iter);
}

void cIngameUI::Init()
{
}

void cIngameUI::Update()
{
}

void cIngameUI::Render()
{
	IMAGE->Render(m_bg, VEC2(0, 0));
	for (int i = 0; i < GAME->m_life; ++i)
		IMAGE->Render(m_life[i]->m_text, m_life[i]->m_pos, VEC2(1, 1), 0, true);

	if(((cPlayer*)OBJFIND(PLAYER))->m_radialTan) IMAGE->DrawFont(": RADIATION", VEC2(1650, 300), "HY태백B", 30);
	else IMAGE->DrawFont(": STRAIGHT", VEC2(1650, 300), "HY태백B", 30);

	char str[3][256] = {
		": AVOID ENEMY BULLET",
		": DESTROY THE PLANET",
		": DESTROY THE BOSS"
	};
	IMAGE->DrawFont(str[GAME->m_story], VEC2(50, 250), "HY태백B", 30);

	RECT rt = {
		0,
		0,
		GAME->m_nowExp / (double)GAME->m_expMax * m_exp->m_info.Width,
		m_exp->m_info.Height
	};
	double result;
	result = GAME->m_nowExp / (double)GAME->m_expMax * 100;
	string str2 = to_string(result);
	str2[5] = '%';
	str2[6] = '\0';

	IMAGE->CropRender(m_exp, VEC2(16, 778), rt);
	IMAGE->DrawFont(str2, VEC2(220, 730), "HY태백B", 30);
}

void cIngameUI::Release()
{
}
