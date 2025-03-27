#include "CResourceManager.h"
namespace Framework//::Resource
{
	namespace Resource
	{
		std::map<std::wstring, Resource::CResource*> CResourceManager::m_mapResoucres = {};

		CResourceManager::CResourceManager()	{}
		CResourceManager::~CResourceManager()	{}
	}


}