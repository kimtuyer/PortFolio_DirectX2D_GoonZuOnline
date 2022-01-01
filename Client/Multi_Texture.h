#pragma once
#include "Texture.h"
class CMulti_Texture final:
	public CTexture
{
public:
	explicit CMulti_Texture();
	virtual ~CMulti_Texture();
public:
	// CTexture을(를) 통해 상속됨in
	virtual HRESULT Insert_Texture(const wstring & wstrFilePath, int rgb[], const wstring & wstrStateKey = L"", const DWORD & dwCount = 0) override;
	virtual  TEXINFO * Get_TexInfo(const wstring & wstrStateKey = L"", const DWORD & dwIndex = 0) override;
	virtual void Release_Texture() override;
private:
	map<wstring, vector<TEXINFO*>> m_mapMultiTex; 	
	int rgb[4]{255,0,0,0};

};

