#pragma once
#include "cSingleton.hpp"

constexpr int KEY_MAX = 256;

class cInputManager : public cSingleton<cInputManager>
{
public:
	bool m_nowKey[KEY_MAX] = { 0 };
	bool m_oldKey[KEY_MAX] = { 0 };
public:
	cInputManager() {}
	virtual ~cInputManager() {}
	void Update();
public:
	bool IsKeyDown(int key) { return (m_nowKey[key] && !m_oldKey[key]); }
	bool IsKeyUp(int key) { return (!m_nowKey[key] && m_oldKey[key]); }
	bool IsKeyPress(int key) { return (m_nowKey[key] && m_oldKey[key]); }
};

#define INPUT cInputManager::GetInst()

#define KEYDOWN(k) INPUT->IsKeyDown(k)
#define KEYUP(k) INPUT->IsKeyUp(k)
#define KEYPRESS(k) INPUT->IsKeyPress(k)