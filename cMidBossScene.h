#pragma once
#include "cScene.h"

class cMidBoss;
class cMidBossScene : public cScene
{
private:
	cTexture* m_map = nullptr;
	cTexture* m_planet = nullptr;
public:
	cMidBossScene();
	virtual ~cMidBossScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

