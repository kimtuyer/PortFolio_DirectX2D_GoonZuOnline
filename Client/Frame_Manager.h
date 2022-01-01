#pragma once
class CFrame_Manager
{
public:
	CFrame_Manager();
	~CFrame_Manager();
public:
	void Ready_Frame_Manager(float fFPS); 
	void Render_Frame_Manager(); 
	bool Frame_Lock(); 

private:
	LARGE_INTEGER m_tBeginTime; 
	LARGE_INTEGER m_tEndTime; 
	LARGE_INTEGER m_tCpuTick; 
	float		m_fDeltaTime; 
	float		m_fSPF; 

	TCHAR m_szFPS[32]; 
	float m_fFPSTime; 
	int	m_iFPS; 
};

