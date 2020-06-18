#include "DXUT.h"
#include "cResultScene.h"

cResultScene::cResultScene()
{
	m_bg = IMAGE->FindTexture("ResultBG");
	m_gage = IMAGE->FindTexture("ResultGageIMG");
	m_gageLine = IMAGE->FindTexture("ResultGageLineIMG");
}

cResultScene::~cResultScene()
{
}

void cResultScene::Init()
{
	SOUND->Play("ResultSND", true);
	CAMERA->ResetCamera();
	m_nowYourScore = 0;
	m_initial = "";
	m_isEnterInitial = false;
	GAME->m_score += (int)(((cPlayer*)OBJFIND(PLAYER))->m_hp / (float)(((cPlayer*)OBJFIND(PLAYER))->m_hpMax) * 100000);
}

void cResultScene::Update()
{
	char str[256];
	Lerp(m_nowYourScore, (double)GAME->m_score, 1);
	sprintf(str, "%07d", (int)m_nowYourScore);
	m_scorePrint = str;
	
	if ((int)m_nowYourScore + 50 > GAME->m_score) {
		if (m_nowYourScore != GAME->m_score)
			m_nowYourScore = GAME->m_score;
	
		if (m_isEnterInitial) {
			if (m_initial.size() && KEYDOWN(VK_BACK)) m_initial.pop_back();
			for (int i = 'A'; i <= 'Z'; ++i)
				if (m_initial.size() < 3 && KEYDOWN(i)) m_initial += i;
	
			if (SCENE->m_isSceneChange == false && m_initial.size() == 3 && KEYDOWN(VK_RETURN)) {
				GAME->m_scoreList[3]->m_initial = this->m_initial;
				GAME->m_scoreList[3]->m_score = GAME->m_score;
				GAME->SortScore();
				SCENE->ChangeScene("RankScene", "WhiteFade", 2);
			}
		}
		else {
			if (SCENE->m_isSceneChange == false && KEYDOWN(VK_RETURN)) {
				if (GAME->m_nowStage == 1) {
					GAME->m_nowStage++;
					GAME->m_story = 0;
					SCENE->ChangeScene("IngameScene", "BlackFade", 3);
				}
				else {
					m_isEnterInitial = true;
				}
			}
		}
	}
}

void cResultScene::Render()
{
	IMAGE->Render(m_bg, VEC2(0, 0));

	RECT rt = {
		0 , 0,
		m_nowYourScore / (double)(GAME->m_score) * m_gage->m_info.Width,
		m_gage->m_info.Height
	};

	IMAGE->CropRender(m_gage, VEC2(300, 200), rt);
	IMAGE->Render(m_gageLine, VEC2(300, 200));

	IMAGE->DrawFont("당신의 점수 : ", VEC2(350, 500), "HY견고딕", 100, D3DCOLOR_XRGB(255, 255, 255));
	IMAGE->DrawFont(m_scorePrint, VEC2(1000, 500), "HY견고딕", 100);
	
	if ((int)m_nowYourScore + 2 > GAME->m_score)
		IMAGE->DrawFont("엔터를 입력하여 진행하세요.", VEC2(550, 350), "HY견고딕", 100, D3DCOLOR_XRGB(255, 255, 0));
	
	if (m_isEnterInitial) {
		IMAGE->DrawFont("이니셜 : ", VEC2(480, 750), "HY견고딕", 100, D3DCOLOR_XRGB(255, 255, 255));
		IMAGE->DrawFont(m_initial, VEC2(900, 750), "HY견고딕", 100, D3DCOLOR_XRGB(255, 255, 0));
	}
}

void cResultScene::Release()
{
	SOUND->Stop("ResultSND");
}

