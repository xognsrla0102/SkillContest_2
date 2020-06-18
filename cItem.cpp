#include "DXUT.h"
#include "cItem.h"

cItem::cItem(string key, VEC2 pos, VEC2 endPos)
{
	m_key = key;
	m_img = IMAGE->FindTexture(key);
	m_pos = pos;
	m_endPos = endPos;
}

cItem::~cItem()
{
}

void cItem::Update()
{
	cPlayer* player = (cPlayer*)OBJFIND(PLAYER);

	if (m_isEndPos == FALSE) {
		if (DistPoint(m_pos, m_endPos) < 5.f) m_isEndPos = TRUE;
		else Lerp(m_pos, m_endPos, 2);
	}
	else {
		//0.5초만에 원래 속도 도달
		if (m_accel < 1.f) m_accel += D_TIME * 2;
		else m_accel = 1.f;
		m_pos.y += 500.f * D_TIME * m_accel;
	}

}

void cItem::Render()
{
	IMAGE->Render(m_img, m_pos, VEC2(1, 1), 0.f, true);
}

void cItem::OnCollision(cObject* other)
{
	if (m_isEndPos == FALSE) return;

	RECT itemRect = GetObjCollider();
	RECT playerRect = OBJFIND(PLAYER)->GetObjCollider();

	cPlayer* player = (cPlayer*)OBJFIND(PLAYER);

	if (AABB(itemRect, playerRect)) {
		SOUND->Copy("GetItemSND");
		SOUND->Copy("GetItemSND");
		SOUND->Copy("GetItemSND");

		if (m_key == "ItemHpIMG") {
			player->m_hp += player->m_hpMax / 5.0;
			if (player->m_hp > player->m_hpMax) {
				player->m_hp = player->m_hpMax;
			}
		}
		else if (m_key == "ItemLevelUpIMG") {
			if (GAME->m_level != 5) GAME->m_nowExp = GAME->m_expMax;
		}
		else if (m_key == "ItemSkillTimeIMG") {
			//모든 스킬 쿨타임 초기화
			//if(!player->m_isAon) player->m_aTime = 0;
			//if(!player->m_isBon) player->m_bTime = 0;
		}
		m_isLive = false;
	}
}

