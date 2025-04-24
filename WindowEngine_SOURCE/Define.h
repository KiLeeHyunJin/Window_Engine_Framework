#pragma once

static const int SOUND_MAX_CHANNEL = 32;

static const float DELTA_TICK	= 0.016f;

static const float REMAIN_RATIO = 0.5f;  // 0.0 ~ 1.0 → 남겨둘 충돌 비율
static const float MIN_OVERLAP	= 0.7f;   // 너무 작은 값은 무시
static const float DRAG_ALLOWABLE_RANGE = 40.f;
static const float CLICK_ALLOWABLE_TIME = 0.2f;

#define DECLARE_SINGLE(classname)							\
private :													\
classname() {}												\
static classname* s_instance;								\
public :													\
	static classname& GetInstance()							\
	{														\
		if(classname::s_instance == nullptr)				\
		{													\
			classname::s_instance = new classname;			\
		}													\
		return *(classname::s_instance);					\
	}										

#define RELEASE_SINGLE(classname)							\
public :													\
	static void DestroyInstance()							\
	{														\
		if (classname::s_instance != nullptr)				\
		{													\
			classname::s_instance->Release();				\
			delete classname::s_instance;					\
			classname::s_instance = nullptr;				\
		}													\
	}														\

#define GET_SINGLE(classname)	classname::GetInstance()

#define SAFE_DELETE(ptr)									\
if(ptr != nullptr)											\
{															\
	delete ptr;												\
	ptr = nullptr;											\
}											

#define RELEASE_MAP(map)									\
			for (auto& pair : map)							\
			{												\
				/*pair.second->Release();*/						\
				delete pair.second;							\
			}												\
			map.clear()										\

#define DECLARE_PARENT(classname) using SUPER = classname;	\
