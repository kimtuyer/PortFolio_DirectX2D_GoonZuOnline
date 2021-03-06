#pragma once
#include "Scene.h"
class CLoading final:
	public CScene
{
public:
	explicit CLoading();
	virtual ~CLoading();
public:
	static unsigned __stdcall ImageLoading(LPVOID pVoid);
public:

	// CScene을(를) 통해 상속됨
	virtual HRESULT Ready_Scene() override;
	virtual void Update_Scene() override;
	virtual void Render_Scene() override;
	virtual void Release_Scene() override;
private:
	HANDLE m_hThread;
	CRITICAL_SECTION m_Critical_Section;
	static int rgb[4];

};

