#include "DXUT.h"
#include "cTitleScene.h"

cTitleScene::cTitleScene()
{
	m_cameraShakeTiming = new cTimer(3 + rand() % 5);
	m_black = new cImage;

	m_bg = IMAGE->FindTexture("TitleBG");
	m_black->m_text = IMAGE->FindTexture("BlackIMG");
}

cTitleScene::~cTitleScene()
{
	SAFE_DELETE(m_black);
	SAFE_DELETE(m_cameraShakeTiming);
}

void cTitleScene::Init()
{
	SOUND->Play("TitleSND", true);
	SOUND->Play("TitleWarningSND", true);

	m_cameraShakeTiming->m_delay = 0;
	m_black->m_a = 0.f;
	m_lightDir = 1.0;
	m_waitFadeOut = 2.0;
	m_isFadeOut = true;
}

void cTitleScene::Update()
{
	if (m_cameraShakeTiming->Update()) {
		CAMERA->SetShake(0.3, 30);
		m_cameraShakeTiming->m_delay = 1 + rand() % 3;
		SOUND->Copy("ExplosionSND");
	}

	static int spd = 5;
	if (m_isFadeOut) {
		Lerp(m_black->m_a, 255.0, spd);
		if (m_black->m_a > 253.0) {
			spd = 5 + 5 * (1 + rand() % 3);
			m_isFadeOut = false;
		}
	}
	else {
		if (m_black->m_a < 2.0) {
			m_waitFadeOut -= D_TIME;
			if (m_waitFadeOut < 0.0) {
				m_waitFadeOut = 2.0;
				m_isFadeOut = true;
			}
			return;
		}
		Lerp(m_black->m_a, 0.0, spd);
	}
}

void cTitleScene::Render()
{
	IMAGE->Render(m_bg, VEC2(WINSIZEX / 2, WINSIZEY / 2), VEC2(1.3, 1.3), 0.f, true, 0xffffffff);
	IMAGE->Render(m_black->m_text, VEC2(WINSIZEX / 2, WINSIZEY / 2), VEC2(1.3, 1.3), 0.f, true, m_black->m_color);
}

void cTitleScene::Release()
{
	SOUND->Stop("TitleSND");
	SOUND->Stop("TitleWarningSND");
}
