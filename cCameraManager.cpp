#include "DXUT.h"
#include "cCameraManager.h"

cCameraManager::cCameraManager()
{
	D3DXMatrixIdentity(&m_view);
	D3DXMatrixIdentity(&m_proj);

	ResetCamera();
}

cCameraManager::~cCameraManager()
{
}

void cCameraManager::ResetCamera()
{
	m_size = VEC2(1, 1);
	m_pos = VEC2(WINSIZEX / 2, WINSIZEY / 2);
	D3DXMatrixOrthoLH(&m_proj, WINSIZEX * m_size.x, -WINSIZEY * m_size.y, 0.f, 1.f);
	DEVICE->SetTransform(D3DTS_PROJECTION, &m_proj);
	m_isShake = false;
}

void cCameraManager::Update()
{
	D3DXMatrixIdentity(&m_view);
	if (m_isShake) Shake();
	D3DXMatrixTranslation(&m_view, -m_pos.x, -m_pos.y, 0.f);
}

void cCameraManager::SetTransform()
{
	D3DXMatrixOrthoLH(&m_proj, WINSIZEX * m_size.x, -WINSIZEY * m_size.y, 0.f, 1.f);
	DEVICE->SetTransform(D3DTS_PROJECTION, &m_proj);
	DEVICE->SetTransform(D3DTS_VIEW, &m_view);
}

void cCameraManager::SetShake(double time, int power, VEC2 initPos)
{
	m_time = time;
	m_power = power;
	m_initPos = initPos;
	m_isShake = true;
}

void cCameraManager::Shake()
{
	if (m_time > 0) {
		m_pos = RandomInsideSquare() * m_power + m_initPos;
		m_time -= D_TIME;
	}
	else {
		m_time = 0.0;
		m_pos = m_initPos;
	}
}
