// TestClient.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"


int main()
{
	// �ӵ� ��� ������ ���� ���� �̴ϴ�. 
	LARGE_INTEGER BeginTime; // 0 
	LARGE_INTEGER EndTime; // 50 
	LARGE_INTEGER CpuTick; // 100 
	float fDeltaTime = 0.f; 
	QueryPerformanceCounter(&BeginTime); // ���� CPU ���� �������� ��ȯ�� ���ִ� �Լ�. 
	QueryPerformanceCounter(&EndTime); 
	QueryPerformanceFrequency(&CpuTick); // �ʴ� CPU �������� ��ȯ�� ���ִ� �Լ�. 


	while (true)
	{
		QueryPerformanceFrequency(&CpuTick); 
		QueryPerformanceCounter(&BeginTime); 
		system("pause"); 
		QueryPerformanceCounter(&EndTime); 
		fDeltaTime = float(EndTime.QuadPart - BeginTime.QuadPart) / CpuTick.QuadPart; 
		cout << fDeltaTime << endl; 
		// �Ⱦ�� no, ��? 
	}
	// ������ ������ ������ ? 
	// ���� üũ�ϰ��� �ϴ� �������� ���� ������ / �ʴ� �������� ������ -> 
    return 0;
}

