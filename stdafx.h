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
#include "cSceneManager.h"

void DEBUG_LOG(LPCSTR fmt, ...);

#define D_TIME DXUTGetElapsedTime() * GAME->TIME_SCALE
#define DEVICE DXUTGetD3D9Device()

template <typename T>
void Lerp(T& pV1, const T& pV2, double s) {
	pV1 = pV1 + (pV2 - pV1) * s * D_TIME;
}