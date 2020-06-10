#include "DXUT.h"
#include "cImageManager.h"

cImageManager::cImageManager()
{
	D3DXCreateSprite(DEVICE, &m_sprite);
}

cImageManager::~cImageManager()
{
	SAFE_RELEASE(m_sprite);
	for (auto iter : m_imgs)
		SAFE_DELETE(iter.second);
	m_imgs.clear();
}

void cImageManager::Begin(bool isUI)
{
	if (isUI) m_sprite->Begin(D3DXSPRITE_ALPHABLEND);
	else	  m_sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);
}

void cImageManager::End()
{
	m_sprite->End();
}

void cImageManager::ReBegin(bool isUI)
{
	End();
	Begin(isUI);
}

void cImageManager::LostDevice()
{
	m_sprite->OnLostDevice();
}

void cImageManager::ResetDevice()
{
	m_sprite->OnResetDevice();
}

void cImageManager::AddTexture(string name, string path, int cnt)
{
	auto find = m_imgs.find(name);
	if (find != m_imgs.end()) {
		DEBUG_LOG("%s이름의 텍스쳐가 이미 있습니다.\n", name.c_str());
		return;
	}
	else if (cnt < 0) {
		DEBUG_LOG("%d는 cnt에 넣을 수 없습니다.\n", cnt);
		return;
	}
	cMultiTexture* text = new cMultiTexture;
	text->AddTexture(path, cnt);
	m_imgs[name] = text;
}

cMultiTexture* cImageManager::FindMultiTexture(string name)
{
	auto find = m_imgs.find(name);
	if (find == m_imgs.end()) {
		DEBUG_LOG("%s 멀티 텍스쳐를 찾을 수 없습니다.\n", name.c_str());
		return nullptr;
	}
	return find->second;
}

cTexture* cImageManager::FindTexture(string name, int cnt)
{
	auto find = m_imgs.find(name);
	if (find == m_imgs.end()) {
		DEBUG_LOG("%s 텍스쳐를 찾을 수 없습니다.\n", name.c_str());
		return nullptr;
	}
	return find->second->FindTexture(cnt);
}

void cImageManager::Render(cTexture* text, VEC2 pos, VEC2 size, double rot, bool isCenter, D3DXCOLOR color)
{
	if (text) {
		MATRIX mat, s, r, t;
		D3DXMatrixScaling(&s, size.x, size.y, 1.f);
		D3DXMatrixRotationZ(&r, D3DXToRadian(rot));
		D3DXMatrixTranslation(&t, pos.x, pos.y, 0.f);
		mat = s * r * t;
		m_sprite->SetTransform(&mat);
		if (isCenter) m_sprite->Draw(text->m_text, nullptr, &VEC3(text->m_info.Width / 2, text->m_info.Height / 2, 0.f), nullptr, color);
		else m_sprite->Draw(text->m_text, nullptr, nullptr, nullptr, color);
	}
	else DEBUG_LOG("텍스쳐가 없어서 그릴 수 없습니다.\n");
}

void cImageManager::CropRender(cTexture* text, VEC2 pos, RECT rt, VEC2 size, bool isCenter)
{
	if (text) {
		MATRIX mat, s, t;
		D3DXMatrixScaling(&s, size.x, size.y, 1.f);
		D3DXMatrixTranslation(&t, pos.x, pos.y, 0.f);
		mat = s * t;
		m_sprite->SetTransform(&mat);
		if (isCenter) m_sprite->Draw(text->m_text, &rt, &VEC3(text->m_info.Width / 2, text->m_info.Height / 2, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		else m_sprite->Draw(text->m_text, &rt, nullptr, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	else DEBUG_LOG("텍스쳐가 없어서 그릴 수 없습니다.\n");
}

void cImageManager::DrawNum(string text, VEC2 pos, int numD, VEC2 size)
{
	cTexture* nowImg;
	for (size_t i = 0; i < text.size(); ++i) {
		char key[256];
		sprintf(key, "num_%c", text[i]);
		nowImg = FindTexture(key);
		Render(nowImg, VEC2(pos.x + (i * numD), pos.y), size);
	}
}

void cImageManager::DrawFloat(string text, VEC2 pos, int length, int dotD, int numD, VEC2 size)
{
	cTexture* nowImg;
	for (size_t i = 0; i < length; ++i) {
		if (text[i] == '.') {
			nowImg = FindTexture("num_dot");
			Render(nowImg, VEC2(pos.x + (i * dotD), pos.y), size);
		}
		else {
			char key[256];
			sprintf(key, "num_%c", text[i]);
			nowImg = FindTexture(key);
			Render(nowImg, VEC2(pos.x + (i * numD), pos.y), size);
		}
	}
}

void cImageManager::DrawFont(string text, VEC2 pos, string fontName, int size, D3DXCOLOR color)
{
	LPD3DXFONT font;
	D3DXCreateFontA(
		DEVICE,
		size,
		0,
		FW_NORMAL,
		1,
		false,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		fontName.c_str(),
		&font
	);

	RECT rt = { pos.x, pos.y, 0, 0 };
	MATRIX m;
	D3DXMatrixIdentity(&m);
	m_sprite->SetTransform(&m);
	font->DrawTextA(
		m_sprite,
		text.c_str(),
		-1,
		&rt,
		DT_NOCLIP,
		color
	);

	SAFE_RELEASE(font);
}
