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
			VEC2 pos = m_enemy[i]->GetPos();
			EFFECT->AddEffect(
				new cEffect("DieEFFECT", 1, 0, pos, VEC2(0, 0), VEC2(1, 1), VEC2(1, 1), 1000)
			);
			for (size_t j = 0; j < m_enemy[i]->GetItemName().size(); j++) {
				string nowItemName = m_enemy[i]->GetItemName()[j];
				((cItemManager*)OBJFIND(ITEM))->m_items.push_back(
					new cItem(nowItemName, pos, VEC2(pos.x, pos.y - (40 + rand() % 30)))
				);
			}
			GAME->m_nowExp += 20 + rand() % 3 * 10;

			SAFE_DELETE(m_enemy[i]);
			m_enemy.erase(m_enemy.begin() + i);
			--i, --size;
		}
	}
}

void cEnemyManager::Render()
{
	for (auto iter : m_enemy)
		iter->Render();
}

void cEnemyManager::Release()
{
	for (auto iter : m_enemy)
		SAFE_DELETE(iter);
	m_enemy.clear();
}
