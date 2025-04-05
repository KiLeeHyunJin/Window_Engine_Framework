#pragma once
#include "CResource.h"

namespace Framework//::Resource
{

	namespace Resource
	{
		class CTexture;
		class CSprite;
		class CFlipbook;
		//class CApplication;
		using namespace Maths;
		class CResourceManager
		{
		public:

			static CTexture*	LoadTexture(const std::wstring& key, const std::wstring& path);
			static void			LoadSound(const std::wstring& key);

			static const bool CreateSprite(const CTexture* texture, const std::wstring& key, const Vector2Int& leftTop, const Vector2Int& size, const Vector2Int& pivot = Maths::Vector2Int::Zero);
			static const bool CreateFlipbook(const std::wstring& key, bool loop);

			static void InsertSprite(const CFlipbook* flipbook, const CSprite* sprite, float duration = 1);

			static const CTexture* FindTexture(const std::wstring& key);
			static const CSprite* FindSprite(const std::wstring& key);
			static const CFlipbook* FindFlipbook(const std::wstring& key);
			static void FindSound(const std::wstring& key);

#pragma region MyRegion
			//static void Insert(const std::wstring& key, CResource* pResource)
			//{
			//	if (pResource == nullptr)
			//	{
			//		return;
			//	}
			//	auto iter = m_mapResoucres.find(key);
			//	if (iter == m_mapResoucres.end())
			//	{
			//		m_mapResoucres.insert(std::make_pair(key, pResource));
			//	}
			//}

			//template<typename CTexture>
			//static const CTexture* Load( const std::wstring& key, const std::wstring& path, 
			//	const UINT horizontalCount, const Maths::Vector2& offset, const Maths::Vector2& size)
			//{
			//	const CTexture* pLoadResource = CResourceManager::FindTexture(key);
			//	if (pLoadResource != nullptr)
			//	{	return pLoadResource;	}

			//	CTexture* pCreateResource = new CTexture();
			//	pCreateResource->SetCount(horizontalCount);

			//	for (size_t i = 0; i < horizontalCount; i++)
			//	{	pCreateResource->PushBackSize(size);	}

			//	Resource::CResource* pParentResource = static_cast<Resource::CResource*>(pCreateResource);
			//	if (LoadResource(pParentResource, key, path) == nullptr)
			//	{	return nullptr;	};
			//	return pCreateResource;
			//}

			//template<typename T>
			//static const T* Load(const std::wstring& key, const std::wstring& path)
			//{
			//	const T* pFindResource = CResourceManager::FindTexture(key);
			//	if (pFindResource != nullptr)
			//	{	return pFindResource;	}
			//	T* pCreateResource = new T();
			//	Resource::CResource* pParentResource = static_cast<Resource::CResource*>(pCreateResource);
			//	pParentResource = LoadResource(pParentResource, key, path);
			//	return pCreateResource;
			//}
#pragma endregion

			

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
				return pResource;
			}

			static void Release();

			static std::map<const std::wstring, Resource::CResource*> m_mapResoucres;

			static std::map<const std::wstring, Resource::CTexture*> m_mapTextures;
			static std::map<const std::wstring, Resource::CSprite*> m_mapSprites;
			static std::map<const std::wstring, Resource::CFlipbook*> m_mapFlipbooks;
		};

#define RESOURCE CResourceManager
	}
	

}


