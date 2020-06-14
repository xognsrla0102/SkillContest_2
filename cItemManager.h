#pragma once
#include "cObject.h"

class cItem;
class cItemManager : public cObject
{
public:
	vector<cItem*> m_items;
public:
	cItemManager() {}
	virtual ~cItemManager();

	virtual void Update() override;
	virtual void Render() override;
	virtual void OnCollision(cObject* other) override {}
	void Release();
};

