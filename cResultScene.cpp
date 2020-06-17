#include "DXUT.h"
#include "cResultScene.h"

cResultScene::cResultScene()
{
	m_bg = IMAGE->FindTexture("ResultBG");
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
	Lerp(m_nowYourScore, (float)GAME->m_score, 1);
	sprintf(str, "%07d", (int)m_nowYourScore);
	m_scorePrint = str;
	
	if ((int)m_nowYourScore + 50 > GAME->m_score) {
		if (m_nowYourScore != GAME->m_score)
			m_nowYourScore = GAME->m_score;
	
		if (m_isEnterInitial) {
			if (m_initial.size() && KEYDOWN(VK_BACK))
				m_initial.pop_back();
			for (int i = 'A'; i != 'Z'; ++i)
				if (m_initial.size() < 3 && KEYDOWN(i))
					m_initial += i;
	
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
	IMAGE->DrawFont("����� ���� : ", VEC2(250, 300), "HY�߰��", 40, D3DCOLOR_XRGB(255, 255, 255));
	IMAGE->DrawFont(m_scorePrint, VEC2(500, 300), "HY�߰��", 40);
	
	if ((int)m_nowYourScore + 2 > GAME->m_score)
		IMAGE->DrawFont("���͸� �Է��Ͽ� �����ϼ���.", VEC2(250, 150), "HY�߰��", 40, D3DCOLOR_XRGB(255, 255, 0));
	
	if (m_isEnterInitial) {
		IMAGE->DrawFont("�̴ϼ� : ", VEC2(250, 400), "HY�߰��", 60, D3DCOLOR_XRGB(255, 255, 255));
		IMAGE->DrawFont(m_initial, VEC2(500, 400), "HY�߰��", 60, D3DCOLOR_XRGB(255, 255, 0));
	}
}

void cResultScene::Release()
{
	SOUND->Stop("ResultSND");
}

