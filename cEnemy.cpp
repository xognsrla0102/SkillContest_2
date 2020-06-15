#include "DXUT.h"
#include "cEnemy.h"

cEnemy::cEnemy(int hp, int atk)
	: cCharacter(hp), m_atk(atk)
{
}

cEnemy::~cEnemy()
{
}

void cEnemy::Render()
{
	IMAGE->Render(m_img, m_pos, m_size, m_rot, true);
}

void cEnemy::N_Way_Tan(string imageName, int n, int theta, VEC2 pos, VEC2 dir, VEC2 size, float bulletSpd, float atk, bool isRandShot, bool isHoming, bool isFaccel, bool isSaccel)
{
	double rot = D3DXToDegree(atan2(dir.y, dir.x));
	double newRot;
	int randShotX = 0, randShotY = 0;

	if (n % 2) newRot = rot + (n / 2) * theta;
	else newRot = rot + (n / 2) * theta - theta / 2;

	for (size_t i = 0; i < n; ++i) {
		if (isRandShot) {
			randShotX = rand() % 50;
			randShotY = rand() % 50;
			dir.x = cos(D3DXToRadian(newRot + randShotX));
			dir.y = sin(D3DXToRadian(newRot + randShotY));
		}
		else {
			dir.x = cos(D3DXToRadian(newRot));
			dir.y = sin(D3DXToRadian(newRot));
		}
		auto bullet = new cEnemyBullet(imageName, pos, dir, D3DXToDegree(atan2(dir.y, dir.x)) + 90, bulletSpd, isFaccel, isSaccel, size);
		bullet->SetName("EnemyBullet");
		bullet->m_atk = atk;
		((cBulletManager*)OBJFIND(BULLET))->GetEnemyBullets().push_back(bullet);
		newRot -= theta;
		if (newRot < 0) newRot += 360;
	}
}

void cEnemy::N_Straight_Tan(string imageName, int n, int length, VEC2 pos, VEC2 dir, VEC2 size, float bulletSpd, float atk, bool isFaccel, bool isSaccel)
{
	double rot = D3DXToDegree(atan2(dir.y, dir.x));

	if (n % 2) pos.x -= n / 2 * length;
	else pos.x -= n / 2 * length - length / 2;

	for (size_t i = 0; i < n; ++i) {
		auto bullet = new cEnemyBullet(imageName, VEC2(pos.x + i * length, pos.y), dir, rot + 90, bulletSpd, isFaccel, isSaccel, size);
		bullet->SetName("EnemyBullet");
		bullet->m_atk = atk;
		((cBulletManager*)OBJFIND(BULLET))->GetEnemyBullets().push_back(bullet);
	}
}

bool cEnemy::CanFire()
{
	RECT world = {
		GX(0),
		GY(0),
		GX(GAMESIZE),
		GY(GAMESIZE)
	};
	return AABB(GetObjCollider(), world);
}


