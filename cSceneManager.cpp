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
		DEBUG_LOG("�� �����Ͱ� �����ϴ�.\n");
		return;
	}

	if (m_scenes.find(key) != m_scenes.end()) {
		DEBUG_LOG("%s ���� �̹� �ֽ��ϴ�.\n", key.c_str());
		return;
	}
	m_scenes[key] = scenePtr;
}

void cSceneManager::ChangeScene(const string& key, string changeName, double changeSpeed)
{
	auto find = m_scenes.find(key);
	if (find == m_scenes.end()) {
		DEBUG_LOG("%s���� �����ϴ�.\n", key.c_str());
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
	//1. �� ��ȭ����Ʈ�� ������ ���� ���� ��ü������� �� (�� : �ε� �� ���� Ÿ��Ʋ �� ����)
	//2. ���� ���� ��ü������ϰ�, ���̵��� �����̰�(ȭ�� ��Ÿ��), ȭ��Ʈ(�Ǵ� ��)�̹����� �������� 240���� Ŭ �� (��ü ����.... )

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
	//���̵� �ƿ� ���� �ϰ� ���̵� ���� �ؾ� �Ѵ�.
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
	return "���� ���� ã�� �� �����ϴ�.\n";
}
