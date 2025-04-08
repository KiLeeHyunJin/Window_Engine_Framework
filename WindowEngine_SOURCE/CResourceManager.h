#pragma once
#include "CResource.h"

namespace Framework//::Resource
{

	namespace Resource
	{
		class CTexture;
		class CSprite;
		class CFlipbook;
	}

	namespace Manager
	{
		using namespace Maths;
		using namespace Resource;

		class CResourceManager
		{
		public:

			static CTexture* LoadTexture(const std::wstring& key, const std::wstring& path);
			static void		 LoadSound(const std::wstring& key);

			static const bool CreateSprite(const CTexture* texture, const std::wstring& key, const Vector2Int& leftTop, const Vector2Int& size, const Vector2Int& pivot = Maths::Vector2Int::Zero);
			static const bool CreateFlipbook(const std::wstring& key, bool loop);

			static void InsertSprite(const CFlipbook* flipbook, const CSprite* sprite, float duration = 1);

			static const CTexture* FindTexture(const std::wstring& key);
			static const CSprite* FindSprite(const std::wstring& key);
			static const CFlipbook* FindFlipbook(const std::wstring& key);
			static void FindSound(const std::wstring& key);


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

			static std::map<const std::wstring, CResource*> m_mapResoucres;

			static std::map<const std::wstring, CTexture*> m_mapTextures;
			static std::map<const std::wstring, CSprite*> m_mapSprites;
			static std::map<const std::wstring, CFlipbook*> m_mapFlipbooks;
		};

	}
	using RESOURCE = Manager::CResourceManager;


	

}


