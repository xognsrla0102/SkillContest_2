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
	m_map->Init();
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
	((cEnemyManager*)OBJFIND(ENEMY))->Release();
}

void cIngameScene::DrawMap()
{
	if (m_time == 10 || m_time == 20 || m_time == 30) {
		CreateMeteor(0, 4);
		CreateTurret(0, 4);

		CreateMeteor(6, 10);
		CreateTurret(6, 10);

		//((cEnemyManager*)OBJFIND(ENEMY))->GetEnemy().push_back(
		//	new cRotate("EnemyRotateIMG", GXY(GAMESIZE / 2, GAMESIZE / 2), VEC2(1, 1))
		//);
	}
}

void cIngameScene::CreateMeteor(int startGrid, int endGrid)
{
	//startGrid 0 ~ 10번 그리드로 그리드 나뉨
	VEC2 startPos = GXY(105 * startGrid, -100);
	int num = endGrid - startGrid + 1;
	//한줄에 운석이 최대 10개 들갈 수 있음
	for (int i = 0; i < num; ++i)
		((cEnemyManager*)OBJFIND(ENEMY))->GetEnemy().push_back(
			new cMeteor("EnemyMeteorIMG", VEC2(startPos.x + i * 105, startPos.y), VEC2(1.5, 1.5), rand() % 36 * 10, 200)
		);
}

void cIngameScene::CreateTurret(int startGrid, int endGrid)
{
	VEC2 startPos = GXY(105 * startGrid, -100);
	int num = endGrid - startGrid + 1;
	for (int i = 0; i < num; ++i)
		((cEnemyManager*)OBJFIND(ENEMY))->GetEnemy().push_back(
			new cTurret("EnemyTurretIMG", VEC2(startPos.x + i * 105, startPos.y), VEC2(1.5, 1.5), 200)
		);
}

