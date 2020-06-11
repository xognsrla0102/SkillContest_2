#include "DXUT.h"
#include "cInputManager.h"

void cInputManager::Update()
{
	memcpy(m_oldKey, m_nowKey, sizeof(m_nowKey));

	if (SCENE->m_isSceneChange) {
		for (int i = 0; i < KEY_MAX; ++i)
			m_nowKey[i] = false;
	}
	else {
		for (int i = 0; i < KEY_MAX; ++i)
			m_nowKey[i] = GetAsyncKeyState(i) ? true : false;
	}
}
