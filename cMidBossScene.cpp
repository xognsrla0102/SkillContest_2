#include "DXUT.h"
#include "cMidBossScene.h"

cMidBossScene::cMidBossScene()
{
	m_midBoss = new cMidBoss;
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

	m_midBoss->SetPos(GXY(GAMESIZE / 2, 200));
	m_midBoss->SetSize(VEC2(2.5, 2.5));
}

void cMidBossScene::Update()
{
	m_midBoss->Update();
}

void cMidBossScene::Render()
{
	IMAGE->Render(m_map, VEC2(0, 0));
	m_midBoss->Render();
}

void cMidBossScene::Release()
{
	OBJFIND(PLAYER)->SetActive(false);
	SAFE_DELETE(m_midBoss);
}
