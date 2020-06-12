#include "DXUT.h"
#include "cScroolMap.h"

cScroolMap::cScroolMap(cTexture* text)
{
	m_img1 = new cImage;
	m_img2 = new cImage;
	m_createGas = new cTimer(0);

	m_img1->m_text = m_img2->m_text = text;
	Init();
}

cScroolMap::~cScroolMap()
{
	Release();

	SAFE_DELETE(m_img1);
	SAFE_DELETE(m_img2);
	SAFE_DELETE(m_createGas);
}

void cScroolMap::Init()
{
	m_img1->m_pos = VEC2(WINSIZEX / 2, WINSIZEY / 2 - (double)m_img2->m_text->m_info.Height);
	m_img2->m_pos = VEC2(WINSIZEX / 2, WINSIZEY / 2);

	m_mapSpd = 1000;
	m_gasSpd = 1500;
}

void cScroolMap::Update()
{
	if (m_createGas->Update()) {
		m_createGas->m_delay = 2.f + rand() % 3;
		//m_gas.push_back(new cImage);
		//m_gas[m_gas.size() - 1]->m_text = IMAGE->FindTexture("CloudIMG");
		//int height = m_gas[m_gas.size() - 1]->m_text->m_info.Height;
		//m_gas[m_gas.size() - 1]->m_pos = VEC2(GAMESIZE / (rand() % 3), -height);
	}

	m_img1->m_pos.y += m_mapSpd * D_TIME;
	m_img2->m_pos.y += m_mapSpd * D_TIME;

	if (m_img2->m_pos.y >= WINSIZEY / 2 + (double)m_img2->m_text->m_info.Height) {
		m_img1->m_pos = VEC2(WINSIZEX / 2, WINSIZEY / 2 -(double)m_img2->m_text->m_info.Height);
		m_img2->m_pos = VEC2(WINSIZEX / 2, WINSIZEY / 2);
	}

	size_t size = m_gas.size();
	for (int i = 0; i < size; ++i) {
		m_gas[i]->m_pos.y += m_gasSpd * D_TIME;
		if (m_gas[i]->m_pos.y > GAMESIZE) {
			SAFE_DELETE(m_gas[i]);
			m_gas.erase(m_gas.begin() + i);
			--i, --size;
		}
	}
}

void cScroolMap::Render()
{
	IMAGE->Render(m_img1->m_text, m_img1->m_pos, VEC2(1, 1), 0.f, true);
	IMAGE->Render(m_img2->m_text, m_img2->m_pos, VEC2(1, 1), 0.f, true);

	for (auto iter : m_gas)
		IMAGE->Render(iter->m_text, iter->m_pos, VEC2(1, 1), 0.f);
}

void cScroolMap::Release()
{
	for (auto iter : m_gas)
		SAFE_DELETE(iter);
	m_gas.clear();
}
