#include "stdafx.h"
#include "Frame_Manager.h"


CFrame_Manager::CFrame_Manager()
	:m_szFPS(L"")
	, m_fFPSTime(0.f)
	, m_iFPS(0)
{
}


CFrame_Manager::~CFrame_Manager()
{
}

void CFrame_Manager::Ready_Frame_Manager(float fFPS)
{
	m_fSPF = 1.f / fFPS; // 0.0166+666
	m_fDeltaTime = 0.f; 
	QueryPerformanceCounter(&m_tBeginTime); 
	QueryPerformanceCounter(&m_tEndTime);
	QueryPerformanceFrequency(&m_tCpuTick);
}

void CFrame_Manager::Render_Frame_Manager()
{
	m_fFPSTime += CTime_Manager::Get_Instance()->Get_DeltaTime();
	if (1.f <= m_fFPSTime)
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS); 
		m_iFPS = 0; 
		m_fFPSTime = 0.f; 
	}
	//SetWindowText(g_hWND, m_szFPS); 
	D3DXMATRIX matTrans; 
	D3DXMatrixTranslation(&matTrans, 100.f, 100.f, 0.f);

	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matTrans); 
	CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), m_szFPS, lstrlen(m_szFPS), nullptr, 0, D3DCOLOR_ARGB(255, 0, 0, 0)); 
}

bool CFrame_Manager::Frame_Lock()
{
	QueryPerformanceCounter(&m_tEndTime);
	
	m_fDeltaTime += float(m_tEndTime.QuadPart - m_tBeginTime.QuadPart) / m_tCpuTick.QuadPart;
	m_tBeginTime = m_tEndTime; 
	if (m_fSPF <= m_fDeltaTime)
	{
		QueryPerformanceFrequency(&m_tCpuTick);
		m_fDeltaTime = 0.f; 
		++m_iFPS; 
		return true; 
	}
	return false;
}
