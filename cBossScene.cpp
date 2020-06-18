#include "DXUT.h"
#include "cBossScene.h"

cBossScene::cBossScene()
{
}

cBossScene::~cBossScene()
{
	Release();
}

void cBossScene::Init()
{
	SOUND->Play("BossSND", true);
	char str[256];
	sprintf(str, "Stage%dBG", GAME->m_nowStage);
	m_map = IMAGE->FindTexture(str);
	OBJFIND(PLAYER)->SetActive(true);
	OBJFIND(PLAYER)->SetPos(GXY(GAMESIZE / 2, 800));
	((cEnemyManager*)OBJFIND(ENEMY))->m_boss = new cBoss;
}

void cBossScene::Update()
{
	GAME->Update();
}

void cBossScene::Render()
{
	IMAGE->Render(m_map, VEC2(WINSIZEX / 2, WINSIZEY / 2), VEC2(1.5, 1.5), 0, true);
}

void cBossScene::Release()
{
	SOUND->Stop("BossSND");
	OBJFIND(PLAYER)->SetActive(false);
	SAFE_DELETE(((cEnemyManager*)OBJFIND(ENEMY))->m_boss);
}

