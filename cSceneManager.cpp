#include "DXUT.h"
#include "cSceneManager.h"

cSceneManager::cSceneManager()
{
	IMAGE->AddTexture("BlackIMG", "resources/image/scenechange/black.png");
	IMAGE->AddTexture("WhiteIMG", "resources/image/scenechange/white.png");

	m_white = new cImage;
	m_white->m_text = IMAGE->FindTexture("WhiteIMG");
	m_white->m_a = 0.f;

	m_black = new cImage;
	m_black->m_text = IMAGE->FindTexture("BlackIMG");
	m_black->m_a = 0.f;
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
	//씬 전환이 "None" 일 때는 바로 교체
	if (!m_isSceneChange && m_next) {
		SAFE_RELEASE(m_now);
		m_now = m_next;
		m_next = nullptr;
		m_now->Init();
	}
	else if (m_isFadeChange) FadeSceneChange();

	if (m_now) m_now->Update();
}

void cSceneManager::Render()
{
	if (m_now) m_now->Render();

	if (m_isFadeChange && m_changeName == "WhiteFade")
		IMAGE->Render(m_white->m_text, VEC2(WINSIZEX / 2, WINSIZEY / 2), VEC2(1.5, 1.5), 0.f, true, m_white->m_color);
	else if (m_isFadeChange && m_changeName == "BlackFade")
		IMAGE->Render(m_black->m_text, VEC2(WINSIZEX / 2, WINSIZEY / 2), VEC2(1.5, 1.5), 0.f, true, m_black->m_color);
}

void cSceneManager::FadeSceneChange()
{
	cImage* img;
	if (m_changeName == "BlackFade") img = m_black;
	else img = m_white;

	//페이드 아웃 먼저 하고 페이드 인을 해야 한다.
	if (m_isFadeOut) {
		Lerp(img->m_a, 255.0, m_changeSpeed);
		if (img->m_a > 253.0) {
			img->m_a = 255.0;
			m_isFadeOut = false;

			//씬 교체해줄 타이밍
			SAFE_RELEASE(m_now);
			m_now = m_next;
			m_next = nullptr;
			m_now->Init();
		}
		return;
	}
	else {
		Lerp(img->m_a, 0.0, m_changeSpeed);
		if (img->m_a < 2.0) {
			img->m_a = 0.0;
			m_isFadeOut = true;
			m_isFadeChange = m_isSceneChange = false;
		}
	}
}

string cSceneManager::GetNowSceneKey()
{
	for (auto iter : m_scenes) {
		if (m_now == iter.second)
			return iter.first;
	}
	return "현재 씬을 찾을 수 없습니다.\n";
}
