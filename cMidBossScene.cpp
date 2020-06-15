#include "DXUT.h"
#include "cMidBossScene.h"

cMidBossScene::cMidBossScene()
{
	m_planet = IMAGE->FindTexture("PlanetIMG");
}

cMidBossScene::~cMidBossScene()
{
	Release();
}

void cMidBossScene::Init()
{
	char str[256];
	sprintf(str, "Stage%dBG", GAME->m_nowStage);
	m_map = IMAGE->FindTexture(str);
	GAME->m_story++;
	OBJFIND(PLAYER)->SetActive(true);
	OBJFIND(PLAYER)->SetPos(GXY(GAMESIZE / 2, GAMESIZE / 2));

	((cEnemyManager*)OBJFIND(ENEMY))->m_midBoss = new cMidBoss;
}

void cMidBossScene::Update()
{
}

void cMidBossScene::Render()
{
	IMAGE->Render(m_map, VEC2(0, 0));
	IMAGE->Render(m_planet, GXY(0, 0), VEC2(0.5, 0.5));
}

void cMidBossScene::Release()
{
	OBJFIND(PLAYER)->SetActive(false);
	SAFE_DELETE(((cEnemyManager*)OBJFIND(ENEMY))->m_midBoss);
}
