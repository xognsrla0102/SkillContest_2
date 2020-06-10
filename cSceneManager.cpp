#include "DXUT.h"
#include "cSceneManager.h"

cSceneManager::cSceneManager()
{
	IMAGE->AddTexture("ChangeSceneWhiteEffect", "resources/image/scenechange/white.png");
	IMAGE->AddTexture("ChangeSceneBlackEffect", "resources/image/scenechange/black.png");

	m_white = new cImage;
	m_white->m_text = IMAGE->FindTexture("ChangeSceneWhiteEffect");
	m_white->m_a = 0.f;
	m_white->SetNowRGB();

	m_black = new cImage;
	m_black->m_text = IMAGE->FindTexture("ChangeSceneBlackEffect");
	m_black->m_a = 0.f;
	m_black->SetNowRGB();
}

cSceneManager::~cSceneManager()
{
	SAFE_DELETE(m_white);
	SAFE_DELETE(m_black);

	for (auto iter : m_scenes)
		SAFE_DELETE(iter.second);
	m_scenes.clear();
}

void cSceneManager::AddScene(const string& key, cScene* scenePtr)
{
	if (!scenePtr) {
		DEBUG_LOG("씬 포인터가 없습니다.\n");
		return;
	}

	if (m_scenes.find(key) != m_scenes.end()) {
		DEBUG_LOG("%s 씬이 이미 있습니다.\n", key.c_str());
		return;
	}
	m_scenes[key] = scenePtr;
}

void cSceneManager::ChangeScene(const string& key, string changeName, double changeSpeed)
{
	auto find = m_scenes.find(key);
	if (find == m_scenes.end()) {
		DEBUG_LOG("%s씬이 없습니다.\n", key.c_str());
		return;
	}
	m_next = find->second;
	m_changeSpeed = changeSpeed;

	if (changeName == "WhiteFade" || changeName == "BlackFade") {
		m_isFadeChange = true;
		m_isFadeOut = true;
	}

	if (changeName != "None") m_isSceneChange = true;
	else m_isSceneChange = false;

	m_changeName = changeName;
}

void cSceneManager::Update()
{
	//1. 씬 변화이펙트는 없지만 다음 씬을 교체해줘야할 때 (예 : 로드 씬 에서 타이틀 씬 접근)
	//2. 다음 씬을 교체해줘야하고, 페이드인 상태이고(화면 나타남), 화이트(또는 블랙)이미지가 불투명도가 240보다 클 때 (교체 도중.... )

	if (
		(!m_isSceneChange && m_next) ||
		(m_next && m_isFadeIn && m_white->m_a > 240.f) ||
	) {
		SAFE_RELEASE(m_now);
		m_now = m_next;
		m_next = nullptr;
		m_now->Init();
	}

	if (m_isFadeChange) FadeSceneChange();

	if (m_now) m_now->Update();
}

void cSceneManager::Render()
{
	if (m_now) m_now->Render();

	if (m_isFadeChange && m_changeName == "WhiteFade")
		IMAGE->Render(m_white->m_text, VEC2(0, 0), VEC2(1, 1), 0.f, FALSE, m_white->m_color);
	else if (m_isFadeChange && m_changeName == "BlackFade")
		IMAGE->Render(m_black->m_text, VEC2(0, 0), VEC2(1, 1), 0.f, FALSE, m_white->m_color);
}

bool cSceneManager::FadeIn()
{
	cImage* img = nullptr;
	if (m_changeName == "WhiteFade") img = m_white;
	else img = m_black;

	if (img->m_a < m_changeSpeed) {
		img->m_a = 0;
		img->SetNowRGB();
		return true;
	}
	else {
		img->m_a -= m_changeSpeed;
		img->SetNowRGB();
		return false;
	}
}

bool cSceneManager::FadeOut()
{
	cImage* img;
	if (m_changeName == "BlackFade") img = m_black;
	else img = m_white;

	if (img->m_a > 255 - m_changeSpeed) {
		img->m_a = 255;
		img->SetNowRGB();
		return true;
	}
	else {
		img->m_a += m_changeSpeed;
		img->SetNowRGB();
		return false;
	}
}

void cSceneManager::FadeSceneChange()
{
	//페이드 아웃 먼저 하고 페이드 인을 해야 한다.
	if (m_isFadeOut) {
		if (FadeOut()) {
			m_isFadeOut = false;
			m_isFadeIn = true;
		}
		return;
	}

	if (m_isFadeIn)
		if (FadeIn())
			m_isFadeIn = m_isFadeChange = m_isSceneChange = false;
}

string cSceneManager::GetNowSceneKey()
{
	for (auto iter : m_scenes) {
		if (m_now == iter.second)
			return iter.first;
	}
	return "현재 씬을 찾을 수 없습니다.\n";
}
