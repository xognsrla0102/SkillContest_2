#include "DXUT.h"
#include "cUI.h"
#include "cUIManager.h"

cUIManager::cUIManager()
{
	m_UIs["TitleSceneUI"] = new cTitleUI;
	m_UIs["IngameSceneUI"] = new cIngameUI;
	m_UIs["MidBossClearSceneUI"] = new cMidBossClearUI;
}

cUIManager::~cUIManager()
{
	for (auto iter : m_UIs)
		SAFE_DELETE(iter.second);
	m_UIs.clear();
}

void cUIManager::Init()
{
	//�ε� �� ���� UI�� �̹��� �ʱ�ȭ
	for (auto iter : m_UIs)
		iter.second->Init();
}

void cUIManager::Update()
{
	const string sceneName = SCENE->GetNowSceneKey();
	bool isChangeUI = false;
	map<string, cUI*>::iterator find;

	if (sceneName == "TitleScene") {
		find = m_UIs.find("TitleSceneUI");
		isChangeUI = true;
	}
	else if (sceneName == "IngameScene" || sceneName == "MidBossScene") {
		find = m_UIs.find("IngameSceneUI");
		isChangeUI = true;
	}
	else if (sceneName == "MidBossClearScene") {
		find = m_UIs.find("MidBossClearSceneUI");
		isChangeUI = true;
	}
	else {
		//Ư���� ���� �� �ʿ䰡 ���� ���̸�
		//���� UI�� �����ش�. (UI ó��, ����� ���� ���ٴ� ��)
		SAFE_RELEASE(m_now);
	}

	if (isChangeUI) m_next = find->second;

	//��ü�� ui�� �ְ�, ���� ui�� ��ü�� ui�� �ٸ� ��
	if (m_next && m_now != m_next) {
		if (m_now) m_now->Release();
		m_now = m_next;
		m_next = nullptr;
		m_now->Init();
	}

	if (m_now) m_now->Update();
}

void cUIManager::Render()
{
	if (m_now) m_now->Render();
	IMAGE->DrawFont(to_string(DXUTGetFPS()), VEC2(1800, 900));
}

cUI* cUIManager::FindUI(string name)
{
	auto find = m_UIs.find(name);
	if (find == m_UIs.end()) return nullptr;
	return find->second;
}
