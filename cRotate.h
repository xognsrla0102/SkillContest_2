#pragma once
#include "cEnemy.h"
class cRotate : public cEnemy
{
private:
	int rotDir;
public:
	cRotate(string name, VEC2 pos, VEC2 size);
	virtual ~cRotate();

	virtual void Update() override;
	virtual void Move() override;
	virtual void Fire() override;
};

