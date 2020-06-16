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
	SOUND->Play("TitleSND", true);
	OBJFIND(PLAYER)->SetActive(true);
	OBJFIND(PLAYER)->SetPos(GXY(GAMESIZE / 2, GAMESIZE / 2));
	m_map->Init();
	m_time = 0;
	GAME->m_isBehind = false;
}

void cIngameScene::Update()
{
	if (KEYDOWN('P')) m_time = 300;

	if (m_t->Update()) {
		m_time++;
		LevelDesign();
	}

	m_map->Update();
}

void cIngameScene::Render()
{
	m_map->Render();
}

void cIngameScene::Release()
{
	SOUND->Stop("TitleSND");
	OBJFIND(PLAYER)->SetActive(false);
	((cBulletManager*)OBJFIND(BULLET))->Reset();
	((cEnemyManager*)OBJFIND(ENEMY))->Release();
}

void cIngameScene::LevelDesign()
{
	if (GAME->m_isBehind) {
		if (m_time % 2 == 0) {
			CreateMeteor(0, 0, 380);
			CreateMeteor(10, 10, 380);
		}

		if (30 <= m_time && m_time <= 40) {
			if (m_time % 2 == 0) CreateMeteor(1, 3, 380);
			if (m_time % 4 == 0) CreateTurret(1, 3, 380);
		}
		if (40 <= m_time && m_time <= 50) {
			if (m_time % 2 == 0) CreateMeteor(7, 9, 380);
			if (m_time % 4 == 0) CreateTurret(7, 9, 380);
		}

		if (m_time == 50) CreateMeteor(5, 5, 380);
		if (m_time == 52) CreateMeteor(5, 5, 380);
		if (m_time == 54) CreateMeteor(4, 6, 380);
		if (m_time == 56) CreateMeteor(4, 6, 380);
		if (m_time == 58) CreateMeteor(3, 7, 380);
		if (m_time == 58) CreateTurret(5, 5, 380);
		if (m_time == 60) CreateMeteor(3, 7, 380);
		if (m_time == 60) CreateTurret(5, 5, 380);
		if (m_time == 62) CreateMeteor(4, 6, 380);
		if (m_time == 64) CreateMeteor(4, 6, 380);
		if (m_time == 66) CreateMeteor(5, 5, 380);
		if (m_time == 68) CreateMeteor(5, 5, 380);


		if (m_time == 80) {
			CreateMeteor(1, 1, 380);
			CreateMeteor(9, 9, 380);
		}
		if (m_time == 82) {
			CreateMeteor(2, 2, 380);
			CreateMeteor(8, 8, 380);
		}
		if (m_time == 84) {
			CreateMeteor(3, 3, 380);
			CreateMeteor(7, 7, 380);
		}
		if (m_time == 86) {
			CreateMeteor(4, 4, 380);
			CreateTurret(1, 1, 380);
			CreateTurret(3, 3, 380);
			CreateMeteor(6, 6, 380);
			CreateTurret(9, 9, 380);
			CreateTurret(7, 7, 380);
		}
		if (m_time == 88) {
			CreateMeteor(3, 3, 380);
			CreateMeteor(7, 7, 380);
		}
		if (m_time == 90) {
			CreateMeteor(2, 2, 380);
			CreateMeteor(8, 8, 380);
		}
		if (m_time == 92) {
			CreateMeteor(1, 1, 380);
			CreateMeteor(9, 9, 380);
		}

		if (98 <= m_time && m_time <= 130) {
			if (m_time % 2 == 0) CreateMeteor(2, 8, 380);
		}

		if (140 <= m_time && m_time <= 150) {
			if (m_time % 2 == 0) {
				CreateMeteor(3, 3, 380);
				CreateMeteor(7, 7, 380);
			}
			if (m_time == 145) {
				CreateRazer(2, 2);
				CreateRazer(8, 8);
			}
		}

		if (m_time == 160) {
			CreateRazer(5, 5);
		}

		if (m_time == 180) CreateMeteor(5, 5, 380);
		if (m_time == 182) CreateMeteor(5, 5, 380);
		if (m_time == 184) CreateMeteor(5, 5, 380);
		if (m_time == 186) CreateMeteor(3, 7, 380);
		if (m_time == 188) CreateMeteor(5, 5, 380);
		if (m_time == 190) CreateMeteor(5, 5, 380);
		if (m_time == 192) CreateMeteor(5, 5, 380);

		if (m_time == 200) {
			CreateMeteor(3, 3, 380);
			CreateMeteor(7, 7, 380);
		}
		if (m_time == 202) {
			CreateMeteor(4, 4, 380);
			CreateMeteor(6, 6, 380);
		}
		if (m_time == 204) {
			CreateMeteor(5, 5, 380);
		}
		if (m_time == 206) {
			CreateMeteor(4, 4, 380);
			CreateMeteor(6, 6, 380);
		}
		if (m_time == 208) {
			CreateMeteor(3, 3, 380);
			CreateMeteor(7, 7, 380);
		}

		if (m_time == 220 || m_time == 228) CreateMeteor(4, 5, 380);
		if (m_time == 222 || m_time == 224 || m_time == 226) {
			CreateMeteor(3, 3, 380);
			CreateMeteor(6, 6, 380);
		}

		if (m_time == 230 || m_time == 238) CreateMeteor(2, 3, 380);
		if (m_time == 232 || m_time == 234 || m_time == 236) {
			CreateMeteor(1, 1, 380);
			CreateMeteor(4, 4, 380);
		}

		if (m_time == 230 || m_time == 232 || m_time == 234 || m_time == 236 || m_time == 238) {
			if (m_time == 234) CreateMeteor(7, 8, 380);
			CreateMeteor(7, 7, 380);
		}

		if (250 <= m_time && m_time <= 300) {
			if (m_time % 2 == 0) CreateMeteor(5, 5, 400);
			if (m_time % 16 == 0) {
				CreateCircle(3, 3, 400);
				CreateCircle(7, 7, 400);
			}
			if (m_time % 14 == 0) CreateMeteor(2, 8, 400);
		}
		if (m_time == 320) SCENE->ChangeScene("MidBossEnterScene", "BlackFade", 3);
	}
	else {
		if (m_time % 2 == 0) {
			CreateMeteor(0, 0, 500);
			CreateMeteor(10, 10, 500);
		}

		if (m_time == 32) CreateMeteor(3, 7, 500);
		if (m_time == 34) CreateMeteor(3, 7, 500);
		if (m_time == 36) CreateMeteor(5, 9, 500);
		if (m_time == 38) CreateMeteor(5, 9, 500);
		if (m_time == 40) CreateMeteor(3, 7, 500);
		if (m_time == 42) CreateMeteor(3, 7, 500);

		if(46 <= m_time && m_time <= 60)
			CreateMeteor(3, 7, 500);
	}
}

