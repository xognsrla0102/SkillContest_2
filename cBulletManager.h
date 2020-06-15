#pragma once

class cBullet;
class cBulletManager : public cObject
{
private:
	vector<cBullet*> m_pBullet;
	vector<cBullet*> m_eBullet;
public:
	cBulletManager();
	virtual ~cBulletManager();

	virtual void Update() override;
	virtual void Render() override;
	virtual void OnCollision(cObject* other) override {}
	void Reset();
	void Release();

	vector<cBullet*>& GetPlayerBullets() { return m_pBullet; }
	vector<cBullet*>& GetEnemyBullets() { return m_eBullet; }
};

