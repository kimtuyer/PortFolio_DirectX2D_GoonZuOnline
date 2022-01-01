#pragma once
#include "Texture.h"
class CSingle_Texture :
	public CTexture
{
public:
	explicit CSingle_Texture();
	virtual ~CSingle_Texture();
public:
	// CTexture을(를) 통해 상속됨
	virtual HRESULT Insert_Texture(const wstring & wstrFilePath, int rgb[],const wstring & wstrStateKey = L"", const DWORD & dwCount = 0) override;
	virtual  TEXINFO * Get_TexInfo(const wstring & wstrStateKey = L"", const DWORD & dwIndex = 0) override;
	virtual void Release_Texture() override;
private:
	TEXINFO m_tTexInfo; 
	int rgb[4]{255,0,0,0};

};

