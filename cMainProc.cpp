#include "DXUT.h"
#include "cMainProc.h"

cMainProc::cMainProc()
{
	srand(time(0));

	IMAGE->AddTexture("TitleBG", "resources/image/title/bg.png");
	IMAGE->AddTexture("TitleNameIMG", "resources/image/title/gamename.png");

	IMAGE->AddTexture("TitleStartUI", "resources/image/ui/title/start.png");
	IMAGE->AddTexture("TitleHowtoUI", "resources/image/ui/title/howto.png");
	IMAGE->AddTexture("TitleRankUI", "resources/image/ui/title/rank.png");
	IMAGE->AddTexture("TitleExitUI", "resources/image/ui/title/exit.png");

	IMAGE->AddTexture("IngamePlayerIMG", "resources/image/ingame/player.png");

	IMAGE->AddTexture("PlayerBulletIMG", "resources/image/bullet/playerbullet.png");

	IMAGE->AddTexture("Howto0IMG", "resources/image/howto/0.png");
	IMAGE->AddTexture("Howto1IMG", "resources/image/howto/1.png");
	IMAGE->AddTexture("Howto2IMG", "resources/image/howto/2.png");
	IMAGE->AddTexture("Howto3IMG", "resources/image/howto/3.png");
	IMAGE->AddTexture("HowtoBGIMG", "resources/image/howto/howto.png");
	IMAGE->AddTexture("HowtoEnterIMG", "resources/image/howto/enter.png");

	IMAGE->AddTexture("Stage1BG", "resources/image/ingame/bg0.png");
	IMAGE->AddTexture("Stage2BG", "resources/image/ingame/bg1.png");
	IMAGE->AddTexture("MidBossClear1BG", "resources/image/ingame/midbossclear0.png");
	IMAGE->AddTexture("MidBossClear2BG", "resources/image/ingame/midbossclear1.png");

	IMAGE->AddTexture("RedCircleEFFECT", "resources/image/effect/redcircle.png");
	IMAGE->AddTexture("DieEFFECT", "resources/image/effect/die.png");
	IMAGE->AddTexture("ExplosionEFFECT", "resources/image/effect/explosion/%d.png", 32);
	IMAGE->AddTexture("ChargeEFFECT", "resources/image/effect/chargeShot/%d.png", 24);

	IMAGE->AddTexture("IngameBGUI", "resources/image/ui/ingame/bg.png");
	IMAGE->AddTexture("IngameHPUI", "resources/image/ui/ingame/hp.png");
	IMAGE->AddTexture("IngameBossHPUI", "resources/image/ui/ingame/bosshp.png");
	IMAGE->AddTexture("IngameEXPUI", "resources/image/ui/ingame/exp.png");
	IMAGE->AddTexture("IngameDamageUI", "resources/image/ui/ingame/damage.png");
	IMAGE->AddTexture("IngameButton0UI", "resources/image/ui/ingame/but0.png");
	IMAGE->AddTexture("IngameButton1UI", "resources/image/ui/ingame/but1.png");
	IMAGE->AddTexture("IngameButtonGageLineUI", "resources/image/ui/ingame/butgageline.png");
	IMAGE->AddTexture("IngameButtonGageUI", "resources/image/ui/ingame/butgage.png");

	IMAGE->AddTexture("IngameSmokeIMG", "resources/image/ingame/%d.png", 4);
	IMAGE->AddTexture("ChargeRazerIMG", "resources/image/effect/chargeRazerEffect/%d.png", 24);

	IMAGE->AddTexture("EnemyMeteorIMG", "resources/image/enemy/meteor.png");
	IMAGE->AddTexture("EnemyTurretIMG", "resources/image/enemy/turret.png");
	IMAGE->AddTexture("EnemyRazerIMG", "resources/image/enemy/razer.png");

	IMAGE->AddTexture("PlanetIMG", "resources/image/enemy/planet.png");

	IMAGE->AddTexture("EnemyCircle0IMG", "resources/image/enemy/0_circle.png");
	IMAGE->AddTexture("EnemyCircle1IMG", "resources/image/enemy/1_circle.png");
	IMAGE->AddTexture("EnemySin0IMG", "resources/image/enemy/0_sin.png");
	IMAGE->AddTexture("EnemySin1IMG", "resources/image/enemy/1_sin.png");
	IMAGE->AddTexture("EnemyStraight0IMG", "resources/image/enemy/0_straight.png");
	IMAGE->AddTexture("EnemyStraight1IMG", "resources/image/enemy/1_straight.png");

	IMAGE->AddTexture("EnemyMidBoss0IMG", "resources/image/enemy/0_midboss.png");
	IMAGE->AddTexture("EnemyMidBoss1IMG", "resources/image/enemy/1_midboss.png");

	IMAGE->AddTexture("EnemyBullet0IMG", "resources/image/bullet/enemybullet0.png");
	IMAGE->AddTexture("EnemyBullet1IMG", "resources/image/bullet/enemybullet1.png");
	IMAGE->AddTexture("EnemyBullet2IMG", "resources/image/bullet/enemybullet2.png");
	IMAGE->AddTexture("EnemyBullet3IMG", "resources/image/bullet/enemybullet3.png");
	IMAGE->AddTexture("EnemyRazer0IMG", "resources/image/bullet/enemyrazer0.png");
	IMAGE->AddTexture("EnemyRazer1IMG", "resources/image/bullet/enemyrazer1.png");

	IMAGE->AddTexture("ShieldIMG", "resources/image/ui/ingame/shield.png");

	SOUND->AddSound("TitleSND", L"resources/sound/title.wav");
	SOUND->AddSound("TitleWarningSND", L"resources/sound/titlewarning.wav");
	SOUND->AddSound("ExplosionSND", L"resources/sound/explosion.wav");
	SOUND->AddSound("SelectSND", L"resources/sound/select.wav");
	SOUND->AddSound("ChargeSND", L"resources/sound/charge.wav");
	SOUND->AddSound("StageEnterSND", L"resources/sound/stageenter.wav");
	SOUND->AddSound("RedCircleSND", L"resources/sound/redcircle.wav");
	SOUND->AddSound("EnemyHitSND", L"resources/sound/enemyhit.wav");
	SOUND->AddSound("EnemyDeadSND", L"resources/sound/enemydead.wav");
	SOUND->AddSound("StageSND", L"resources/sound/stage.wav");
	SOUND->AddSound("PlayerBulletSND", L"resources/sound/playerbullet.wav");
	SOUND->AddSound("PlayerDamageSND", L"resources/sound/playerdamage.wav");
	SOUND->AddSound("RazerChargeSND", L"resources/sound/razer_charge.wav");
	SOUND->AddSound("RazerFireSND", L"resources/sound/razer_fire.wav");
	//SCENE 매니저 생성자 호출
	SCENE;

	OBJECT->AddOBJ(new cPlayer, PLAYER);
	OBJECT->AddOBJ(new cBulletManager, BULLET);
	OBJECT->AddOBJ(new cEnemyManager, ENEMY);
	OBJECT->AddOBJ(new cItemManager, ITEM);

	SCENE->AddScene("TitleScene", new cTitleScene);
	SCENE->AddScene("HowtoScene", new cHowtoScene);
	SCENE->AddScene("IntroScene", new cIntroScene);
	SCENE->AddScene("IngameScene", new cIngameScene);
	SCENE->AddScene("MidBossEnterScene", new cMidBossEnterScene);
	SCENE->AddScene("MidBossScene", new cMidBossScene);
	SCENE->AddScene("MidBossClearScene", new cMidBossClear);

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

	if (KEYDOWN(VK_F4)) {
		CAMERA->m_size = VEC2(1, 1);
		GAME->m_nowStage = 0;
		SCENE->ChangeScene("TitleScene", "None", 0.f);
	}
	if (KEYDOWN(VK_F5)) {
		CAMERA->m_size = VEC2(1, 1);
		GAME->m_nowStage = 1;
		GAME->m_story = 0;
		SCENE->ChangeScene("IngameScene", "None", 0.f);
	}
	if (KEYDOWN(VK_F6)) {
		CAMERA->m_size = VEC2(1, 1);
		GAME->m_nowStage = 2;
		GAME->m_story = 0;
		SCENE->ChangeScene("IngameScene", "None", 0.f);
	}

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
