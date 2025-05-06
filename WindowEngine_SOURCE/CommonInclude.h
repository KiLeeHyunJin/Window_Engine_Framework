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
//#include <filesystem>

#include <io.h>
#include <string>

#include <cmath>
#include <limits.h> 
#include <algorithm>

#include <functional>

#pragma endregion


#pragma region Headers

#include "Types.h"

#include "ColliderStruct.h" // Maths.h가 포함되어있음
#include "Structs.h"

#include "Enums.h"
#include "Define.h"
#include "Utils.h"


#pragma endregion


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

#define _CRTDEBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif


#pragma region WinAPI_Graphic

#pragma comment(lib, "Msimg32.lib")
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")
#pragma endregion

#pragma region GDI_PLUS
//#include <gdiplus.h>
//#include <gdiplusheaders.h>
//#pragma comment(lib, "gdiplus.lib")
#pragma endregion


#pragma region D2D
#include <wincodec.h>

#include <d2d1.h>
#pragma comment(lib,"D2D1.lib")
#pragma endregion

#pragma region Text
#include <dwrite.h>
#pragma comment(lib,"Dwrite.lib")
#pragma endregion

#pragma region Video
#include <Vfw.h>
#pragma comment(lib, "vfw32.lib")
#pragma endregion


#pragma region FMOD_Sound
#include "..\\WindowEngine_SOURCE\\FMOD\\inc\\fmod.h"
#include "..\\WindowEngine_SOURCE\\FMOD\\inc\\fmod.hpp"
#pragma comment(lib, "..\\WindowEngine_SOURCE\\FMOD\\lib\\x64\\fmod_vc.lib")

//#include <mmsystem.h>
//#include <dsound.h>
//#pragma comment(lib, "winmm.lib")
//#pragma comment(lib, "dsound.lib")

#pragma endregion

