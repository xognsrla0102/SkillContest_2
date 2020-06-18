#include "DXUT.h"
#include "cBulletManager.h"

cBulletManager::cBulletManager()
{
}

cBulletManager::~cBulletManager()
{
	Release();
}

void cBulletManager::Update()
{
	size_t size = m_pBullet.size();
	for (size_t i = 0; i < size; ++i) {
		m_pBullet[i]->Update();
		if (m_pBullet[i]->GetLive() == false) {
			SAFE_DELETE(m_pBullet[i]);
			m_pBullet.erase(m_pBullet.begin() + i);
			--i, --size;
		}
	}
	size = m_eBullet.size();
	for (size_t i = 0; i < size; ++i) {
		m_eBullet[i]->Update();
		if (m_eBullet[i]->GetLive() == false) {
			if(!m_eBullet[i]->OutMapChk())
				EFFECT->AddEffect(new cEffect("DieEFFECT", 1, 0, m_eBullet[i]->GetPos(), VEC2(0, 0), VEC2(1, 1), VEC2(1, 1), 1000));
			SAFE_DELETE(m_eBullet[i]);
			m_eBullet.erase(m_eBullet.begin() + i);
			--i, --size;
		}
	}
}

void cBulletManager::Render()
{
	for (auto iter : m_pBullet)
		iter->Render();
	for (auto iter : m_eBullet)
		iter->Render();
}


void cBulletManager::EnemyBulletReset()
{
	for (auto iter : m_eBullet)
		iter->SetLive(false);
}

void cBulletManager::Reset()
{
	for (auto iter : m_pBullet)
		iter->SetLive(false);
	for (auto iter : m_eBullet)
		iter->SetLive(false);
}

void cBulletManager::Release()
{
	for (auto iter : m_pBullet)
		SAFE_DELETE(iter);
	m_pBullet.clear();
	for (auto iter : m_eBullet)
		SAFE_DELETE(iter);
	m_eBullet.clear();
}

