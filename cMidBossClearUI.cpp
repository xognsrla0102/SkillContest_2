#include "DXUT.h"
#include "cMidBossClearUI.h"

cMidBossClearUI::cMidBossClearUI()
{
	m_t = new cTimer(0.1);
	m_gageLine = IMAGE->FindTexture("IngameButtonGageLineUI");
	m_gage = IMAGE->FindTexture("IngameButtonGageUI");
}

cMidBossClearUI::~cMidBossClearUI()
{
	SAFE_DELETE(m_t);
}

void cMidBossClearUI::Init()
{
	time = 0;
	enterHit = 0;
	isEnter = false;
}

void cMidBossClearUI::Update()
{
	if (!isEnter) {
		Lerp(CAMERA->m_size, VEC2(0.5, 0.5), 2);

		if (m_t->Update()) {
			time++;
			if(time % 2 == 0)
				enterHit--;
		}

		if (KEYDOWN(VK_RETURN)) {
			CAMERA->SetShake(0.05, 10);
			enterHit += 2;
			if (enterHit > 50) {
				CAMERA->SetShake(1, 40);
				SOUND->Copy("RazerFireSND");
				enterHit = 50;
				isEnter = true;
			}
		}
		if (enterHit < 0) enterHit = 0;
	}
	else {
		Lerp(CAMERA->m_size, VEC2(1, 1), 2);
	}
}

void cMidBossClearUI::Render()
{
	if (!isEnter) {
		if (time <= 20) return;

		if (time % 2 == 0) m_but = IMAGE->FindTexture("IngameButton0UI");
		else m_but = IMAGE->FindTexture("IngameButton1UI");

		IMAGE->Render(m_but, GXY(GAMESIZE / 2, 300), VEC2(1, 1), 0, true);

		RECT rt = {
			0, 0,
			enterHit / 50.0 * m_gage->m_info.Width,
			m_gage->m_info.Height
		};

		IMAGE->CropRender(m_gage, GXY(GAMESIZE / 2, 200), rt, VEC2(1, 1), true);
		IMAGE->Render(m_gageLine, GXY(GAMESIZE / 2, 200), VEC2(1, 1), 0, true);
	}
}

void cMidBossClearUI::Release()
{
}
