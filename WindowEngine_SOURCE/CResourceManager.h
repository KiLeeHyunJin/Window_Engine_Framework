#pragma once
#include "CResource.h"
#include "CommonInclude.h"
#include "CSoundManager.h"


namespace Framework//::Resource
{
	class CTilemap;

	namespace Resource
	{
		class CTexture;
		class CSprite;
		class CFlipbook;
		class CSound;
	}

	namespace Manager
	{
		using namespace Maths;
		using namespace Resource;

		//class CSoundManager;

		class CResourceManager 
		{
			DECLARE_SINGLE(CResourceManager)
			RELEASE_SINGLE(CResourceManager)
		public:

			void		SaveTilemap(const std::wstring& key, const std::wstring& path);
			void		InsertSprite(const CFlipbook* flipbook, const CSprite* sprite, float duration = 1);

			CTilemap*		LoadTilemap(const std::wstring& key, const std::wstring& path);
			const CSound*	LoadSound(const std::wstring& key, const std::wstring& path, UINT uiChannel);
			const CTexture*	LoadTexture(const std::wstring& key, const std::wstring& path);

			const bool	CreateSprite(const CTexture* texture, const std::wstring& key, const Vector2Int& leftTop, const Vector2Int& size, const Vector2Int& pivot = Maths::Vector2Int::Zero);
			const bool	CreateFlipbook(const std::wstring& key, bool loop);
			CTilemap*	CreateTilemap(const std::wstring& key);


			const CTexture*		FindTexture(const std::wstring& key);
			const CSprite*		FindSprite(const std::wstring& key);
			const CFlipbook*	FindFlipbook(const std::wstring& key);
			const CSound*		FindSound(const std::wstring& key);

			void Initialize()		{};

			friend class CApplication;
		private:
			//CResourceManager();
			~CResourceManager();

			CResource* LoadResource(CResource* pResource, const std::wstring& key, const std::wstring& path)
			{
				if (FAILED(pResource->Load(path)))
				{
					assert(false);
					SAFE_DELETE(pResource);
					return nullptr;
				}
				pResource->SetName(key);
				pResource->SetPath(path);
				return pResource;
			}

			void Release();

			//std::map<const std::wstring, CResource*> m_mapResoucres = {};

			std::map<const std::wstring, CTexture*> m_mapTextures	= {};
			std::map<const std::wstring, CSprite*> m_mapSprites		= {};
			std::map<const std::wstring, CFlipbook*> m_mapFlipbooks = {};
			std::map<const std::wstring, CTilemap*> m_mapTilemap	= {};
			std::map<const std::wstring, CSound*> m_mapSounds		= {};
		};

	}
	using RESOURCE = Manager::CResourceManager;


	

}


