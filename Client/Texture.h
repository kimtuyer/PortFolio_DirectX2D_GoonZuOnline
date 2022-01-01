#pragma once
class CTexture abstract
{
public:
	explicit CTexture();
	virtual ~CTexture();
public:
	virtual HRESULT Insert_Texture(const wstring& wstrFilePath, int rgb[], const wstring& wstrStateKey = L"", const DWORD& dwCount =0)PURE;
		// ObjectKey -> ex)Player, Monster1, 1StageBoss, , StateKey 
	virtual  TEXINFO* Get_TexInfo(const wstring& wstrStateKey = L"", const DWORD& dwIndex = 0)PURE; 
	virtual void Release_Texture()PURE; 

};

