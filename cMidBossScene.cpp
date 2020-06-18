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
	SOUND->Play("MidBossSND", true);

	char str[256];
	sprintf(str, "Stage%dBG", GAME->m_nowStage);
	m_map = IMAGE->FindTexture(str);
	GAME->m_story = 1;
	OBJFIND(PLAYER)->SetActive(true);
	OBJFIND(PLAYER)->SetPos(GXY(GAMESIZE / 2, 800));

	((cEnemyManager*)OBJFIND(ENEMY))->m_midBoss = new cMidBoss;
}

void cMidBossScene::Update()
{
	GAME->Update();
}

void cMidBossScene::Render()
{
	IMAGE->Render(m_map, VEC2(WINSIZEX / 2, WINSIZEY / 2), VEC2(1.5, 1.5), 0, true);
	IMAGE->Render(m_planet, GXY(0, 0), VEC2(0.5, 0.5));
}

void cMidBossScene::Release()
{
	SOUND->Stop("MidBossSND");
	OBJFIND(PLAYER)->SetActive(false);
	((cBulletManager*)OBJFIND(BULLET))->Reset();
	((cEnemyManager*)OBJFIND(ENEMY))->Release();
	((cItemManager*)OBJFIND(ITEM))->Release();
	EFFECT->Reset();
	SAFE_DELETE(((cEnemyManager*)OBJFIND(ENEMY))->m_midBoss);
}
