#include "DXUT.h"
#include "cRankScene.h"

cRankScene::cRankScene()
{
	m_bg = IMAGE->FindTexture("RankBG");
}

cRankScene::~cRankScene()
{
}

void cRankScene::Init()
{
	SOUND->Play("RankSND", true);
}

void cRankScene::Update()
{
	if (KEYDOWN(VK_RETURN))
		SCENE->ChangeScene("TitleScene", "WhiteFade", 5);
}

void cRankScene::Render()
{
	IMAGE->Render(m_bg, VEC2(0, 0));
	for (size_t i = 0; i < 3; ++i) {
		IMAGE->DrawFont(GAME->m_scoreList[i]->m_initial, VEC2(1000, 290 + i * 240), "HY°ß°íµñ", 70, D3DCOLOR_XRGB(255, 255, 0));
		IMAGE->DrawFont(to_string(GAME->m_scoreList[i]->m_score), VEC2(1400, 290 + i * 240), "HY°ß°íµñ", 70);
	}
}

void cRankScene::Release()
{
	SOUND->Stop("RankSND");
}
