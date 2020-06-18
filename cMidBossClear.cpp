#include "DXUT.h"
#include "cMidBossClear.h"

cMidBossClear::cMidBossClear()
{
	m_ani = new cAnimation(0.01, 24, false);
	m_player = new cImage;
	m_white = IMAGE->FindTexture("WhiteIMG");
	m_player->m_text = IMAGE->FindTexture("IngamePlayerIMG");
	m_razer = IMAGE->FindTexture("EnemyBulletRazer1IMG");
	m_shield = IMAGE->FindTexture("ShieldIMG");
}

cMidBossClear::~cMidBossClear()
{
	SAFE_DELETE(m_ani);
	SAFE_DELETE(m_player);
}

void cMidBossClear::Init()
{
	char str[256];
	sprintf(str, "MidBossClear%dBG", GAME->m_nowStage);
	m_bg = IMAGE->FindTexture(str);
	sprintf(str, "Stage%dBG", GAME->m_nowStage);
	m_bg2 = IMAGE->FindTexture(str);

	m_ani->m_nowFrame = 0;
	whiteAlpha = 0;
	isWhite = false;
}

void cMidBossClear::Update()
{
	m_ani->Update();
	auto isEnter = ((cMidBossClearUI*)UI->FindUI("MidBossClearSceneUI"))->isEnter;
	if (isEnter) {
		if (!isWhite) {
			Lerp(whiteAlpha, 255.0, 2);
			if (whiteAlpha >= 253) isWhite = true;
		}
		else {
			Lerp(whiteAlpha, 0.0, 1);
			if (whiteAlpha < 10) {
				GAME->m_isBehind = false;
				GAME->m_story = 2;
				SCENE->ChangeScene("IngameScene", "BlackFade", 3);
			}
		}
	}
}

void cMidBossClear::Render()
{
	IMAGE->Render(m_bg, VEC2(0, 0));
	IMAGE->Render(m_player->m_text, GXY(GAMESIZE / 2, GAMESIZE / 2), VEC2(1, 1), 0, true);

	auto isEnter = ((cMidBossClearUI*)UI->FindUI("MidBossClearSceneUI"))->isEnter;
	if (!isEnter) IMAGE->Render(IMAGE->FindTexture("ChargeEFFECT", m_ani->m_nowFrame), GXY(GAMESIZE / 2, GAMESIZE / 2), VEC2(1, 1), 0, true);
	else {
		if (!isWhite) {
			IMAGE->Render(m_razer, GXY(GAMESIZE / 2, 0), VEC2(5, 20), 0, true);
			IMAGE->Render(m_player->m_text, GXY(GAMESIZE / 2, GAMESIZE / 2), VEC2(1, 1), 0, true);
			IMAGE->Render(m_shield, GXY(GAMESIZE / 2, GAMESIZE / 2), VEC2(1, 1), 0, true);
			EFFECT->AddEffect(new cEffect("ExplosionEFFECT", 32, 0.02, VEC2(rand() % WINSIZEX, rand() % WINSIZEY), VEC2(0, 0)));
			IMAGE->Render(m_white, VEC2(0, 0), VEC2(1, 1), 0, false, D3DCOLOR_ARGB((int)whiteAlpha, 255, 255, 255));
		}
		else {
			IMAGE->Render(m_bg2, VEC2(0, 0));
			IMAGE->Render(m_player->m_text, GXY(GAMESIZE / 2, GAMESIZE / 2), VEC2(1, 1), 0, true);
			IMAGE->Render(m_shield, GXY(GAMESIZE / 2, GAMESIZE / 2), VEC2(1, 1), 0, true);
			IMAGE->Render(m_white, VEC2(0, 0), VEC2(1, 1), 0, false, D3DCOLOR_ARGB((int)whiteAlpha, 255, 255, 255));
			IMAGE->DrawFont("FINAL MISSION : DESTROY THE BOSS", GXY(GAMESIZE / 2 - 500, 300), "HY°ß°íµñ", 50, D3DCOLOR_XRGB(255, 255, 0));
		}
	}
}

void cMidBossClear::Release()
{
}

