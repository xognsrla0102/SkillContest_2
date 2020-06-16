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
	//로딩 후 각종 UI속 이미지 초기화
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
		//특별한 일을 할 필요가 없는 씬이면
		//현재 UI를 없애준다. (UI 처리, 출력할 일이 없다는 뜻)
		SAFE_RELEASE(m_now);
	}

	if (isChangeUI) m_next = find->second;

	//교체할 ui가 있고, 현재 ui가 교체할 ui와 다를 때
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
