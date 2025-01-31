#pragma once

// Windows 헤더 파일
#include <windows.h>

#pragma region  C 런타임 헤더 파일
//#include <stdlib.h>
//#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <cassert>
#include <bitset>
#pragma endregion


#pragma region C++ 표준 라이브러리
//C++ 표준 라이브러리
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



