#include "DXUT.h"
#include "cMotionBlur.h"

cMotionBlur::cMotionBlur(int blurCnt, VEC2 nowPos)
{
	m_computeBlur = new cTimer(0.05);

	double alpha = 255.0 / (blurCnt + 1);
	for (size_t i = 0; i < blurCnt; i++) {
		m_motionInfo.push_back(new cMotionInfo(nowPos));
		m_motionInfo[i]->m_color = D3DCOLOR_ARGB((int)(alpha + alpha * i), 128, 128, 255);
	}
}

cMotionBlur::~cMotionBlur()
{
	SAFE_DELETE(m_computeBlur);
	for (auto iter : m_motionInfo)
		SAFE_DELETE(iter);
	m_motionInfo.clear();
}

void cMotionBlur::Update(VEC2 nowPos)
{
	//1�����Ӹ��� ���� ����ϴ� �� ���꿡 ������ �� �� ����
	if (m_computeBlur->Update()) {
		//UINT ����÷ο� ����
		if (m_motionInfo.size() == 0) return;
		for (int i = 0; i < m_motionInfo.size() - 1; ++i)
			m_motionInfo[i]->m_motionPos = m_motionInfo[i + 1]->m_motionPos;
		m_motionInfo[m_motionInfo.size() - 1]->m_motionPos = nowPos;
	}
}
