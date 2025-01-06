#pragma once
#include "CResource.h"

namespace Framework
{
	class CResourceManager
	{
	public:
		template<typename T>
		static T* Find(const std::wstring& key) 
		{
			auto iter = m_mapResoucre.find(key);
			return iter == m_mapResoucre.end() ? nullptr : dynamic_cast<T*>(iter->second);
		}

		template<typename T>
		static T* Load(const std::wstring& key, const std::wstring& path)
		{
			T* pResource = CResourceManager::Find(key);
			if (pResource != nullptr)
			{
				return pResource;
			}
			pResource = new T();
			if ( FAILED(pResource->Load(path)) )
			{
				assert();
				//MessageBox(nullptr, key + L"Image Load Failed!", L"Error", MB_OK);
				return nullptr;
			}
			pResource->SetName(key);
			pResource->SetPath(path);

			m_mapResoucre.insert(std::make_pair<key,pResource>);
			return pResource;
		}

	private:
		static std::map<std::wstring, CResource*> m_mapResoucre;
	};
}


