// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <process.h>
#include <functional>


// ���� fmod_vc
 #pragma comment(lib, "fmod_vc.lib")
//#pragma comment(lib, "fmodex_vc.lib")
#include <io.h>
#include <fmod.h>

// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.

// ������ ũ��� ��Ÿ����� ������ �̿��Ͽ� ������ �� �ִ�. 
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include "../Headers/Headers.h"
#include "Scroll_Manager.h"
#include "Time_Manager.h"
#include "GameObject_Manager.h"
#include "CSoundMgr.h""