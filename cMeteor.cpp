#include "DXUT.h"
#include "cMeteor.h"

cMeteor::cMeteor(string name, VEC2 pos, VEC2 size, double rot, double downSpd)
	: cEnemy(100, 5), m_downSpd(downSpd)
{
	m_img = IMAGE->FindTexture(name);

	m_objName = "EnemyMeteor";
	m_pos = pos;
	m_size = size;
	m_rot = rot;
}

cMeteor::~cMeteor()
{
}

void cMeteor::Update()
{
	Move();
	if(OutMapChk(200)) m_isLive = false;
}

void cMeteor::Render()
{
	IMAGE->Render(m_img, m_pos, m_size, m_rot, true);
}

void cMeteor::OnCollision(cObject* other)
{
}

void cMeteor::Dead()
{
}

void cMeteor::Move()
{
	m_pos.y += m_downSpd * D_TIME;
}
