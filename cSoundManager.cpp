#include "DXUT.h"
#include "cSoundManager.h"

cSoundManager::cSoundManager()
{
	m_manager = new CSoundManager;
	m_manager->Initialize(DXUTGetHWND(), 2);
}

cSoundManager::~cSoundManager()
{
	for (auto iter : m_sounds)
		SAFE_DELETE(iter.second);
	m_sounds.clear();
	SAFE_DELETE(m_manager);
}

void cSoundManager::AddSound(string str, wstring path)
{
	auto find = m_sounds.find(str);
	if (find != m_sounds.end()) {
		DEBUG_LOG("%s 사운드가 이미 있습니다.\n", str.c_str());
		return;
	}
	CSound* sound;
	m_manager->Create(&sound, (LPWSTR)path.c_str());
	m_sounds[str] = sound;
}

void cSoundManager::Play(string str, BOOL isLoop)
{
	auto find = m_sounds.find(str);
	if (find == m_sounds.end()) {
		DEBUG_LOG("%s 사운드가 없습니다.\n", str.c_str());
		return;
	}
	find->second->GetBuffer(0)->SetCurrentPosition(0);
	find->second->Play(0, isLoop);
}

void cSoundManager::Copy(string str)
{
	auto find = m_sounds.find(str);
	if (find == m_sounds.end()) {
		DEBUG_LOG("%s사운드가 없습니다.\n", str.c_str());
		return;
	}
	LPDIRECTSOUNDBUFFER buf;
	m_manager->GetDirectSound()->DuplicateSoundBuffer(find->second->GetBuffer(0), &buf);
	buf->SetCurrentPosition(0);
	buf->Play(0, 0, 0);
}

void cSoundManager::Stop(string str)
{
	auto find = m_sounds.find(str);
	if (find == m_sounds.end()) {
		DEBUG_LOG("%s사운드가 없습니다.\n", str.c_str());
		return;
	}
	find->second->Stop();
}
