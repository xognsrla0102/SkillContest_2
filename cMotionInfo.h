#pragma once

class cMotionInfo {
public:
	VEC2 m_motionPos;
	D3DXCOLOR m_color;
public:
	cMotionInfo(VEC2 pos) : m_motionPos(pos) {}
};