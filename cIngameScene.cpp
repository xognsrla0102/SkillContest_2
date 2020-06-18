#include "DXUT.h"
#include "cIngameScene.h"

cIngameScene::cIngameScene()
{
	m_t = new cTimer(0.1);
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
	OBJFIND(PLAYER)->SetPos(GXY(GAMESIZE / 2, GAMESIZE / 2));

	char str[256];
	sprintf(str, "Stage%dBG", GAME->m_nowStage);
	m_map = new cScroolMap(IMAGE->FindTexture(str));

	m_map->Init();
	m_time = 0;

	//중간보스 이전
	if (GAME->m_isBehind) ((cPlayer*)OBJFIND(PLAYER))->Init();
	else ((cPlayer*)OBJFIND(PLAYER))->m_hp = ((cPlayer*)OBJFIND(PLAYER))->m_hpMax;
}

void cIngameScene::Update()
{
	GAME->Update();

	if (KEYDOWN('O')) GAME->m_isBehind = !GAME->m_isBehind;

	if (KEYDOWN('P')) {
		if (GAME->m_isBehind) m_time = 300;
		else m_time = 390;
	}

	if (m_t->Update()) {
		m_time++;
		LevelDesign();
	}

	if (!GAME->m_isBehind) {
		if (m_time >= 350) {
			((cPlayer*)OBJFIND(PLAYER))->m_canMove = false;
			Lerp(OBJFIND(PLAYER)->GetRefPos(), GXY(GAMESIZE / 2, GAMESIZE / 2), 5);
			if (DistPoint(OBJFIND(PLAYER)->GetPos(), GXY(GAMESIZE / 2, GAMESIZE / 2)) < 0.2) {
				SCENE->ChangeScene("BossEnterScene", "BlackFade", 1.5);
			}
		}
	}
	m_map->Update();
}

void cIngameScene::Render()
{
	m_map->Render();
}

void cIngameScene::Release()
{
	SAFE_DELETE(m_map);

	SOUND->Stop("StageSND");
	auto player = (cPlayer*)OBJFIND(PLAYER);
	player->SetActive(false);
	player->m_canMove = true;
	player->m_aTime = 10;
	player->m_bTime = 20;
	player->m_isAon = true;
	player->m_isAon = true;
	player->m_isAdown = false;
	player->m_isReflect = false;

	((cBulletManager*)OBJFIND(BULLET))->Reset();
	((cEnemyManager*)OBJFIND(ENEMY))->Release();
	((cItemManager*)OBJFIND(ITEM))->Release();
	EFFECT->Reset();
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
		if (m_time == 186) CreateTurret(5, 5, 380);

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
			CreateTurret(5, 5, 380);
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
		if (m_time % 2 == 0 && m_time < 400) {
			CreateMeteor(0, 0, 500);
			CreateMeteor(10, 10, 500);
		}

		if (m_time == 5) {
			CreateRazer(1, 1);
			CreateRazer(5, 5);
			CreateRazer(7, 7);
		}

		if (m_time == 22) CreateMeteor(3, 7, 500);
		if (m_time == 24) CreateMeteor(5, 9, 500);
		if (m_time == 26) CreateMeteor(3, 7, 500);
		if (m_time == 28) CreateMeteor(5, 9, 500);
		if (m_time == 32) CreateMeteor(1, 2, 500);
		if (m_time == 34) CreateMeteor(4, 2, 500);

		for (int i = 0; i < 4; ++i) {
			if (m_time == 40 + 20 * i) {
				CreateMeteor(1, 1, 500);
				CreateMeteor(4, 4, 500);
			}
			if (m_time == 42 + 20 * i) {
				CreateMeteor(1, 1, 500);
				CreateMeteor(4, 4, 500);
			}
			if (m_time == 44 + 20 * i) {
				CreateMeteor(1, 1, 500);
				CreateMeteor(4, 4, 500);
				CreateTurret(2, 2, 500);
				CreateTurret(3, 3, 500);
			}
			if (m_time == 46 + 20 * i)
				CreateMeteor(2, 3, 500);


			if (m_time == 50 + 20 * i) {
				CreateMeteor(6, 6, 500);
				CreateMeteor(9, 9, 500);
			}
			if (m_time == 52 + 20 * i) {
				CreateMeteor(6, 6, 500);
				CreateMeteor(9, 9, 500);
			}
			if (m_time == 54 + 20 * i) {
				CreateMeteor(6, 6, 500);
				CreateMeteor(9, 9, 500);
				CreateTurret(7, 7, 500);
				CreateTurret(8, 8, 500);
			}
			if (m_time == 56 + 20 * i)
				CreateMeteor(7, 8, 500);
		}

		if (m_time == 120)
			CreateTurret(1, 9, 500);

		for (int i = 0; i < 2; ++i) {
			if (m_time == 130 + 20 * i) {
				CreateTurret(1, 1, 500);
				CreateTurret(4, 4, 500);
			}
			if (m_time == 132 + 20 * i) {
				CreateTurret(1, 1, 500);
				CreateTurret(4, 4, 500);
			}
			if (m_time == 134 + 20 * i) {
				CreateMeteor(2, 2, 500);
				CreateMeteor(3, 3, 500);
				CreateTurret(1, 1, 500);
				CreateTurret(4, 4, 500);
			}
			if (m_time == 136 + 20 * i)
				CreateTurret(2, 3, 500);


			if (m_time == 140 + 20 * i) {
				CreateTurret(6, 6, 500);
				CreateTurret(9, 9, 500);
			}
			if (m_time == 142 + 20 * i) {
				CreateTurret(6, 6, 500);
				CreateTurret(9, 9, 500);
			}
			if (m_time == 144 + 20 * i) {
				CreateTurret(6, 6, 500);
				CreateTurret(9, 9, 500);
				CreateMeteor(7, 7, 500);
				CreateMeteor(8, 8, 500);
			}
			if (m_time == 146 + 20 * i)
				CreateTurret(7, 8, 500);
		}

		for (int i = 1; i < 9; ++i) {
			if (m_time == 170 + i * 5)
				CreateRazer(i, i);
		}

		if (m_time == 230) {
			CreateRazer(1, 4);
			CreateRazer(6, 9);
		}

		if (m_time == 280) {
			CreateRazer(3, 7);
			CreateRazer(1, 1);
		}

		if (m_time == 290) 
			CreateRazer(1, 9);

		if (m_time == 300)
			CreateRazer(1, 9);

		if (m_time == 305)
			CreateRazer(1, 9);

		if (m_time == 305)
			CreateRazer(1, 9);
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
	auto& enemy = ((cEnemyManager*)OBJFIND(ENEMY))->GetEnemy();
	for (int i = 0; i < num; ++i) {
		enemy.push_back(
			new cCircle(VEC2(startPos.x + i * 105, startPos.y), speed)
		);
		enemy[enemy.size() - 1]->m_itemName.push_back("ItemHpIMG");
	}
}

void cIngameScene::CreateRazer(int startGrid, int endGrid)
{
	VEC2 startPos = GXY(105 * startGrid, 0);
	int num = endGrid - startGrid + 1;
	auto& enemy = ((cEnemyManager*)OBJFIND(ENEMY))->GetEnemy();
	for (int i = 0; i < num; ++i) {
		enemy.push_back(
			new cRazer(VEC2(startPos.x + i * 105, startPos.y), GAME->m_isBehind)
		);
		enemy[enemy.size() - 1]->m_itemName.push_back("ItemHpIMG");
	}
}

