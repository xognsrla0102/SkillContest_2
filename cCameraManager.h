#pragma once
#include "cSingleton.hpp"

class cCameraManager : public cSingleton<cCameraManager>
{
private:
	MATRIX m_view;
	MATRIX m_proj;
public:
	VEC2 m_initPos = VEC2(WINSIZEX / 2, WINSIZEY / 2);
	VEC2 m_pos = VEC2(WINSIZEX / 2, WINSIZEY / 2);
	VEC2 m_size = VEC2(1, 1);

	double m_time;
	int m_power;
	bool m_isShake = false;
public:
	cCameraManager();
	virtual ~cCameraManager();

	void ResetCamera();
	void Update();
	void SetTransform();

	void SetShake(double time, int power, VEC2 initPos = VEC2(WINSIZEX / 2, WINSIZEY / 2));
	void Shake();
};

#define CAMERA cCameraManager::GetInst()