#include "DXUT.h"
#include "cObject.h"

RECT cObject::GetObjCollider()
{
	RECT rt = {
		GetPos().x - GetImg()->m_info.Width / 2 * GetSize().x,
		GetPos().y - GetImg()->m_info.Height / 2 * GetSize().y,
		GetPos().x + GetImg()->m_info.Width / 2 * GetSize().x,
		GetPos().y + GetImg()->m_info.Height / 2 * GetSize().y,
	};
	return rt;
}

RECT cObject::GetCustomCollider(double n, VEC2 size)
{
	RECT rt = {
		GetPos().x - n * size.x,
		GetPos().y - n * size.y,
		GetPos().x + n * size.x,
		GetPos().y + n * size.y,
	};
	return rt;
}

bool cObject::OutMapChk(int offset)
{
	RECT world = {
		0 - offset,
		0 - offset,
		GAMESIZE + offset,
		GAMESIZE + offset,
	};

	//���� ��ü�� �ʰ� �浹���� ���� �� ( �ʹ��� ��) true ��ȯ
	return (!AABB(GetObjCollider(), world));
}
