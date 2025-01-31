#pragma once

// Windows ��� ����
#include <windows.h>

#pragma region  C ��Ÿ�� ��� ����
//#include <stdlib.h>
//#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <cassert>
#include <bitset>
#pragma endregion


#pragma region C++ ǥ�� ���̺귯��
//C++ ǥ�� ���̺귯��
//#include <clocale>
//#include <chrono>
#include <string>
#include <cmath>
#include <functional>
#include <filesystem>
#pragma endregion


#include "Enums.h"
#include "Maths.h"

#pragma region STL
//STL
#include <vector>
#include <list>
#include <queue>
#include <map>
#include <unordered_map>
#include <stack>
#include <queue>
#pragma endregion  STL

#include <dinput.h> //DX_Input

#pragma region WinAPI Graphic

#include <mmsystem.h>

#pragma comment(lib, "Msimg32.lib")
#pragma comment(lib, "winmm.lib")

#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")
#pragma endregion



