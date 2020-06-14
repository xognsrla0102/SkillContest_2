#include "DXUT.h"
#include "cIngameScene.h"

cIngameScene::cIngameScene()
{
	m_t = new cTimer(0.1);
	m_map = new cScroolMap(IMAGE->FindTexture("Stage1BG"));
}

cIngameScene::~cIngameScene()
{
	SAFE_DELETE(m_t);
	SAFE_DELETE(m_map);
}

void cIngameScene::Init()
{
	SOUND->Play("StageSND", true);

	OBJFIND(PLAYER)->SetActive(true);
	((cPlayer*)OBJFIND(PLAYER))->Init();
	m_time = 0;
}

void cIngameScene::Update()
{
	if (m_t->Update()) {
		m_time++;
		DrawMap();
	}

	m_map->Update();
}

void cIngameScene::Render()
{
	m_map->Render();
}

void cIngameScene::Release()
{
	SOUND->Stop("StageSND");
	OBJFIND(PLAYER)->SetActive(false);
	((cBulletManager*)OBJFIND(BULLET))->Reset();
}

void cIngameScene::DrawMap()
{
	switch (m_time) {
	case 10:
		//((cEnemyManager*)OBJFIND(ENEMY))->GetEnemy().push_back(
		//	new cMeteor("EnemyMeteorIMG", GXY(GAMESIZE / 2, GAMESIZE / 2), VEC2(1, 1), 0, 300)
		//);
		break;
	case 20:
		break;
	case 30:
		break;
	}
}
