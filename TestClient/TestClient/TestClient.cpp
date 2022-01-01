// TestClient.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"


int main()
{
	// 속도 라는 개념을 집어 넣을 겁니다. 
	LARGE_INTEGER BeginTime; // 0 
	LARGE_INTEGER EndTime; // 50 
	LARGE_INTEGER CpuTick; // 100 
	float fDeltaTime = 0.f; 
	QueryPerformanceCounter(&BeginTime); // 현재 CPU 진동 누적수를 반환을 해주는 함수. 
	QueryPerformanceCounter(&EndTime); 
	QueryPerformanceFrequency(&CpuTick); // 초당 CPU 진동수를 반환을 해주는 함수. 


	while (true)
	{
		QueryPerformanceFrequency(&CpuTick); 
		QueryPerformanceCounter(&BeginTime); 
		system("pause"); 
		QueryPerformanceCounter(&EndTime); 
		fDeltaTime = float(EndTime.QuadPart - BeginTime.QuadPart) / CpuTick.QuadPart; 
		cout << fDeltaTime << endl; 
		// 싫어욥 no, 뭐? 
	}
	// 누적수 나누기 진동수 ? 
	// 내가 체크하고자 하는 시작지점 부터 끝지점 / 초당 진동수로 나누면 -> 
    return 0;
}

