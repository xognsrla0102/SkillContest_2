#pragma once
#include "cScene.h"
class cIngameScene : public cScene
{
private:
	cTimer* m_t = nullptr;
	cScroolMap* m_map = nullptr;
	int m_time;
public:
	cIngameScene();
	virtual ~cIngameScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	void LevelDesign();
	void CreateMeteor(int startGrid, int endGrid, int speed);
	void CreateTurret(int startGrid, int endGrid, int speed);
	void CreateCircle(int startGrid, int endGrid, int speed);
	void CreateRazer(int startGrid, int endGrid);
};

