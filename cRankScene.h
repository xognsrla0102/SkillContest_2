#pragma once
#include "cScene.h"
class cRankScene : public cScene
{
private:
	cTexture* m_bg = nullptr;
public:
	cRankScene();
	virtual ~cRankScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

