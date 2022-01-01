#include "stdafx.h"
#include "Time_Manager.h"

IMPLEMENT_SINGLETON(CTime_Manager)
CTime_Manager::CTime_Manager()
	:m_fDeltaTime(0.f)
	, m_tBeginTime({})
{
	ZeroMemory(&m_tEndTime, sizeof(m_tEndTime)); 
	ZeroMemory(&m_tCpuTick, sizeof(LARGE_INTEGER)); 

}


CTime_Manager::~CTime_Manager()
{
}

void CTime_Manager::Ready_Time_Manager()
{
	QueryPerformanceFrequency(&m_tCpuTick); 
	QueryPerformanceCounter(&m_tBeginTime); 
	QueryPerformanceCounter(&m_tEndTime); 
}

void CTime_Manager::Update_Time_Manager()
{
	QueryPerformanceCounter(&m_tEndTime); 
	QueryPerformanceFrequency(&m_tCpuTick); 

	m_fDeltaTime = float(m_tEndTime.QuadPart - m_tBeginTime.QuadPart) / m_tCpuTick.QuadPart; 
	m_tBeginTime = m_tEndTime; 
}
