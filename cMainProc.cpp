#include "DXUT.h"
#include "cMainProc.h"

cMainProc::cMainProc()
{
	srand(time(0));

	IMAGE->AddTexture("TitleBG", "resources/image/title/bg.png");

	IMAGE->AddTexture("TitleStartUI", "resources/image/ui/title/start.png");
	IMAGE->AddTexture("TitleHowtoUI", "resources/image/ui/title/howto.png");
	IMAGE->AddTexture("TitleRankUI", "resources/image/ui/title/rank.png");
	IMAGE->AddTexture("TitleExitUI", "resources/image/ui/title/exit.png");

	IMAGE->AddTexture("Howto0IMG", "resources/image/howto/0.png");
	IMAGE->AddTexture("Howto1IMG", "resources/image/howto/1.png");
	IMAGE->AddTexture("Howto2IMG", "resources/image/howto/2.png");
	IMAGE->AddTexture("Howto3IMG", "resources/image/howto/3.png");
	IMAGE->AddTexture("HowtoBGIMG", "resources/image/howto/howto.png");
	IMAGE->AddTexture("HowtoEnterIMG", "resources/image/howto/enter.png");


	SOUND->AddSound("TitleSND", L"resources/sound/title.wav");
	SOUND->AddSound("TitleWarningSND", L"resources/sound/titlewarning.wav");
	SOUND->AddSound("ExplosionSND", L"resources/sound/explosion.wav");
	SOUND->AddSound("SelectSND", L"resources/sound/select.wav");

	SCENE;

	SCENE->AddScene("TitleScene", new cTitleScene);
	SCENE->AddScene("HowtoScene", new cHowtoScene);
	//SCENE->AddScene("IngameScene", new cIngameScene);
	SCENE->ChangeScene("TitleScene", "None", 0);
}

cMainProc::~cMainProc()
{
	UI->ReleaseInst();
	SCENE->ReleaseInst();
	GAME->ReleaseInst();
	OBJECT->ReleaseInst();
	EFFECT->ReleaseInst();
	FONT->ReleaseInst();
	SOUND->ReleaseInst();
	IMAGE->ReleaseInst();
	INPUT->ReleaseInst();
	CAMERA->ReleaseInst();
}

void cMainProc::Update()
{
	INPUT->Update();
	CAMERA->Update();
	UI->Update();
	GAME->Update();
	EFFECT->Update();
	FONT->Update();
	OBJECT->Update();
	SCENE->Update();
}

void cMainProc::Render()
{
	CAMERA->SetTransform();

	IMAGE->Begin(false);
	SCENE->Render();
	OBJECT->Render();
	EFFECT->Render();
	FONT->Render();

	IMAGE->ReBegin(true);
	UI->Render();
	IMAGE->End();
}

void cMainProc::LostDevice()
{
	IMAGE->LostDevice();
}

void cMainProc::ResetDevice()
{
	CAMERA->ResetCamera();
	IMAGE->ResetDevice();
}
