#pragma once

class cMotionBlur
{
public:
	vector<cMotionInfo*> m_motionInfo;
	cTimer* m_computeBlur = nullptr;
public:
	cMotionBlur(int blurCnt, VEC2 nowPos);
	~cMotionBlur();

	void Update(VEC2 nowPos);
};