void cIngameScene::CreateMeteor(int startGrid, int endGrid, int speed)
{
	//startGrid 0 ~ 10번 그리드로 그리드 나뉨
	VEC2 startPos = GXY(105 * startGrid, -100);
	int num = endGrid - startGrid + 1;
	//한줄에 운석이 최대 10개 들갈 수 있음
	for (int i = 0; i < num; ++i)
		((cEnemyManager*)OBJFIND(ENEMY))->GetEnemy().push_back(
			new cMeteor(VEC2(startPos.x + i * 105, startPos.y), rand() % 36 * 10, speed)
		);
}

void cIngameScene::CreateTurret(int startGrid, int endGrid, int speed)
{
	VEC2 startPos = GXY(105 * startGrid, -100);
	int num = endGrid - startGrid + 1;
	for (int i = 0; i < num; ++i)
		((cEnemyManager*)OBJFIND(ENEMY))->GetEnemy().push_back(
			new cTurret(VEC2(startPos.x + i * 105, startPos.y), speed)
		);
}

void cIngameScene::CreateCircle(int startGrid, int endGrid, int speed)
{
	VEC2 startPos = GXY(105 * startGrid, -100);
	int num = endGrid - startGrid + 1;
	for (int i = 0; i < num; ++i)
		((cEnemyManager*)OBJFIND(ENEMY))->GetEnemy().push_back(
			new cCircle(VEC2(startPos.x + i * 105, startPos.y), speed)
		);
}

void cIngameScene::CreateRazer(int startGrid, int endGrid)
{
	VEC2 startPos = GXY(105 * startGrid, -100);
	if (GAME->m_isBehind) startPos.y = GAMESIZE + 100;

	int num = endGrid - startGrid + 1;
	for (int i = 0; i < num; ++i)
		((cEnemyManager*)OBJFIND(ENEMY))->GetEnemy().push_back(
			new cRazer(VEC2(startPos.x + i * 105, startPos.y), GAME->m_isBehind)
		);
}

