#include "DXUT.h"
#include "cIngameScene.h"

cIngameScene::cIngameScene()
{
	m_bg = IMAGE->FindTexture("Stage1BG");

	map = new cScroolMap(m_bg);

	m_black = new cImage;
	m_black->m_text = IMAGE->FindTexture("BlackIMG");
	m_white = new cImage;
	m_white->m_text = IMAGE->FindTexture("WhiteIMG");
	m_redCircle = new cImage;
	m_redCircle->m_text = IMAGE->FindTexture("RedCircleEFFECT");
}

cIngameScene::~cIngameScene()
{
	SAFE_DELETE(map);
	SAFE_DELETE(m_black);
	SAFE_DELETE(m_white);
	SAFE_DELETE(m_redCircle);
}

void cIngameScene::Init()
{
	m_white->m_a = 0.0;
	m_black->m_a = 255.0;
	late = 1.0;

	isIntro = true;
	isCharge = false;
	isReady = false;

	CAMERA->m_size = VEC2(0.3, 0.3);
	m_redCircle->m_size = VEC2(80, 80);

	OBJFIND(PLAYER)->SetActive(true);
	((cPlayer*)OBJFIND(PLAYER))->Init();
	((cPlayer*)OBJFIND(PLAYER))->m_canMove = false;
	OBJFIND(PLAYER)->SetPos(GXY(GAMESIZE / 2, GAMESIZE + 100));

	map->Init();
}

void cIngameScene::Update()
{
	if (isIntro) {
		Intro();
		return;
	}
	map->Update();
}

void cIngameScene::Render()
{
	if (isIntro) {
		IMAGE->Render(m_bg, VEC2(WINSIZEX / 2, WINSIZEY / 2), VEC2(1, 1), 0.f, true);
		IMAGE->Render(m_black->m_text, VEC2(WINSIZEX / 2, WINSIZEY / 2), VEC2(2, 2), 0.f, true, m_black->m_color);
		IMAGE->Render(m_white->m_text, VEC2(WINSIZEX / 2, WINSIZEY / 2), VEC2(2, 2), 0.f, true, m_white->m_color);
		IMAGE->Render(m_redCircle->m_text, OBJFIND(PLAYER)->GetPos(), m_redCircle->m_size, 0.f, true);
		return;
	}
	map->Render();
}

void cIngameScene::Release()
{
	map->Release();
	FONT->Release();
	EFFECT->Reset();
	OBJFIND(PLAYER)->SetActive(false);
}

void cIngameScene::Intro()
{
	if (isCharge) {
		if (late > 0.0) {
			late -= D_TIME;
			Lerp(m_redCircle->m_size, VEC2(0, 0), 10);
		}
		else if (late < 0.0) {
			FONT->AddFont("STAGE 1 ÁøÀÔ", GXY(GAMESIZE / 2 - 270, 200), 100, 2, false, D3DCOLOR_XRGB(255, 255, 0));
			SOUND->Copy("RedCircleSND");
			SOUND->Copy("StageEnterSND");
			SOUND->Copy("StageEnterSND");
			m_black->m_a = 0.0;
			m_white->m_a = 255.0;
			late = 0.0;
		}
		else {
			if (isReady) {
				Lerp(CAMERA->m_size, VEC2(1, 1), 3);
				if (CAMERA->m_size.x < 1.01) {
					CAMERA->m_size = VEC2(1, 1);
					((cPlayer*)OBJFIND(PLAYER))->m_canMove = true;
					late = 1.0;
					isIntro = false;
				}
			}
			else {
				Lerp(m_white->m_a, 0.0, 3);
				Lerp(CAMERA->m_size, VEC2(1.5, 1.5), 3);
				if (CAMERA->m_size.x > 1.48) {
					CAMERA->m_size = VEC2(1.5, 1.5);
					isReady = true;
				}
			}
		}
	}
	else {
		Lerp(OBJFIND(PLAYER)->GetRefPos(), GXY(GAMESIZE / 2, GAMESIZE / 2), 2);
		if (DistPoint(OBJFIND(PLAYER)->GetPos(), GXY(GAMESIZE / 2, GAMESIZE / 2)) < 1.0) {
			OBJFIND(PLAYER)->SetPos(GXY(GAMESIZE / 2, GAMESIZE / 2));
			CAMERA->SetShake(0.5, 20);
			SOUND->Copy("ChargeSND");
			isCharge = true;
		}
	}
}
