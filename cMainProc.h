#pragma once
class cMainProc
{
public:
	cMainProc();
	~cMainProc();

	void Update();
	void Render();

	void LostDevice();
	void ResetDevice();
};

