#include "DXUT.h"
#include "cIntroScene.h"

cIntroScene::cIntroScene()
{
	m_player	= new cImage;
	m_black		= new cImage;
	m_white		= new cImage;
	m_redCircle = new cImage;

	m_bg = IMAGE->FindTexture("Stage1BG");
	m_player->m_text = IMAGE->FindTexture("IngamePlayerIMG");
	m_black->m_text = IMAGE->FindTexture("BlackIMG");
	m_white->m_text = IMAGE->FindTexture("WhiteIMG");
	m_redCircle->m_text = IMAGE->FindTexture("RedCircleEFFECT");
}

cIntroScene::~cIntroScene()
{
	SAFE_DELETE(m_player);
	SAFE_DELETE(m_black);
	SAFE_DELETE(m_white);
	SAFE_DELETE(m_redCircle);
}

void cIntroScene::Init()
{
	m_white->m_a = 0.0;
	m_black->m_a = 255.0;
	wait = 1.0;

	isCharge = isReady = false;

	CAMERA->m_size		= VEC2(0.3, 0.3);
	m_redCircle->m_size = VEC2(80, 80);

	m_player->m_pos = GXY(GAMESIZE / 2, GAMESIZE + 100);
}

void cIntroScene::Update()
{
	Intro();
}

void cIntroScene::Render()
{
	IMAGE->Render(m_bg, VEC2(WINSIZEX / 2, WINSIZEY / 2), VEC2(1, 1), 0, true);
	IMAGE->Render(m_black->m_text, VEC2(WINSIZEX / 2, WINSIZEY / 2), VEC2(2, 2), 0, true, m_black->m_color);

	IMAGE->Render(m_redCircle->m_text, m_player->m_pos, m_redCircle->m_size, 0, true);
	IMAGE->Render(m_player->m_text, m_player->m_pos, VEC2(1, 1), 0, true);

	IMAGE->Render(m_white->m_text, VEC2(WINSIZEX / 2, WINSIZEY / 2), VEC2(2, 2), 0, true, m_white->m_color);
}

void cIntroScene::Release()
{
	FONT->Release();
	CAMERA->ResetCamera();
}

void cIntroScene::Intro()
{
	if (isCharge) {
		if (wait > 0.0) {
			wait -= D_TIME;
			Lerp(m_redCircle->m_size, VEC2(0, 0), 10);
		}
		else if (wait < 0.0) {
			FONT->AddFont("AVOID ENEMY BULLET!!", GXY(GAMESIZE / 2 - 500, 200), 100, 2, false, D3DCOLOR_XRGB(255, 0, 0));
			SOUND->Copy("RedCircleSND");
			SOUND->Copy("StageEnterSND");
			SOUND->Copy("StageEnterSND");
			m_black->m_a = 0;
			m_white->m_a = 255;
			wait = 0;
		}
		else {
			if (isReady) {
				Lerp(CAMERA->m_size, VEC2(1, 1), 3);
				if (CAMERA->m_size.x < 1.01) {
					GAME->Init();
					((cPlayer*)OBJFIND(PLAYER))->Init();
					SCENE->ChangeScene("IngameScene", "None", 0);
				}
			}
			else {
				Lerp(m_white->m_a, 0.0, 3);
				Lerp(CAMERA->m_size, VEC2(1.5, 1.5), 3);
				if (CAMERA->m_size.x > 1.48) {
					CAMERA->m_size = VEC2(1.5, 1.5);
					m_white->m_a = 0;
					isReady = true;
				}
			}
		}
	}
	else {
		Lerp(m_player->m_pos, GXY(GAMESIZE / 2, GAMESIZE / 2), 2);
		if (DistPoint(m_player->m_pos, GXY(GAMESIZE / 2, GAMESIZE / 2)) < 0.5) {
			m_player->m_pos = GXY(GAMESIZE / 2, GAMESIZE / 2);
			CAMERA->SetShake(0.5, 20);
			SOUND->Copy("ChargeSND");
			isCharge = true;
		}
	}
}
