#pragma once
class CTime_Manager
{
	DECLARE_SINGLETON(CTime_Manager)
private:
	CTime_Manager();
	~CTime_Manager();
public:
	float Get_DeltaTime() { return m_fDeltaTime; }
public:
	void Ready_Time_Manager(); 
	void Update_Time_Manager(); 
private:
	LARGE_INTEGER	m_tBeginTime; 
	LARGE_INTEGER	m_tEndTime; 
	LARGE_INTEGER	m_tCpuTick; 
	float			m_fDeltaTime; 
};

