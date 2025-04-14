#pragma once

// Windows 헤더 파일
#include <windows.h>

#pragma region  C 런타임 헤더 파일
//#include <stdlib.h>
#include <malloc.h>
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
//#include <filesystem>
#pragma endregion


#include "Define.h"
#include "Enums.h"
#include "Maths.h"
#include "ColliderStruct.h"

#include <limits.h>


#pragma region STL
//STL
#include <vector> // list
#include <list> //linked list 

#include <stack> 
#include <queue>

#include <map> // tree
#include <set>

#include <unordered_map> //hash
#include <unordered_set>


#pragma endregion  STL

#include <dinput.h> //DX_Input

//#define _CRTDEBG_MAP_ALLOC
//#include <cstdlib>
//#include <crtdbg.h>
//
//#ifdef _DEBUG
//#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
//#endif


#pragma region WinAPI Graphic

#pragma comment(lib, "Msimg32.lib")
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

#include <gdiplus.h>
#include <gdiplusheaders.h>
#pragma comment(lib, "gdiplus.lib")
#pragma endregion



#pragma region Sound
#include <mmsystem.h>
#include <dsound.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")
#pragma endregion

