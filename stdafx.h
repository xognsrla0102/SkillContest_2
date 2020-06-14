#pragma once
#pragma comment(lib, "dsound.lib")

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>
#include <string>
#include <ctime>
using namespace std;

using VEC2 = D3DXVECTOR2;
using VEC3 = D3DXVECTOR3;
using VEC4 = D3DXVECTOR4;
using MATRIX = D3DXMATRIXA16;

constexpr int WINSIZEX = 1920;
constexpr int WINSIZEY = 1080;

//인게임 크기 가로 : 세로 = 1080 : 1080
//UI     크기 가로 : 세로 = 840 : 1080
constexpr int GAMESIZE = 1080;

#define GX(x) (420 + x)
#define GY(y) (y)
#define GXY(x, y) (VEC2(420 + x, y))

enum TAGS {
	ENEMY,
	ITEM,
	BULLET,
	PLAYER,
	TAG_END,
};

#include "SDKsound.h"
#include "math.h"
#include "collision.h"
#include "cTexture.h"
#include "cMultiTexture.h"
#include "cImage.h"
#include "cImageManager.h"
#include "cInputManager.h"
#include "cSoundManager.h"
#include "cCameraManager.h"
#include "cGameManager.h"
#include "cScene.h"
#include "cEffect.h"
#include "cEffectManager.h"
#include "cTimer.h"
#include "cAnimation.h"
#include "cTitleScene.h"
#include "cHowtoScene.h"
#include "cIntroScene.h"
#include "cIngameScene.h"
#include "cSceneManager.h"
#include "cFontManager.h"
#include "cButton.h"
#include "cUI.h"
#include "cTitleUI.h"
#include "cIngameUI.h"
#include "cUIManager.h"
#include "cObject.h"
#include "cObjectManager.h"
#include "cItem.h"
#include "cItemManager.h"
#include "cMotionInfo.h"
#include "cMotionBlur.h"
#include "cPlayer.h"
#include "cScroolMap.h"
#include "cBullet.h"
#include "cPlayerBullet.h"
#include "cEnemyBullet.h"
#include "cBulletManager.h"
#include "cEnemy.h"
#include "cMeteor.h"
#include "cTurret.h"
#include "cRotate.h"
#include "cEnemyManager.h"

void DEBUG_LOG(LPCSTR fmt, ...);

#define D_TIME DXUTGetElapsedTime() * GAME->TIME_SCALE
#define DEVICE DXUTGetD3D9Device()

template <typename T>
void Lerp(T& pV1, const T& pV2, double s = 1) {
	pV1 = pV1 + (pV2 - pV1) * s * D_TIME;
}