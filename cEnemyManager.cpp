#include "DXUT.h"
#include "cEnemyManager.h"

cEnemyManager::cEnemyManager()
{
}

cEnemyManager::~cEnemyManager()
{
	Release();
}

void cEnemyManager::Update()
{
	size_t size = m_enemy.size();
	for (size_t i = 0; i < size; ++i) {
		m_enemy[i]->Update();
		if (!m_enemy[i]->GetLive()) {
			SAFE_DELETE(m_enemy[i]);
			m_enemy.erase(m_enemy.begin() + i);
			--i, --size;
		}
	}
	if (m_midBoss) {
		if (m_midBoss->GetLive()) m_midBoss->Update();
		else SAFE_DELETE(m_midBoss);
	}
}

void cEnemyManager::Render()
{
	for (auto iter : m_enemy)
		iter->Render();
	if (m_midBoss && m_midBoss->GetLive())
		m_midBoss->Render();
}

void cEnemyManager::Release()
{
	for (auto iter : m_enemy)
		SAFE_DELETE(iter);
	m_enemy.clear();
	SAFE_DELETE(m_midBoss);
}
