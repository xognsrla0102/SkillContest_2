#pragma once
#include "cScene.h"
class cBossScene : public cScene
{
private:
	cTexture* m_map = nullptr;
public:
	cBossScene();
	virtual ~cBossScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

