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


#include "Define.h"
#include "Enums.h"
#include "Maths.h"
#include "ColliderStruct.h"


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

#pragma region WinAPI Graphic

#include <mmsystem.h>

#pragma comment(lib, "Msimg32.lib")
#pragma comment(lib, "winmm.lib")

#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")
#pragma endregion





