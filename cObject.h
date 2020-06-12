#pragma once

class cObject abstract
{
protected:
	cImage* m_img = nullptr;
	cAnimation* m_ani = nullptr;

	VEC2 m_pos = VEC2(0, 0);
	VEC2 m_size = VEC2(1, 1);

	double m_rot = 0.0;

	bool m_isLive = true;
	bool m_isActive = false;

	string m_objName;
public:
	cObject() {}
	virtual ~cObject() {}

	virtual void Update() PURE;
	virtual void Render() PURE;
	virtual void OnCollision(cObject* other) PURE;

	bool OutMapChk(int offset = 0);

	cTexture*	GetImg() { return m_img->m_text; }
	VEC2		GetPos() { return m_pos; }
	VEC2		GetSize() { return m_size; }
	FLOAT		GetRot() { return m_rot; }
	BOOL		GetLive() { return m_isLive; }
	BOOL		GetActive() { return m_isActive; }
	cAnimation* GetAni() { return m_ani; }
	string		GetName() { return m_objName; }

	VEC2&		GetRefPos() { return m_pos; }

	RECT		GetObjCollider();
	RECT		GetCustomCollider(double n, VEC2 size = VEC2(1, 1));

	void SetImg(cTexture* img)    { m_img->m_text = img; }
	void SetPos(VEC2 pos)		  { m_pos = pos; }
	void SetSize(VEC2 size)		  { m_size = size; }
	void SetRot(FLOAT rot)		  { m_rot = rot; }
	void SetLive(BOOL isLive)	  { m_isLive = isLive; }
	void SetActive(BOOL isActive) { m_isActive = isActive; }
	void SetName(string name)     { m_objName = name; }
};

