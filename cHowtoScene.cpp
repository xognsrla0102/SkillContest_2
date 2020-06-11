#include "DXUT.h"
#include "cHowtoScene.h"

cHowtoScene::cHowtoScene()
{
	m_bg = IMAGE->FindTexture("BlackIMG");
	m_enter = IMAGE->FindTexture("HowtoEnterIMG");
	m_howto = IMAGE->FindTexture("HowtoBGIMG");

	for (int i = 0; i < 4; ++i) {
		char str[256];
		sprintf(str, "Howto%dIMG", i);
		m_imgs.push_back(new cImage);
		m_imgs[i]->m_a = 0;
		m_imgs[i]->m_text = IMAGE->FindTexture(str);
	}
	m_imgs[0]->m_pos = VEC2(20, 100);
	m_imgs[1]->m_pos = VEC2(20, 250);
	m_imgs[2]->m_pos = VEC2(20, 500);
	m_imgs[3]->m_pos = VEC2(20, 850);
}

cHowtoScene::~cHowtoScene()
{
	for (auto iter : m_imgs)
		SAFE_DELETE(iter);
	m_imgs.clear();
}

void cHowtoScene::Init()
{
	for (auto iter : m_imgs)
		iter->m_a = 0;
	m_imgCnt = -1;
	howtoAlpha = 0;
}

void cHowtoScene::Update()
{
	if (KEYDOWN(VK_RETURN)) {
		m_imgCnt++;
		if(m_imgCnt < 4) m_imgs[m_imgCnt]->m_a = 255.0;
		else if (m_imgCnt == 4) howtoAlpha = 255;
		else if (m_imgCnt == 5) SCENE->ChangeScene("TitleScene", "BlackFade", 10);
	}
}

void cHowtoScene::Render()
{
	IMAGE->Render(m_bg, VEC2(0, 0));
	for (auto iter : m_imgs)
		IMAGE->Render(iter->m_text, iter->m_pos, VEC2(1, 1), 0.f, false, iter->m_color);
	IMAGE->Render(m_howto, VEC2(0, 0), VEC2(1, 1), 0.f, false, D3DCOLOR_ARGB(howtoAlpha, 255, 255, 255));
	IMAGE->Render(m_enter, VEC2(1400, 1000));
}

void cHowtoScene::Release()
{
}
