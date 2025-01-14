#pragma once
#include "CResource.h"

namespace Framework::Resource
{
	class CResourceManager
	{
	public:
		template<typename T>
		static T* Find(const std::wstring& key) 
		{
			auto iter = m_mapResoucres.find(key);
			return iter == m_mapResoucres.end() ? nullptr : dynamic_cast<T*>(iter->second);
		}

		template<typename T>
		static T* Load(const std::wstring& key, const std::wstring& path)
		{
			T* pResource = CResourceManager::Find<T>(key);
			if (pResource != nullptr)
			{
				return pResource;
			}
			Resource::CResource* pParentResource = static_cast<Resource::CResource*>(new T());
			if ( FAILED(pParentResource->Load(path)) )
			{
				assert(1);
				//MessageBox(nullptr, key + L"Image Load Failed!", L"Error", MB_OK);
				return nullptr;
			}
			pParentResource->SetName(key);
			pParentResource->SetPath(path);
			m_mapResoucres.insert(std::make_pair(key, pParentResource));
			return pResource;
		}

		friend class CApplication;
	private:
		static void Release()
		{
			for (const auto& pair : m_mapResoucres)
			{
				delete pair.second;
			}
			m_mapResoucres.clear();
		}

		static std::map<std::wstring, Resource::CResource*> m_mapResoucres;
	};

#define RESOURCE CResourceManager

}


