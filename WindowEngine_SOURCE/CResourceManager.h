#pragma once
#include "CResource.h"
//#include "CTexture.h"

namespace Framework//::Resource
{
	namespace Resource
	{
		class CTexture;

		class CResourceManager
		{
		public:
			template<typename T>
			static const T* Find(const std::wstring& key)
			{
				auto iter = m_mapResoucres.find(key);
				return iter == m_mapResoucres.end() ? nullptr : dynamic_cast<T*>(iter->second);
			}

			static void Insert(const std::wstring& key, CResource* pResource)
			{
				if (pResource == nullptr)
				{
					return;
				}
				auto iter = m_mapResoucres.find(key);
				if (iter == m_mapResoucres.end())
				{
					m_mapResoucres.insert(std::make_pair(key, pResource));
				}
			}
			
			template<typename CTexture>
			static const CTexture* Load( const std::wstring& key, const std::wstring& path, 
				const UINT horizontalCount, const Maths::Vector2& offset, const Maths::Vector2& size)
			{
				const CTexture* pLoadResource = CResourceManager::Find<CTexture>(key);
				if (pLoadResource != nullptr)
				{	return pLoadResource;	}

				CTexture* pCreateResource = new CTexture();
				pCreateResource->SetCount(horizontalCount);

				for (size_t i = 0; i < horizontalCount; i++)
				{	pCreateResource->PushBackSize(size);	}

				Resource::CResource* pParentResource = static_cast<Resource::CResource*>(pCreateResource);
				if (LoadResource(pParentResource, key, path) == nullptr)
				{	return nullptr;	};
				return pCreateResource;
			}

			template<typename T>
			static const T* Load(const std::wstring& key, const std::wstring& path)
			{
				const T* pFindResource = CResourceManager::Find<T>(key);
				if (pFindResource != nullptr)
				{	return pFindResource;	}
				T* pCreateResource = new T();
				Resource::CResource* pParentResource = static_cast<Resource::CResource*>(pCreateResource);
				pParentResource = LoadResource(pParentResource, key, path);
				return pCreateResource;
			}


			friend class CApplication;
		private:
			CResourceManager();
			~CResourceManager();

			static CResource* LoadResource(CResource* pResource, const std::wstring& key, const std::wstring& path)
			{
				if (FAILED(pResource->Load(path)))
				{
					assert(true);
					SAFE_DELETE(pResource);
					return nullptr;
				}
				pResource->SetName(key);
				pResource->SetPath(path);
				m_mapResoucres.insert(std::make_pair(key, pResource));
				return pResource;
			}

			static void Release()
			{
				for (auto& pair : m_mapResoucres)
				{
					delete pair.second;
					pair.second = nullptr;
				}
				m_mapResoucres.clear();
			}

			static std::map<const std::wstring, Resource::CResource*> m_mapResoucres;
		};

#define RESOURCE CResourceManager
	}
	

}


