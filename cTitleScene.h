#pragma once
class cTitleScene : public cScene
{
private:
	cTexture* m_bg = nullptr;
	cImage* m_black = nullptr;
	cTimer* m_cameraShakeTiming = nullptr;
	double	m_lightDir;
	double  m_waitFadeOut;
	bool	m_isFadeOut;
public:
	cTitleScene();
	virtual ~cTitleScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

