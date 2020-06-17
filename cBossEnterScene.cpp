#include "DXUT.h"
#include "cBossEnterScene.h"

cBossEnterScene::cBossEnterScene()
{
	m_t = new cTimer(0.1);
	m_white = IMAGE->FindTexture("WhiteIMG");
	m_black = IMAGE->FindTexture("BlackIMG");

	m_player = new cImage;
	m_player->m_text = IMAGE->FindTexture("IngamePlayerIMG");

	m_boss = new cImage;

	char str[256];
	sprintf(str, "EnemyRazer%dIMG", GAME->m_nowStage - 1);
	for (int i = 0; i < 3; ++i) {
		m_leftRazer.push_back(new cImage);
		m_rightRazer.push_back(new cImage);
		m_leftRazer[i]->m_text = 
		m_rightRazer[i]->m_text = IMAGE->FindTexture(str);
	}
}

cBossEnterScene::~cBossEnterScene()
{
	SAFE_DELETE(m_t);
	SAFE_DELETE(m_player);
	SAFE_DELETE(m_boss);
	for(auto iter : m_leftRazer)
		SAFE_DELETE(iter);
	m_leftRazer.clear();
	for (auto iter : m_rightRazer)
		SAFE_DELETE(iter);
	m_rightRazer.clear();
}

void cBossEnterScene::Init()
{
	SOUND->Play("TitleSND", true);

	char str[256];
	sprintf(str, "Stage%dBG", GAME->m_nowStage);
	m_bg = IMAGE->FindTexture(str);

	sprintf(str, "EnemyBoss%dIMG", GAME->m_nowStage - 1);
	m_boss->m_text = IMAGE->FindTexture(str);
	m_boss->m_pos = GXY(GAMESIZE / 2, -100);

	time = 0;
	m_player->m_pos = GXY(GAMESIZE / 2, GAMESIZE + 100);
	whiteAlpha = blackAlpha = 0;

	for (int i = 0; i < 3; ++i) {
		m_leftRazer[i]->m_pos = GXY(-1000, 600 + i * 200);
		m_rightRazer[i]->m_pos = GXY(GAMESIZE + 1000, 600 + i * 200);
	}
}

void cBossEnterScene::Update()
{
	if (m_t->Update()) {
		time++;
		if (time == 125) {
			SOUND->Copy("RazerChargeSND");
			SOUND->Copy("RazerChargeSND");
			SOUND->Copy("RazerChargeSND");

			for (auto iter : m_leftRazer) {
				EFFECT->AddEffect(
					new cEffect("ChargeRazerIMG", 24, 0.03, VEC2(iter->m_pos.x + 200, iter->m_pos.y), VEC2(0, 0), VEC2(0, 0), VEC2(5, 5))
				);
			}
			for (auto iter : m_rightRazer) {
				EFFECT->AddEffect(
					new cEffect("ChargeRazerIMG", 24, 0.03, VEC2(iter->m_pos.x - 200, iter->m_pos.y), VEC2(0, 0), VEC2(0, 0), VEC2(5, 5))
				);
			}
		}

		if (time == 135) {
			CAMERA->SetShake(0.3, 150);
			SOUND->Copy("RazerFireSND");
			SOUND->Copy("RazerFireSND");
			SOUND->Copy("RazerFireSND");
			SCENE->ChangeScene("BossScene", "WhiteFade", 10);
		}
	}

	if (DistPoint(m_player->m_pos, GXY(GAMESIZE / 2, 900)) > 0.3)
		Lerp(m_player->m_pos, GXY(GAMESIZE / 2, 900), 2);

	if (20 <= time && time <= 100)
		m_boss->m_pos.y += 30.0 * D_TIME;

	for (int i = 1; i <= 3; ++i) {
		if (10 + 20 * i <= time && time <= 20 + 20 * i)
			Lerp(blackAlpha, 255.0, 5);
		if (20 + 20 * i <= time && time <= 30 + 20 * i)
			Lerp(blackAlpha, 150.0, 5);
	}
	if (90 <= time && time <= 100)
		Lerp(blackAlpha, 255.0, 5);
	if (100 <= time && time <= 110)
		Lerp(blackAlpha, 0.0, 5);

	if (115 <= time) {
		for (auto iter : m_leftRazer)
			Lerp(iter->m_pos, GXY(-200, iter->m_pos.y), 3);
		for (auto iter : m_rightRazer)
			Lerp(iter->m_pos, GXY(GAMESIZE + 200, iter->m_pos.y), 3);
	}

	if (135 <= time) {
		CAMERA->m_pos = OBJFIND(PLAYER)->GetPos();
		Lerp(CAMERA->m_size, VEC2(0.5, 0.5), 10);
	}
}

void cBossEnterScene::Render()
{
	IMAGE->Render(m_bg, VEC2(WINSIZEX / 2, WINSIZEY / 2), VEC2(1.5, 1.5), 0, true);
	IMAGE->Render(m_player->m_text, m_player->m_pos, VEC2(1, 1), 0, true);
	if(80 <= time)
		IMAGE->Render(m_boss->m_text, m_boss->m_pos, VEC2(8, 8), 0, true);
	for (auto iter : m_leftRazer)
		IMAGE->Render(iter->m_text, iter->m_pos, VEC2(1, 1), -90, true);
	for (auto iter : m_rightRazer)
		IMAGE->Render(iter->m_text, iter->m_pos, VEC2(1, 1), 90, true);
	IMAGE->Render(m_black, VEC2(0, 0), VEC2(1, 1), 0, false, D3DCOLOR_ARGB((int)blackAlpha, 255, 255, 255));
}

void cBossEnterScene::Release()
{
	SOUND->Stop("TitleSND");
	EFFECT->Reset();
	CAMERA->ResetCamera();
}

