#include "DXUT.h"
#include "cEnemy.h"

cEnemy::cEnemy(int hp, int atk)
	: cCharacter(hp), m_atk(atk)
{
}

cEnemy::~cEnemy()
{
}

void cEnemy::Update()
{
}

void cEnemy::Render()
{
}

void cEnemy::OnCollision(cObject* other)
{
}

void cEnemy::N_Way_Tan(string imageName, int n, int theta, VEC2 pos, VEC2 dir, VEC2 size, float bulletSpd, float atk, bool isRandShot, bool isHoming, bool isFaccel, bool isSaccel)
{
}

void cEnemy::N_Straight_Tan(string imageName, int n, int length, VEC2 pos, VEC2 dir, VEC2 size, float bulletSpd, float atk, bool isFaccel, bool isSaccel)
{
}

void cEnemy::Dead()
{
}

void cEnemy::Move()
{
}

void cEnemy::Fire()
{
}
