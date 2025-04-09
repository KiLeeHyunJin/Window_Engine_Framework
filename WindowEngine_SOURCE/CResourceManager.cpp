#include "CResourceManager.h"
#include "CTexture.h"
#include "CSprite.h"
#include "CFlipbook.h"

namespace Framework//::Resource
{

	namespace Manager
	{
		CResourceManager* CResourceManager::s_instance = nullptr;
		//std::map<const std::wstring, Resource::CResource*> CResourceManager::m_mapResoucres = {};
		//std::map<const std::wstring, Resource::CTexture*>  CResourceManager::m_mapTextures = {};
		//std::map<const std::wstring, Resource::CSprite*>   CResourceManager::m_mapSprites = {};
		//std::map<const std::wstring, Resource::CFlipbook*> CResourceManager::m_mapFlipbooks = {};
		//CResourceManager::CResourceManager() {}
		CResourceManager::~CResourceManager() {}

		CTexture* CResourceManager::LoadTexture(const std::wstring& key, const std::wstring& path)
		{
			const CTexture* pTexture = CResourceManager::FindTexture(key);
			if (pTexture != nullptr)
			{
				return nullptr;
			}
			CTexture* pCreateResource = new CTexture();
			Resource::CResource* pParentResource = static_cast<Resource::CResource*>(pCreateResource);
			if (LoadResource(pParentResource, key, path) == nullptr)
			{
				return nullptr;
			};
			m_mapTextures.insert(std::make_pair(key, pCreateResource));
			return pCreateResource;
		}

		void CResourceManager::LoadSound(const std::wstring& key)
		{
		}



		const bool CResourceManager::CreateSprite(const CTexture* texture, const std::wstring& key, const Maths::Vector2Int& leftTop, const Maths::Vector2Int& size, const Maths::Vector2Int& pivot)
		{
			const CSprite* pSprite = CResourceManager::FindSprite(key);
			if (pSprite != nullptr)
			{
				return false;
			}
			CTexture* pTexture = const_cast<CTexture*>(texture);
			CSprite* pCreateResource = new CSprite(pTexture, leftTop, size, pivot);
			Resource::CResource* pParentResource = static_cast<Resource::CResource*>(pCreateResource);
			const std::wstring& path = pTexture->GetPath();
			if (LoadResource(pParentResource, key, path) == nullptr)
			{
				return false;
			};
			m_mapSprites.insert(std::make_pair(key, pCreateResource));
			return true;
		}

		const bool CResourceManager::CreateFlipbook(const std::wstring& key, bool loop)
		{
			const Resource::CFlipbook* flipbook = FindFlipbook(key);
			if (flipbook != nullptr)
			{
				return false;
			}
			Resource::CFlipbook* pCreateResource = new CFlipbook(loop);
			Resource::CResource* pParentResource = static_cast<Resource::CResource*>(pCreateResource);
			if (LoadResource(pParentResource, key, L"") == nullptr)
			{
				return false;
			};
			m_mapFlipbooks.insert(std::make_pair(key, pCreateResource));
			return true;
		}

		void CResourceManager::InsertSprite(const CFlipbook* flipbook, const CSprite* sprite, float duration)
		{
			CFlipbook* pFlipbook = const_cast<CFlipbook*>(flipbook);
			pFlipbook->AddSprite(sprite, duration);
		}


		const CTexture* CResourceManager::FindTexture(const std::wstring& key)
		{
			auto iter = m_mapTextures.find(key);
			if (iter == m_mapTextures.end())
			{
				return nullptr;
			}
			return iter->second;
		}
		const CSprite* CResourceManager::FindSprite(const std::wstring& key)
		{
			auto iter = m_mapSprites.find(key);
			if (iter == m_mapSprites.end())
			{
				return nullptr;
			}
			return iter->second;
		}
		const CFlipbook* CResourceManager::FindFlipbook(const std::wstring& key)
		{
			auto iter = m_mapFlipbooks.find(key);
			if (iter == m_mapFlipbooks.end())
			{
				return nullptr;
			}
			return iter->second;
		}
		void CResourceManager::FindSound(const std::wstring& key)
		{
		}


		void CResourceManager::Release()
		{
			RELEASE_MAP(m_mapResoucres);
			RELEASE_MAP(m_mapTextures);
			RELEASE_MAP(m_mapSprites);
			RELEASE_MAP(m_mapFlipbooks);
		}
	}

	namespace Resource
	{
		
	}


}