#include "DXUT.h"
#include "cMidBossEnterScene.h"

cMidBossEnterScene::cMidBossEnterScene()
{
	m_t = new cTimer(0.1);

	m_white = IMAGE->FindTexture("WhiteIMG");
	m_black = IMAGE->FindTexture("BlackIMG");

	m_player = new cImage;
	m_planet = new cImage;
	m_planet->m_text = IMAGE->FindTexture("PlanetIMG");
	m_player->m_text = IMAGE->FindTexture("IngamePlayerIMG");
}

cMidBossEnterScene::~cMidBossEnterScene()
{
	SAFE_DELETE(m_t);
	SAFE_DELETE(m_player);
	SAFE_DELETE(m_planet);
	SAFE_DELETE(m_map);
}

void cMidBossEnterScene::Init()
{
	char str[256];
	sprintf(str, "Stage%dBG", GAME->m_nowStage);
	m_map = new cScroolMap(IMAGE->FindTexture(str));

	sprintf(str, "EnemyMidBoss%dIMG", GAME->m_nowStage - 1);
	m_midBoss = IMAGE->FindTexture(str);

	m_planet->m_pos = GXY(GAMESIZE / 2, -300);
	m_player->m_pos = GXY(GAMESIZE / 2, GAMESIZE + 200);
	m_map->m_mapSpd = 5000;
	m_time = 0;
	m_alpha = 0;
	m_bAlpha = 255;
	m_bossAlpha = 0;

	m_blackPos[0] = VEC2(0, -GAMESIZE);
	m_blackPos[1] = VEC2(0, GAMESIZE);
}

void cMidBossEnterScene::Update()
{
	if (m_t->Update()) {
		m_time++;
		EnterBoss();
	}

	if (20 <= m_time && m_time <= 30) {
		Lerp(m_blackPos[0], VEC2(0, -GAMESIZE + 400), 5);
		Lerp(m_blackPos[1], VEC2(0, GAMESIZE - 400), 5);
		Lerp(CAMERA->m_size, VEC2(0.5, 0.5), 3);
	}

	if (35 <= m_time && m_time <= 45) {
		m_bAlpha = 0;
		Lerp(CAMERA->m_size, VEC2(1.2, 1.2), 5);
	}
	
	if (35 <= m_time && m_time <= 50) {
		VEC2 dir;
		for (int i = 0; i < 360; i += 12) {
			dir.x = cos(D3DXToRadian(i));
			dir.y = sin(D3DXToRadian(i));
			char str[256];
			sprintf(str, "EnemyBullet%dIMG", rand() % 4);
			((cBulletManager*)OBJFIND(BULLET))->GetEnemyBullets().push_back(
				new cEnemyBullet(str, GXY(GAMESIZE / 2, 500), dir, 0, 400, false, true, VEC2(2, 2))
			);
		}
	}

	m_map->Update();
	Lerp(m_map->m_mapSpd, 100.0, 3);
	Lerp(m_planet->m_pos, GXY(GAMESIZE / 2, 200), 3);
	Lerp(m_player->m_pos, GXY(GAMESIZE / 2, GAMESIZE - 200), 3);
}

void cMidBossEnterScene::Render()
{
	m_map->Render();

	IMAGE->Render(m_planet->m_text, m_planet->m_pos, VEC2(0.8, 0.8), 0, true);
	IMAGE->Render(m_player->m_text, m_player->m_pos, VEC2(1, 1), 0, true);
	IMAGE->Render(m_midBoss, GXY(GAMESIZE / 2, 550), VEC2(3, 3), 0, true, D3DCOLOR_ARGB(m_bossAlpha, 255, 255, 255));

	IMAGE->Render(m_white, VEC2(0, 0), VEC2(1, 1), 0, false, D3DCOLOR_ARGB(m_alpha, 255, 255, 255));

	IMAGE->Render(m_black, m_blackPos[0], VEC2(1, 1), 0, false, D3DCOLOR_ARGB(m_bAlpha, 255, 255, 255));
	IMAGE->Render(m_black, m_blackPos[1], VEC2(1, 1), 0, false, D3DCOLOR_ARGB(m_bAlpha, 255, 255, 255));

	if (20 <= m_time && m_time <= 40)
		IMAGE->DrawFont("DESTROY THE PLANET!!!!", GXY(GAMESIZE / 2 - 300, 300), "HY°ß°íµñ", 50, D3DCOLOR_XRGB(255, 0, 0));
}

void cMidBossEnterScene::Release()
{
	SAFE_DELETE(m_map);
	CAMERA->m_size = VEC2(1, 1);
}

void cMidBossEnterScene::EnterBoss()
{
	if (10 <= m_time && m_time <= 15) {
		if (m_time == 12) m_alpha = 255;
		if (m_time == 13) m_alpha = 0;
		if (m_time == 14) m_alpha = 255;
		m_bossAlpha = 255;
		if (m_time == 15) m_alpha = 0;
	}

	if (m_time == 20) CAMERA->SetShake(0.2, 50);

	if (m_time == 40) SCENE->ChangeScene("MidBossScene", "WhiteFade", 2);
}

