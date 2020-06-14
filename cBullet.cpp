#include "DXUT.h"
#include "cBullet.h"

cBullet::cBullet(string imageName, VEC2 pos, VEC2 dir, double rot, VEC2 size)
{
	m_img = IMAGE->FindTexture(imageName);

	m_pos = pos;
	m_dir = dir;
	m_rot = rot;
	m_size = size;
}

cBullet::~cBullet()
{
}

void cBullet::Render()
{
	IMAGE->Render(m_img, m_pos, m_size, m_rot, true);
}

void cBullet::Homing()
{
	Lerp(m_dir, m_target);
}
