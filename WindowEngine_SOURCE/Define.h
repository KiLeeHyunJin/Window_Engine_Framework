#pragma once

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
