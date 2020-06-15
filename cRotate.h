#pragma once
#include "cEnemy.h"
class cRotate : public cEnemy
{
private:
	int rotDir;
public:
	cRotate(VEC2 pos);
	virtual ~cRotate();

	virtual void Update() override;
	virtual void Move() override;
	virtual void Fire() override;
};

