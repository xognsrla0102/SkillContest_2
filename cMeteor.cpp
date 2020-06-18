#include "DXUT.h"
#include "cMeteor.h"

cMeteor::cMeteor(VEC2 pos, double rot, double downSpd)
	: cEnemy(0, 10 * GAME->m_nowStage * GAME->m_level), m_downSpd(downSpd)
{
	m_img = IMAGE->FindTexture("EnemyMeteorIMG");

	m_objName = "EnemyMeteor";
	m_pos = pos;
	m_size = VEC2(1.5, 1.5);
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

void cMeteor::Move()
{
	m_pos.y += m_downSpd * D_TIME;
}
