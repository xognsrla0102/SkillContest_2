#pragma once
class cMainProc
{
public:
	cMainProc();
	~cMainProc();

	void Init();
	void Update();
	void Render();
	void Release();

	void LostDevice();
	void ResetDevice();
};

