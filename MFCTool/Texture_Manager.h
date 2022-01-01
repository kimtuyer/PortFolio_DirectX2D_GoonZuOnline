#pragma once
class CTexture; 
class CTexture_Manager
{
	DECLARE_SINGLETON(CTexture_Manager)
public:
	enum TEX_ID {TEX_SINGLE, TEX_MULTI, TEX_END};
private:
	explicit CTexture_Manager();
	~CTexture_Manager();
public:
	HRESULT Insert_Texture_Manager(TEX_ID eID,
		const wstring& wstrFilePath,
		const wstring& wstrOjbectKey,
		const wstring& wstrStateKey = L"",
		const DWORD& dwCount = 0, D3DCOLOR color = (255, 0, 0, 0));
	const TEXINFO* Get_TexInfo_Manager(const wstring& wstrObjectKey,
		const wstring& wstrStateKey = L"",
		const DWORD& dwIndex = 0);
	void Release_Texture_Manager(); 
private:
	// ObjectKey ;
	map<wstring, CTexture*> m_mapTexture; 
	
};

